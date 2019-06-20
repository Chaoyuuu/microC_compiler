/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "y.tab.h"

int table_depth = 0;
const char *type_f = "function";
const char *type_p = "parameter";
const char *type_v = "variable";

struct Entry{
    struct Entry * entry_next;
    struct Entry * entry_pre;

    int index;
    char name[20];     
    char kind[20];
    char type[20];
    int scope;
    char attribute[50];

    Value entry_val;
};

struct Table{
    int table_depth;
    struct Entry * entry_header;
    struct Entry * entry_current;
    struct Table * pre;
};

struct Table *table_header = NULL;
struct Table *table_current = NULL;
struct Table *table_dump = NULL;

struct Func{
    char f_name[50];
    Symbol_type f_type;
    struct Func * f_pre;
    int f_count;
    char f_attr[50];
};

struct Func * f_header = NULL;
struct Func * f_current = NULL;

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[500];  // Get current code line from lex
extern char syntax_buf[500];
extern int error_flag; //1.redefined 2.undefined
extern int syntax_flag;
extern char error_msg[500];
extern int dump_flag;
extern void yyerror(char *s);

int func_flag = 0;


// int cast_flag = 0;          // flag for arith casting
char func_buf[5000];         // buf for jasmin function
char func_para[50];         // buf for function parameter
char func_para_2[50];
char label_buf[500];        // buf for if-else {compond statement}
int label_index = 0;        // index of if-else label
int func_input_num = 0;     // index of func_para_type[]
Value func_para_type[10]; // buf for function input parameter
Value trash_var;     // for trash value parameter
FILE *file;         // To generate .j file for Jasmin


/* Symbol table function - you can add new function if needed. */
void get_attribute(struct Entry * tmp);
void create_symbol();
void lookup_symbol();
void lookup_function();
void insert_symbol();
void dump_symbol();
void dump_table();


/* expression function */
Value switch_mul_op();
Value switch_addition_op();
Value switch_postfix_op();
Value switch_assign_op();
Value switch_relation_op();
Value get_id_value();    //get id type & value
Value get_id_entry();    //get id type structure

//arithmetic
Value mul_arith(Value v1, Value v2);
Value div_arith(Value v1, Value v2);
Value mod_arith(Value v1, Value v2);
Value add_arith(Value v1, Value v2);
Value minus_arith(Value v1, Value v2);

//error detecting && tool
Value gencode_funcall();  //function checking and return is_arith & type
int func_return_checking();
void create_func_table();
void set_func_para();

//code generation function
Value gencode_global_1();
Value gencode_global_2();
Value gencode_local_1();
Value gencode_local_2();
Value gencode_parameter();
void gencode_func();
void gencode_print();
void gencode_return();
void gencode_iload();
void gencode_istore();
void gencode_if_arith();

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    
    Value val;
    Operator op;

}

/* Token */
%token BOOL FLOAT INT VOID STRING
%token INC_OP DEC_OP GE_OP LE_OP EQ_OP NE_OP AND_OP OR_OP
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token PRINT RETURN
%token IF ELSE FOR WHILE 
%token SEMICOLON QUOTA 

/* Token with return, which need to sepcify type */
%token <val> I_CONST F_CONST STRING_CONST 
%token <val> ID TRUE FALSE

%type <val> type initializer 
%type <val> expression comparison_expr add_expr mul_expr 
%type <val> postfix_expr parenthesis_expr assign_expr
%type <op>  postfix_op mul_op relation_op addition_op assign_op 

/* Yacc will start at this nonterminal */
%start program 

/* Grammar section */
%%

program
    : program stat 
    | error
    |
;

stat
    : declaration 
    | compound_stat
    | expression_stat
    | print_func 
    | function_declaration
;

declaration
    : type ID '=' expression SEMICOLON  { lookup_symbol($2.id_name, 1); 
                                          if(error_flag != 1){
                                            insert_symbol($1, $2, type_v, $4);
                                          }
                                        }
    | type ID SEMICOLON { lookup_symbol($2.id_name, 1); 
                          if(error_flag != 1){
                            insert_symbol($1, $2, type_v, trash_var); 
                          }
                        }
;

print_func
    : PRINT '(' initializer ')' SEMICOLON { gencode_print($3); }
;

compound_stat
    : 
    '{'      
    program 
    '}'     { dump_table(); dump_flag = 1;}
;

expression_stat
    : selection_statement { /* printf("&&&&&&&& is select\n"); */}
    | while_statement 
    | expression SEMICOLON { /* printf("&&&&&&&&is expression\n"); */}
    | return_statement 
;

selection_statement
    : IF { create_symbol(); }
      '(' expression ')' compound_stat
    | selection_statement
      ELSE { create_symbol(); } 
      compound_stat
    | selection_statement
      ELSE IF{ create_symbol(); }
      '(' expression ')' compound_stat
;

while_statement
    : WHILE                                 
      { create_symbol(); }
     '(' expression ')' compound_stat 
;


expression
    : assign_expr
;

assign_expr
    : comparison_expr                       {}
    | assign_expr assign_op comparison_expr   { $$ = switch_assign_op($1, $2, $3); }
;

comparison_expr
    : add_expr {}
    | comparison_expr relation_op add_expr { $$ = switch_relation_op($1, $2, $3); }
;

add_expr
    : mul_expr {}
    | add_expr addition_op mul_expr { $$ = switch_addition_op($1, $2, $3); }
;

mul_expr
    : postfix_expr {}
    | mul_expr mul_op postfix_expr { $$ = switch_mul_op($1, $2, $3); }
;

postfix_expr
    : parenthesis_expr {}
    | parenthesis_expr postfix_op { $$ = switch_postfix_op($1, $2); }
;

parenthesis_expr
    : initializer { $$ = $1; }                           /* for constant */
    | ID { lookup_function($1.id_name, 1); }   /* for function */
      declarator2 { $$ = gencode_funcall($1); } 
    | '(' expression ')' { $$ = $2; }
;

postfix_op
    : INC_OP    { $$ = INC_OPT; }
    | DEC_OP    { $$ = DEC_OPT; }
;

mul_op
    : '*'   { $$ = MUL_OPT; }
    | '/'   { $$ = DIV_OPT; }
    | '%'   { $$ = MOD_OPT; }
;

relation_op
    : '>'   { $$ = MORE_OPT; }
    | '<'   { $$ = LESS_OPT; }
    | GE_OP { $$ = GE_OPT; }
    | LE_OP { $$ = LE_OPT; }
    | EQ_OP { $$ = EQ_OPT; }
    | NE_OP { $$ = NE_OPT; }
;

addition_op
    : '+'   { $$ = ADD_OPT; }
    | '-'   { $$ = MINUS_OPT; }
;

assign_op
    : ADD_ASSIGN { $$ = ADD_ASSIGN_OPT; }
    | SUB_ASSIGN { $$ = SUB_ASSIGN_OPT; }
    | MUL_ASSIGN { $$ = MUL_ASSIGN_OPT; }
    | DIV_ASSIGN { $$ = DIV_ASSIGN_OPT; }
    | MOD_ASSIGN { $$ = MOD_ASSIGN_OPT; }
    | '='        { $$ = ASSIGN_OPT; }
;

return_statement
    : RETURN expression SEMICOLON { gencode_return($2); }
    | RETURN SEMICOLON  { gencode_return(trash_var); }
;

function_declaration
    : type ID declarator compound_stat  { // lookup_function($2.id_name, 3);      //declare
                                          int a = func_return_checking($1, $2, 0); 
                                          if(a == 0){
                                              insert_symbol($1, $2, type_f, trash_var);
                                          }
                                          gencode_func($1, $2);

                                        }
    | type ID declarator SEMICOLON  { dump_table();                             //define
                                      // lookup_function($2.id_name, 2); 
                                      int a = func_return_checking($1, $2, 1);
                                      if(error_flag != 1 && a == 0){
                                            insert_symbol($1, $2, type_f, trash_var);
                                      }
                                      f_current->f_count = 1;
                                    }
;

declarator
    : '(' { create_symbol(); }
      identifier_list ')'  
    | '(' { create_symbol(); }
      ')'
;

identifier_list
    : identifier_list ',' type ID  { insert_symbol($3, $4, type_p, trash_var); 
                                     set_func_para($3, 1);}
    | type ID
        { insert_symbol($1, $2, type_p, trash_var); set_func_para($1, 0);}
;

declarator2
    : '(' identifier_list2 ')' 
    | '(' ')'
;

identifier_list2
    : identifier_list2 ',' expression   { if($3.symbol_type == ID_Type){
                                            func_para_type[func_input_num++] = get_id_entry($3);
                                          }else
                                            func_para_type[func_input_num++] = $3;
                                        }
    | expression    { if($1.symbol_type == ID_Type){
                        func_para_type[func_input_num++] = get_id_entry($1);
                      }else
                        func_para_type[func_input_num++] = $1; 
                    }
;

initializer
    : I_CONST /*neg_const I_CONST */ { $$ = yylval.val; } 
    | F_CONST /*neg_const F_CONST */ { $$ = yylval.val; }
    | QUOTA STRING_CONST QUOTA { $$ = yylval.val; }
    | TRUE  { $$ = yylval.val; }
    | FALSE { $$ = yylval.val; }
    | ID { lookup_symbol($1.id_name, 2); $$ = yylval.val; }
;

/* neg_const
    : '-'
    |
; */

/* actions can be taken when meet the token or rule */
/* $$ = yylval.val; */
type
    : INT   { $$ = yylval.val; }
    | FLOAT { $$ = yylval.val; }
    | BOOL  { $$ = yylval.val; }
    | STRING{ $$ = yylval.val; }
    | VOID  { $$ = yylval.val; }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    //init
    memset(func_buf, 0, sizeof(func_buf));  //init func_buf
    trash_var.symbol_type = T_Type;         //init trash_var

    file = fopen("compiler_hw3.j","w");
    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");
             

    create_symbol();
    yyparse();

    if(syntax_flag != 0){
        // print syntax error msg
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno, syntax_buf);
        printf("| %s","syntax error");
        printf("\n|-----------------------------------------------|\n\n");
        return 0;
    } 
    
    dump_table();
    dump_symbol();
    printf("\nTotal lines: %d \n",yylineno);

    fclose(file);

    return 0;
}

void yyerror(char *s)
{
    if(!strcmp(s, "syntax error")){
        // printf("in syntax error");
        memset(syntax_buf, 0, sizeof(syntax_buf));
        strcpy(syntax_buf, buf);
        syntax_flag = 1;
        // printf(" btn %s, num = %d",buf, yylineno);
        
        return;
    }

    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s",s);
    printf("\n|-----------------------------------------------|\n\n");
    
}

void create_symbol() {
    //initialize symbol_table
    struct Table * ptr = malloc(sizeof(struct Table));

    ptr->table_depth = table_depth++;   //depth == scope
    ptr->entry_header = NULL;
    ptr->entry_current = ptr->entry_header;
    ptr->pre = table_current;

    table_current = ptr;

    if(table_header == NULL){
        table_header = table_current;
    }

    printf("\n----in create_symbol, depth = %d, current = %p----\n", ptr->table_depth, table_current);
}

void insert_symbol(Value _type, Value _ID, char* k, Value _expr) {
   
    struct Table *ptr = table_current; 
    struct Entry *e_ptr = malloc(sizeof(struct Entry));

    Symbol_type t = _type.symbol_type;
    char *n = _ID.id_name;
    
    // printf("\n----in insert_symbol, %d, %s, %s, %d----\n", t, n, k, ptr->table_depth);

    if(ptr->entry_header == NULL){
        ptr->entry_header = e_ptr;
        e_ptr->entry_pre = NULL;
        e_ptr->entry_next = NULL;
        e_ptr->index = 0;
    }else{
        e_ptr->entry_pre = ptr->entry_current;
        ptr->entry_current->entry_next = e_ptr; 
        e_ptr->index = (ptr->entry_current->index) + 1;
    }
    
    ptr->entry_current = e_ptr;
    //initialize entry
    e_ptr->entry_next = NULL;
    e_ptr->scope = ptr->table_depth;
    memset(e_ptr->type, 0, sizeof(e_ptr->type));
    memset(e_ptr->kind, 0, sizeof(e_ptr->kind));
    memset(e_ptr->name, 0, sizeof(e_ptr->name));
    memset(e_ptr->attribute, 0, sizeof(e_ptr->attribute));

    //set symbol table
    strcpy(e_ptr->kind, k);
    strcpy(e_ptr->name, n);  

    switch (t){
        case V_Type:
            strcpy(e_ptr->type, "void");
            break;
        case I_Type:
            strcpy(e_ptr->type, "int");
            break;
        case F_Type:
            strcpy(e_ptr->type, "float");
            break;
        case S_Type:
            strcpy(e_ptr->type, "String");
            break;
        /*    
        case ID_Type:
            strcpy(e_ptr->type, "ID");
            break;
        */
        case B_Type:
            strcpy(e_ptr->type, "bool");
            break;
        default:
            printf("wrong input in type insert_symbol");
            break;
    }

    // for gencode
    if(strcmp(k, "function") == 0){
        get_attribute(e_ptr);
        create_func_table(_type, _ID);
        // gencode_func(_type, _ID);
    }else if(strcmp(k, "variable") == 0){      
        //paremeter and variable, generate to jasim & set e_ptr->entry_val
        if(table_current->table_depth == 0){
            if(_expr.symbol_type != T_Type)       //int a = 3;
                e_ptr->entry_val = gencode_global_1(_type, _ID, _expr, e_ptr->entry_val);
            else                                //int a;
                e_ptr->entry_val = gencode_global_2(_type, _ID, e_ptr->entry_val);
        }else{
            if(_expr.symbol_type != T_Type)        //int a = 3;
                e_ptr->entry_val = gencode_local_1(_type, _ID, _expr, e_ptr->index, e_ptr->entry_val);
            else                                //int a;
                e_ptr->entry_val = gencode_local_2(_type, _ID, e_ptr->index, e_ptr->entry_val);
        }
    }else if(strcmp(k, "parameter") == 0){      
        //paremeter,only set e_ptr->entry_val, no generate to jasmin
        e_ptr->entry_val = gencode_parameter(_type, _ID, e_ptr->index);
    }else{
        printf("error in -- insert_symbol\n");
    }

    printf("%s, %d\n", e_ptr->entry_val.id_name, e_ptr->entry_val.id_symbol_type);
 
    printf("\n++++%d, %s, %s, %s, %d++++\n", e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope);
}

void create_func_table(Value _type, Value _id){
    printf("in create_function_table\n");

    printf("hooo\n");
    struct Func * f_ptr = malloc(sizeof(struct Func));
    memset(f_ptr->f_name, 0, sizeof(f_ptr->f_name));
    memset(f_ptr->f_attr, 0, sizeof(f_ptr->f_attr));

    //set value
    strcat(f_ptr->f_name, _id.id_name);   
    strcat(f_ptr->f_attr, func_para);
    f_ptr->f_type = _type.symbol_type;
    f_ptr->f_pre = f_current;
    f_ptr->f_count = 0;
    
    f_current = f_ptr;
  
    if(f_header == NULL){
        f_header = f_current;
    }

    printf("*** function table, %s %d ***\n", f_ptr->f_name, f_ptr->f_type);
}

int func_return_checking(Value _type, Value _id, int flag){
    printf("in function_return_checking\n ");
    // declare & defined the same return type ?

    struct Func * f_ptr = f_current;
    while(f_ptr != NULL){
        // printf("hiii, %s, %s\n", f_ptr->f_name, _id.id_name);
        if(strcmp(f_ptr->f_name, _id.id_name) == 0){
            // printf("hiii222\n");
            if(_type.symbol_type != f_ptr->f_type ){
                if(strcmp(f_ptr->f_attr, func_para_2) != 0){
                    printf("different return type\n");
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "1. function return type is not the same\n");
                    strcat(error_msg, "| 2. function formal patameter is not the same");
                    error_flag = 1;
                }else{
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "function return type is not the same");
                    error_flag = 1;
                }

                return 1;   //find & different return type
            }

            printf("%s, %s = %s\n", f_ptr->f_name, f_ptr->f_attr, func_para_2);

            if(strcmp(f_ptr->f_attr, func_para_2) != 0){
                printf("different return type\n");
                //yyerror
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "function formal patameter is not the same");
                error_flag = 1;
            }

            if(f_ptr->f_count == flag){
                printf("redeclared\n");
                //yyerror
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared function ");
                strcat(error_msg, f_ptr->f_name);
                error_flag = 1;
            }
            return 2;   //find
        }
        f_ptr = f_ptr->f_pre;
    }
    return 0; //not find
}

void get_attribute(struct Entry * tmp){
    // get entry_attribute
    struct Entry *e_ptr = tmp;   //add function attribute
    struct Table *dump = table_dump;    //find parameter table
    struct Entry *e_dump = dump->entry_header; //find parameter entry

    memset(func_para, 0, sizeof(func_para));

    while(e_dump != NULL){
        if(strcmp(e_dump->kind, "parameter") == 0){
            //set function attribute to symbol table
            if(strlen(e_ptr->attribute) != 0){  //attribute is not empty
                strcat(e_ptr->attribute, ", ");
            }
            strcat(e_ptr->attribute, e_dump->type);

            //set function parameter type to jasmin
            if(strcmp(e_dump->type, "int") == 0 || strcmp(e_dump->type, "bool") == 0){
                strcat(func_para, "I");
            }else if(strcmp(e_dump->type, "float") == 0){
                strcat(func_para, "F");
            }else if(strcmp(e_dump->type, "string") == 0){
                strcat(func_para, "S");
            }else{
                printf("wrong function parameter , %s\n", e_dump->type);
            }
        }
        e_dump = e_dump->entry_next;
    }
    // printf("\nin get_attribute = %s\n", e_ptr->attribute);

    return;
}

void lookup_symbol(char* name, int flag) {
    // printf("\nin lookup_symbol\n");
    //check semetic_error 

    if(flag == 1){  //check if Redeclared variable
        struct Entry *e_ptr = table_current->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){  // Redeclared variable !!!
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared variable ");
                strcat(error_msg, name);
                error_flag = 1;
                break;
            }
            e_ptr = e_ptr->entry_next;
        }
    }else{      //check if Undeclared variable
        struct Table *ptr = table_current;
        while(ptr != NULL){
            struct Entry *e_ptr = ptr->entry_header;
            while(e_ptr != NULL){
                if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){ //declared variable
                    return;
                }
                /*
                printf("%-10d%-10s%-12s%-10s%-10d%-10s\n",
                   e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope, e_ptr->attribute);
                */
                e_ptr = e_ptr->entry_next;
            }
            ptr = ptr->pre;
        }
        // Undeclared variable !!!
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Undeclared variable ");
        strcat(error_msg, name);
        error_flag = 1;
    }
}

void lookup_function(char *name, int flag){
    // printf("\nin lookup_function\n");
    struct Table * ptr = table_current;

    if(flag == 1){   //Undeclared function
        while(ptr != NULL){
            struct Entry * e_ptr = ptr->entry_header;
            while(e_ptr != NULL){
                if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, name)== 0 ){
                    // printf("function declared !!!");
                    return;
                }
                e_ptr = e_ptr->entry_next;
            }
            ptr = ptr->pre;
        }

        // printf("\nno declared\n");
        // printf("num = %d, buf = %s\n", yylineno, buf);
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Undeclared function ");
        strcat(error_msg, name);
        error_flag = 1;
    }else{   //redeclared function
    /*
        struct Entry * e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, name)== 0){
                // redeclared
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared function ");
                strcat(error_msg, name); 
                
                if(flag == 3)
                    func_flag = 1;
                else
                    error_flag = 1;
        
                return;
            }
            e_ptr = e_ptr->entry_next;
        }  
    */
    /*
        struct Func *f_ptr = f_current;
        while(f_ptr != NULL){
            if(strcmp(f_ptr->f_name, name) == 0){
                // redeclared
                if(f_ptr->f_count == 1){
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "Redeclared function ");
                    strcat(error_msg, name);
                    error_flag = 1;
                }
                break;
            }
            f_ptr = f_ptr->f_pre;
        }  
        */

    }

}

void set_func_para(Value _type, int flag){
    if(flag == 0){ // init
        memset(func_para_2, 0, sizeof(func_para_2));
    }

    switch(_type.symbol_type){
        case I_Type:
            strcat(func_para_2, "I");
            break;
        case B_Type:
            strcat(func_para_2, "I");
            break;
        case F_Type:
            strcat(func_para_2, "F");
            break;
        case S_Type:
            strcat(func_para_2, "Ljava/lang/String;");
            break;
        default:
            printf(" in set_func_para\n");
            break;
    }
}

void dump_table(){
    // printf("\n----in dump_table, depth = %d, current = %p----\n", table_current->table_depth, table_current);
    table_dump = table_current;
    table_current = table_current->pre;
    table_depth --;
}
void dump_symbol() {
    // printf("\n----in dump_symbol\n");
    struct Table *ptr = table_dump;
    
    if(ptr->entry_header == NULL){ 
        //not entry, print nothing and drop the table
        // printf(", depth = %d, current = %p----\n", ptr->table_depth, ptr);
    }else{
        //print symbol_table && delete it
        printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
            "Index", "Name", "Kind", "Type", "Scope", "Attribute");
        
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            printf("%-10d%-10s%-12s%-10s%-10d",
            e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope);
            if(strlen(e_ptr->attribute) != 0)
                printf("%s", e_ptr->attribute);
            
            printf("\n");
            e_ptr = e_ptr->entry_next;
        }
        printf("\n");
    
    }
}

//code generation function
Value gencode_global_1(Value _type, Value _id, Value _expr, Value vval){
    printf("in gencode_1\n");
    fprintf(file, ".field public static");
    /* Example:
      a. only const
      b. no need to casting
    */
    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 1;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    
    switch (_type.symbol_type){
        case B_Type:  
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);  
            _val.id_i = _expr.i;
            break;
        case I_Type:
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);
            _val.id_i = _expr.i;
            break;
        case F_Type:
            sprintf(input_tmp, " %s F = %f\n", _id.id_name, _expr.f);
            _val.id_f = _expr.f;
            break;    
        case S_Type:
            sprintf(input_tmp, " %s Ljava/lang/String; = \"%s\"\n", _id.id_name, _expr.s);
            _val.id_s = _expr.s;
            break;
        default:
            printf("wrong input in type, gencode_global_1, %d\n",_type.symbol_type);
            break;
    }

    fprintf(file, "%s", input_tmp);
    printf("%s", input_tmp);
    return _val;
}

Value gencode_global_2(Value _type, Value _id, Value vval){
    printf("in gencode_2\n");
    fprintf(file, ".field public static");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 1;
    
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);
            _val.id_i = 0;  
            break;
        case I_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);
            _val.id_i = 0;
            break;
        case F_Type:
            sprintf(input_tmp, " %s F\n", _id.id_name);
            _val.id_i = 0.0;
            break;
        default:
            printf("wrong input in type, gencode_global_2, %d\n", _type.symbol_type);
            break;
    }

    fprintf(file, "%s", input_tmp);
    printf("%s", input_tmp);    
    // printf("%s, _id = %s, %d\n", input_tmp, _val.id_name, _val.id_symbol_type);
    return _val;
}

Value gencode_local_1(Value _type, Value _id, Value _expr, int index, Value vval){
    printf("in gencode_local_1\n");
    /* Example:
       a. int a = 5;        ldc const
       b. int a = b;        find b ID
       c. int a = 3 + 4;    is_arith
       d. int a = sqrt(d);  return what??
       e. int a = 2.0;      ldc & casting

       Exapmle: int d = 3;
       ldc 0
       istore 0
    */
    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    if(_expr.is_arith == 1){  //case c, d
        switch(_type.symbol_type){
            case I_Type:
                if(_expr.symbol_type == F_Type){
                    sprintf(input_tmp, "\tf2i\n\tistore %d\n", index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tistore %d\n", index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\ti2f\n\tfstore %d\n", index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tfstore %d\n", index);
                    _val.id_f = _expr.f;
                }
                break;
            default:
                printf("wrong input in type, gencode_local_1 1, %d\n", _type.symbol_type);
                break;
        }
    }else if(_expr.symbol_type == ID_Type){  //case b
        Value v1 = get_id_value(_expr);
        _expr = get_id_entry(_expr);
        gencode_iload(_expr);
        switch(_type.symbol_type){
            case I_Type:
                if(v1.symbol_type == F_Type){
                    sprintf(input_tmp, "\tf2i\n\tistore %d\n", index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tistore %d\n", index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\ti2f\n\tfstore %d\n", index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tfstore %d\n", index);
                    _val.id_f = _expr.f;
                }
                break;
            default:
                printf("wrong input in type, gencode_local_1 2, %d\n", _type.symbol_type);
                break;
        }              
    }else{ //case a, e
        switch (_type.symbol_type){
            case B_Type:
                sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
                _val.id_i = _expr.i; 
                break;
            case I_Type:
                if(_expr.symbol_type == F_Type){
                    sprintf(input_tmp, "\tldc %f\n\tf2i\n\tistore %d\n", _expr.f, index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\tldc %d\n\ti2f\n\tfstore %d\n", _expr.i, index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tldc %f\n\tfstore %d\n", _expr.f, index);
                    _val.id_f = _expr.f;
                }
                break;
            case S_Type:
                sprintf(input_tmp, "\tldc \"%s\"\n\tastore %d\n", _expr.s, index);
                _val.id_s = _expr.s;
                break;
            default:
                printf("wrong input in type, gencode_local_1 3, %d\n", _type.symbol_type);
                break;
        }
    }
    
    strcat(func_buf, input_tmp);
    printf("%s", input_tmp);
    return _val;
}

Value gencode_local_2(Value _type, Value _id, int index, Value vval){
    printf("in gencode_local_2\n");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    /*Example: int a; 
      a. initial value 0 
      b. no init empty string
    */
    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, "\tldc 0\nistore %d\n", index);
            _val.id_i = 0;
            break;
        case I_Type:
            sprintf(input_tmp, "\tldc 0\n\tistore %d\n", index);
            _val.id_i = 0;
            break;
        case F_Type:
            sprintf(input_tmp, "\tldc 0.0\n\tfstore %d\n", index);
            _val.id_f = 0.0;
            break;
        default:
            printf("wrong input in type, gencode_local_2, %d\n", _type.symbol_type);
            break;
    }

    strcat(func_buf, input_tmp);
    printf("%s", input_tmp);
    return _val;
}

Value gencode_parameter(Value _type, Value _id, int index){
    printf("in gencode_parameter\n");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    return _val;
}

void gencode_func(Value _type, Value _id){
    printf("in gencode_func\n");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    if(strcmp(_id.id_name, "main") == 0){   //if main function
        // printf(" ohhhh\n");
        fprintf(file, ".method public static main([Ljava/lang/String;)V\n");
        // printf(" ohhhh\n");
    }else{
        switch (_type.symbol_type){
            case B_Type:
                sprintf(input_tmp, ".method public static %s(%s)I\n", _id.id_name, func_para);  
                break;
            case I_Type:
                sprintf(input_tmp, ".method public static %s(%s)I\n", _id.id_name, func_para);
                break;
            case F_Type:
                sprintf(input_tmp, ".method public static %s(%s)F\n", _id.id_name, func_para);
                break;
            case V_Type:
                sprintf(input_tmp, ".method public static %s(%s)V\n", _id.id_name, func_para);
                break;
            default:
                printf("wrong input in type, gencode function\n");
                break;
        }    
        fprintf(file, "%s", input_tmp);
        printf("%s", input_tmp);
    }

    fprintf(file, ".limit stack 50\n.limit locals 50\n");
    fprintf(file, "%s", func_buf);
    fprintf(file, ".end method\n");

    printf("%s", ".limit stack 50\n.limit locals 50\n");
    printf("%s", func_buf);
    printf(".end method\n");

    memset(func_buf, 0, sizeof(func_buf));       
    return;
}

void gencode_return(Value v){
    printf("in gencode_return\n");
    /* Example: 
       a. return;
       b. return a;
       c. return 3;
       d. teturm a + 3;
       e. return foo(a);
       iload 0 / getstatic / is_arith ... <- get_id_value
       ireturn    
    */
    
    //special case
    if(v.symbol_type == T_Type){
        v.symbol_type = V_Type;
    }

    if(v.is_arith == 1){ //case d, e
        switch(v.symbol_type){
            case I_Type:
            case B_Type: 
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                strcat(func_buf, "\tfreturn\n");
                break;
            default:
                printf("wrong return type 1 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }else if(v.symbol_type == ID_Type){ //case b
        Value v1 = get_id_value(v);
        v = get_id_entry(v);
        gencode_iload(v);
        switch(v1.symbol_type){
            case I_Type:
            case B_Type:
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                strcat(func_buf, "\tfreturn\n");
                break;
            default:
                printf("wrong return type 2 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }else{ //case a, c
        switch(v.symbol_type){
            case I_Type:
            case B_Type:
                gencode_iload(v); 
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                gencode_iload(v);
                strcat(func_buf, "\tfreturn\n");
                break;
            case V_Type:
                strcat(func_buf, "\treturn\n");
                break;
            default:
                printf("wrong return type 3 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }
    return;
}

void gencode_print(Value v){ 
    printf("in gencode_print\n");
    /* Example: only print int, float, string variables and constants
       a. print(1);
       b. print("HELLO");
       c. print(a);

       * not test:
       print(a+b);  -->grammar can't handle
       print(TRUE); -->no print bool

       * todo
       1. put something on TOS
       2. getstatic java/lang/System/out Ljava/io/PrintStream; 
          swap
       3. invokevirtural java/io/PrintStream/println(I)V
    */

    Value tmp;
    if(v.symbol_type == ID_Type){
        tmp = get_id_value(v);
        v = get_id_entry(v);
    }else{
        tmp.symbol_type = v.symbol_type;
    }

    // todo step
    gencode_iload(v);
    strcat(func_buf, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n");
    switch(tmp.symbol_type){
        case I_Type:
        case B_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(I)V\n");
            break;
        case F_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(F)V\n");
            break;
        case S_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            break;
        default:
            printf("wrong case -- gencode_print, %d\n", tmp.symbol_type);
            break;
    }
    return;
}

//expression function
Value switch_mul_op(Value v1, Operator op, Value v2){
    printf("in switch_mul_op\n");
    
    switch (op){
        case MUL_OPT:
            return mul_arith(v1, v2);
        case DIV_OPT:
            return div_arith(v1, v2);
        case MOD_OPT:
            return mod_arith(v1, v2);
        default:
            printf("wrong case in mul_arith\n");
            break;
    }
}

Value switch_addition_op(Value v1, Operator op, Value v2){
    printf("in switch_addition_op\n");
    switch (op) {
        case ADD_OPT:
            return add_arith(v1, v2);
        case MINUS_OPT:
            return minus_arith(v1, v2);
        default:
            printf("wrong case in addition_op\n");
            break;
    }
}

Value switch_postfix_op(Value v1, Operator op){
    printf("in switch_postfix_op\n");
    Value tmp;
    tmp.symbol_type = I_Type;
    tmp.i = 1;

    switch (op){
        case INC_OPT:
            return add_arith(v1, tmp);
        case DEC_OPT:
            return minus_arith(v1, tmp);
        default:
            printf("wrong case in postfix_op\n");
            break;
    }
}

Value switch_assign_op(Value v1, Operator op, Value v2){
    printf("in switch_assign_op\n");
    // LHS_val = RHS_val
    Value RHS_val;
    Value LHS_val;

    //get LHS_val type, (v1 must be an ID)
    LHS_val = get_id_value(v1);
    v1 = get_id_entry(v1);

    if(op == ASSIGN_OPT){
        /* Example
            a. x = y + 3;
            b. x = y;
            c. x = 12;
        */
        if(v2.symbol_type == ID_Type){  //case b
            RHS_val = get_id_value(v2);
            v2 = get_id_entry(v2);
            gencode_iload(v2);
        }else if(v2.is_arith == 1){ // case a
            RHS_val = v2;
        }else{ //case c
            gencode_iload(v2);
            RHS_val = v2;
        }
    }else{
        switch (op){
            case ADD_ASSIGN_OPT:
                RHS_val = add_arith(v1, v2);
                break;
            case SUB_ASSIGN_OPT:
                RHS_val = minus_arith(v1, v2);
                break;
            case MUL_ASSIGN_OPT:
                RHS_val = mul_arith(v1, v2);
                break;
            case DIV_ASSIGN_OPT:
                RHS_val = div_arith(v1, v2);
                break;
            default:
                printf("wrong case -- assign_op, %d\n", op);
                break;
        }
    }

    //type casting
    if(LHS_val.symbol_type == I_Type && RHS_val.symbol_type == F_Type){
        strcat(func_buf, "\tf2i\n");
    }else if(LHS_val.symbol_type == F_Type && RHS_val.symbol_type == I_Type){
        strcat(func_buf, "\ti2f\n");
    }

    gencode_istore(v1);
    return LHS_val;  ///set RHS_val to LHS_val ????? cheating ???
}

Value switch_relation_op(Value A, Operator op, Value B){
    printf("in switch_relation_op\n");
    /* Example:
       a. x == y
       b. x != 3
       c. (2+x) > (x+y)
       d. 5 > 6
       *not to consider if x, y is different type
       *return 0/1
       * todo Example: a > b
        iload a           ---> get_id_value
        iload b           ---> get_id_value
        if_icmpgt label_1 ---> if_XXcmp & label
        **FALSE           ---> store in label_buf
        goto label_next
        label_1:
        **TRUE
        label_next:
        ...
    */

    if(A.is_arith == 0){
        A = get_id_entry(A);
        gencode_iload(A);
    }else if(B.is_arith == 0){
        B = get_id_entry(B);
        gencode_iload(B);
    }
    
    Value tmp;
    tmp.symbol_type = B_Type; 

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
   
    switch (op){
        case MORE_OPT: // >
            sprintf(input_tmp, "\tif_icmpgt label_%d\n", label_index);
            break;
        case LESS_OPT: // <
            sprintf(input_tmp, "\tif_icmplt label_%d\n", label_index);
            break;
        case GE_OPT: // >=
            sprintf(input_tmp, "\tif_icmpge label_%d\n", label_index);
            break;
        case LE_OPT: // <=
            sprintf(input_tmp, "\tif_icmple label_%d\n", label_index);
            break;
        case EQ_OPT: // ==
            sprintf(input_tmp, "\tif_icmpeq label_%d\n", label_index);
            break;
        case NE_OPT: // !=
            sprintf(input_tmp, "\tif_icmpne label_%d\n", label_index);
            break;
        default:
            printf("wrong case in relation_op\n");
            break;
    }

    strcat(func_buf, input_tmp);
    memset(input_tmp, 0, sizeof(input_tmp));

    int label_next = label_index + 1;
    sprintf(input_tmp, "\tiload FALSE\n\tgoto label_%d\n\tlabel_%d:\n\tiload TRUE\n\tlabel_%d:\n"
                     , label_next, label_index, label_next);
    strcat(func_buf, input_tmp);

    label_index = label_next + 1;
    return tmp;
}

//arithmetic function
Value mul_arith(Value A, Value B){
    printf("in mul_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);
    
    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)*(v2.i);
        strcat(func_buf, "\timul\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)*(v2.f);
        strcat(func_buf, "\tfmul\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)*(v2.i);
        strcat(func_buf, "\tfmul\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)*(v2.f);
        strcat(func_buf, "\tfmul\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value div_arith(Value A, Value B){
    printf("in div_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    //cannot divide by zero
    if((v2.symbol_type == I_Type && v2.i == 0)
        || (v2.symbol_type == F_Type && v2.f == 0.0)){
        printf("cannot divide by zero!!\n ");
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Arithmetic errors - cannot divided by zero");
        error_flag = 1;
        return A;
    }

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)/(v2.i);
        strcat(func_buf, "\tidiv\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)/(v2.f);
        strcat(func_buf, "\tfdiv\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)/(v2.i);
        strcat(func_buf, "\tfdiv\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)/(v2.f);
        strcat(func_buf, "\tfdiv\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value mod_arith(Value A, Value B){
    printf("in mod_arith\n");

    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)%(v2.i);
        strcat(func_buf, "\tirem\n");
    }else{
        printf("wrong -- only int can mod\n");
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Arithmetic errors - Modulo operator only for interger");
        error_flag = 1;
    }

    v_tmp.is_arith = 1;
    
    return A;
}

Value add_arith(Value A, Value B){
    printf("in add_arith\n");
    // printf("%d, %d, %s,,,%d\n", A.symbol_type, A.id_symbol_type, A.id_name, B.symbol_type);
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    // printf("%d, %d, %s,,,%d\n", A.symbol_type, A.id_symbol_type, A.id_name, B.symbol_type);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)+(v2.i);
        strcat(func_buf, "\tiadd\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)+(v2.f);
        strcat(func_buf, "\tfadd\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)+(v2.i);
        strcat(func_buf, "\tfadd\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)+(v2.f);
        strcat(func_buf, "\tfadd\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value minus_arith(Value A, Value B){
    printf("in minus_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)-(v2.i);
        strcat(func_buf, "\tisub\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)-(v2.f);
        strcat(func_buf, "\tfsub\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)-(v2.i);
        strcat(func_buf, "\tfsub\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)-(v2.f);
        strcat(func_buf, "\tfsub\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value get_id_value(Value v, int flag){

    if(v.symbol_type != ID_Type)
        return v;

    struct Table *ptr = table_current;
    Value _val;
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ 
                //declared variable && find id & gencode 
                Value tmp = e_ptr->entry_val;
                // set _val
                switch(tmp.id_symbol_type){
                    case I_Type:
                    case B_Type:
                        _val.i = tmp.id_i;
                        break;
                    case F_Type:
                        _val.f = tmp.id_f;
                        break;
                    case S_Type:
                        _val.s = tmp.id_s;
                        break;
                    default:
                        printf("wrong id type -- get_id_value\n");
                        break;
                }
                _val.symbol_type = tmp.id_symbol_type;
                return _val;
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }
    printf("Not Find ID -- get_id_value !!!!\n");
    return _val;
}

Value get_id_entry(Value v){

    if(v.symbol_type != ID_Type)
        return v;

    struct Table *ptr = table_current;
    Value _val;
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ 
                //declared variable && find id & gencode 
                _val = e_ptr->entry_val;
                _val.symbol_type = ID_Type;
                _val.is_arith = v.is_arith;
                return _val;    
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }
    printf("Not Find ID -- get_id_entry !!!!\n");
    return v;
}

void gencode_iload(Value v){
    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    // printf("----type %d\n", v.symbol_type);

    if(v.symbol_type == ID_Type){
        // printf(" ==== type %d\n", v.id_symbol_type);
        if(v.is_global == 1){
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s I\n", v.id_name);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s F\n", v.id_name);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s Ljava/lang/String;\n", v.id_name);
                    break;
                default:
                    printf("wrong id type -- iload global\n");
                    break;
            }
        }else{
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tiload %d\n", v.id_index);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tfload %d\n", v.id_index);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\taload %d\n", v.id_index);
                    break;
                default:
                    printf("wrong id type -- iload loacl\n");
                    break;
            }
        }
    }else{  // the const
        switch(v.symbol_type){
            case I_Type:
            case B_Type:
                sprintf(input_tmp, "\tldc %d\n", v.i);
                break;
            case F_Type:
                sprintf(input_tmp, "\tldc %f\n", v.f);
                break;
            case S_Type:
                sprintf(input_tmp, "\tldc \"%s\"\n", v.s);
                break;
            default:
                printf("wrong id type -- iload const\n");
                break;
        }
    }

    strcat(func_buf, input_tmp);
    return;
}

void gencode_istore (Value v){
    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    
    if(v.symbol_type == ID_Type){
        if(v.is_global == 1){
           switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s I\n", v.id_name);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s F\n", v.id_name);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s Ljava/lang/String;\n", v.id_name);
                    break;
                default:
                    printf("wrong id type -- gencode_istore, %d\n", v.id_symbol_type );
                    break;
            }
        }else{
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tistore %d\n", v.id_index);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tfstore %d\n", v.id_index);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tastore %d\n", v.id_index);
                    break;
                default:
                    printf("wrong id type -- gencode_istore, %d\n", v.id_symbol_type);
                    break;
            }
        }
    }else{  // the const
        printf("store in const ??? -- gencode_istore\n");
    }

    strcat(func_buf, input_tmp);
    return;
}

void gencode_if_arith(Value A, Value B, int flag){
    if(A.is_arith == 0 && B.is_arith == 0){
        switch(flag){
            case 1:
                gencode_iload(A);
                gencode_iload(B);
                break;
            case 2:
                gencode_iload(A);
                strcat(func_buf, "\ti2f\n");
                gencode_iload(B);
                break;
            case 3:
                gencode_iload(A);
                gencode_iload(B);
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 1, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 1 && B.is_arith == 0){
        switch(flag){
            case 1:
                gencode_iload(B);
                break;
            case 2:
                strcat(func_buf, "\ti2f\n");
                gencode_iload(B);
                break;
            case 3:
                gencode_iload(B);
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 2, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 0 && B.is_arith == 1){
        switch(flag){
            case 1:
                gencode_iload(A);
                break;
            case 2:
                gencode_iload(A);
                strcat(func_buf, "\ti2f\n");
                break;
            case 3:
                strcat(func_buf, "\ti2f\n");
                gencode_iload(A);
                break;
            default:
                printf("wrong in -- gencode_if_arith 3, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 1 && B.is_arith == 1){
        switch(flag){
            case 1:
                break;
            case 2:
                printf("in speeeeeical case\n");
                strcat(func_buf, "\tswap\n\ti2f\n");
                break;
            case 3:
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 4, %d\n", flag);
                break;
        }   
    }else{
        printf("error in -- gencode_if_arith\n");
    }
    return;
}

Value gencode_funcall(Value _val){     
    printf("in gencode_funcall\n");
    /* Example: a = foo(6);
       ldc 6
       invokestatic compiler_hw3/foo(I)I
       istore 0

       * todo
       1. checking input parameter type
       2. generate function call code (invokestatic)
    */
    char input_tmp[200];
    memset(input_tmp, 0, sizeof(input_tmp));
    Value v;

    //cut attribute
    char *delim = ", ";
    char *token;
    char str[50];
    char para_tmp[50];
    memset(str, 0, sizeof(str));
    memset(para_tmp, 0, sizeof(para_tmp));

    //creat function parameter array from symbol table
    Symbol_type tmp[10];
    int tmp_index = 0;
       

    struct Entry *e_ptr = table_header->entry_header;

    while(e_ptr != NULL){
        if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, _val .id_name) == 0){ //declared variable
            //find attribute & cut token to make tmp[]
            strcat(str, e_ptr->attribute);
            token = strtok(str, delim);
            while (token != NULL)
            {
                if(strcmp(token, "int") == 0){
                    tmp[tmp_index++] = I_Type;
                    strcat(para_tmp, "I");
                }else if(strcmp(token, "float") == 0){
                    tmp[tmp_index++] = F_Type;
                    strcat(para_tmp, "F");
                }else if(strcmp(token, "string") == 0){
                    tmp[tmp_index++] = S_Type;
                    strcat(para_tmp, "Ljava/lang/String;");
                }else if(strcmp(token, "bool") == 0){
                    tmp[tmp_index++] = B_Type;
                    strcat(para_tmp, "I");
                }else{
                    printf("wrong !!!\n");
                }
                token = strtok (NULL, delim);
            } 

            //get function type & gencode
            if(strcmp(e_ptr->type, "int") == 0 || strcmp(e_ptr->type, "bool") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)I\n", e_ptr->name, para_tmp);
                v.symbol_type = I_Type;
            }else if(strcmp(e_ptr->type, "float") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)F\n", e_ptr->name, para_tmp);
                v.symbol_type = F_Type;
            }else if(strcmp(e_ptr->type, "void") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)V\n", e_ptr->name, para_tmp);
                v.symbol_type = V_Type;
            }else{
                printf("wrong !!!\n");
            }
            break;
        }
        e_ptr = e_ptr->entry_next;
    }

    //is same # of parameter ?
    if(tmp_index != func_input_num){
        printf("different index num %d, %d\n", tmp_index, func_input_num);
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "function formal parameter is not the same");
        error_flag = 1;
    }

    //type casting
    Symbol_type _type;
    for(int i=0; i<tmp_index; i++){
        if(func_para_type[i].symbol_type == ID_Type){
            _type = func_para_type[i].id_symbol_type;
        }else{
            _type = func_para_type[i].symbol_type;
        }

        if(_type != tmp[i]){
            printf("error is different inptut type\n");
            //yyerror
            memset(error_msg, 0, sizeof(error_msg));
            strcat(error_msg, "function formal parameter is not the same");
            error_flag = 1;
        }

        //gencode
        gencode_iload(func_para_type[i]);
    }

    strcat(func_buf, input_tmp);
    func_input_num = 0;
    v.is_arith = 1;
    return v;
}