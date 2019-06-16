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

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex
extern char syntax_buf[256];
extern int error_flag; //1.redefined 2.undefined
extern int syntax_flag;
extern char error_msg[256];
extern int dump_flag;
extern void yyerror(char *s);

int func_flag = 0;
char func_buf[500]; //buf for jasmin function
char func_para[20]; //buf for function parameter
int func_input_num = 0;     // index of func_input[]
Symbol_type func_input[10]; //buf for function input parameter
Symbol_type return_type;    // record function return type;
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
Value switch_logic_op();
Value get_id_value();

//arithmetic
Value mul_arith(Value v1, Value v2);
Value div_arith(Value v1, Value v2);
Value mod_arith(Value v1, Value v2);
Value add_arith(Value v1, Value v2);
Value minus_arith(Value v1, Value v2);

//error detecting && tool
Value lookup_id();
Value lookup_id_istore();
Symbol_type lookup_id_return();
Symbol_type lookup_id_type();
void input_checking();

//code generation function
void gencode_global_1();
void gencode_global_2();
void gencode_local_1();
void gencode_local_2();
void gencode_func();
void gencode_print();
void gencode_return();

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
%token TRUE FALSE RETURN 
%token PRINT 
%token IF ELSE FOR WHILE 
%token SEMICOLON QUOTA 

/* Token with return, which need to sepcify type */
%token <val> I_CONST
%token <val> F_CONST
%token <val> STRING_CONST 
%token <val> ID


%type <val> type initializer 
%type <val> expression logic_expr comparison_expr add_expr mul_expr 
%type <val> postfix_expr parenthesis_expr assign_expression 
%type <op>  postfix_op mul_op relation_op addition_op logic_op assign_op 

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
    : selection_statement 
    | while_statement 
    | expression SEMICOLON
    | return_statement 
;

selection_statement
    : IF { create_symbol(); }
      '(' expression ')' compound_stat
    | /* selection_statement */
      ELSE { create_symbol(); } compound_stat
    | /* selection_statement */
      ELSE IF{ create_symbol(); }
      '(' expression ')' compound_stat
;

while_statement
    : WHILE                                 
      { create_symbol(); }
     '(' expression ')' compound_stat 
;


expression
    : logic_expr {}
    | assign_expression {}
;

logic_expr
    : comparison_expr                       {}
    | logic_expr logic_op comparison_expr   { $$ = switch_logic_op($1, $2, $3); }
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
    : initializer {}                           /* for constant */
    | ID { lookup_function($1.id_name, 1); }   /* for function */
      declarator2 { input_checking($1); } 
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

logic_op
    : AND_OP { $$ = AND_OPT; }
    | OR_OP  { $$ = OR_OPT; }
    | '!'    { $$ = NOT_OPT; }
;

assign_expression
    : expression assign_op expression { switch_assign_op($1, $2, $3); }
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
    : type ID declarator compound_stat  { lookup_function($2.id_name, 3); 
                                          if(func_flag != 1){
                                              insert_symbol($1, $2, type_f, trash_var);
                                          }
                                          func_flag = 0;
                                        }
    | type ID declarator SEMICOLON  { dump_table(); 
                                      lookup_function($2.id_name, 2); 
                                      if(error_flag != 1){
                                        insert_symbol($1, $2, type_f, trash_var);
                                      }
                                    }
;

declarator
    : '(' { create_symbol(); }
      identifier_list ')'  
    | '(' { create_symbol(); }
      ')'
;

identifier_list
    : identifier_list ',' type ID 
        { insert_symbol($3, $4, type_p, trash_var); }
    | type ID
        { insert_symbol($1, $2, type_p, trash_var); }
;

declarator2
    : '(' identifier_list2 ')' 
    | '(' ')'
;

identifier_list2
    : identifier_list2 ',' expression   { if($3.symbol_type == ID_Type)
                                            func_input[func_input_num++] = lookup_id_type($3); 
                                          else
                                            func_input[func_input_num++] = $3.symbol_type; 

                                         //load variable
                                          get_id_value($3);
                                        }
    | expression    { if($1.symbol_type == ID_Type)
                        func_input[func_input_num++] = lookup_id_type($1); 
                      else
                        func_input[func_input_num++] = $1.symbol_type; 

                      //load variable
                      get_id_value($1);
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

void insert_symbol(Value v1, Value v2, char* k, Value v3) {
   
    struct Table *ptr = table_current; 
    struct Entry *e_ptr = malloc(sizeof(struct Entry));

    Symbol_type t = v1.symbol_type;
    char *n = v2.id_name;
    
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

    // strcpy(e_ptr->type, t);
    strcpy(e_ptr->kind, k);
    strcpy(e_ptr->name, n);  
    // e_ptr->type = t;

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
        case ID_Type:
            strcpy(e_ptr->type, "ID");
            break;
        case B_Type:
            strcpy(e_ptr->type, "bool");
            break;
        default:
            printf("wrong input in type");
            break;
    }

    if(strcmp(k, "function") == 0){
        get_attribute(e_ptr);
        gencode_func(v1, v2);
    }else if(strcmp(k, "variable") == 0){      //paremeter and variable, generate to jasim 
        //set e_ptr->entry_val
        // if(strcmp(e_ptr->type, "int") == 0){
        //     e_ptr->entry_val.symbol_type = I_Type;
        //     e_ptr->entry_val.i = 
        // }else if(strcmp(e_ptr->type, "float") == 0){
        //     e_ptr->entry_val.symbol_type = F_Type;
        // }else if(strcmp(e_ptr->type, "string") == 0){
        //     e_ptr->entry_val.symbol_type = S_Type;
        // }else if(strcmp(e_ptr->type, "bool") == 0){
        //     e_ptr->entry_val.symbol_type = B_Type;
        // }else{
        //     printf("the wrong e_ptr->type\n");
        // }

        if(table_current->table_depth == 0){
            if(v3.symbol_type != 6)     //int a = 3;
                gencode_global_1(v1, v2, v3);
            else                        //int a;
                gencode_global_2(v1, v2);
        }else{
            if(v3.symbol_type != 6)     //int a = 3;
                gencode_local_1(v1, v2, v3, e_ptr->index);
            else                        //int a;
                gencode_local_2(v1, v2, e_ptr->index);
        }
    }
 
    printf("\n++++%d, %s, %s, %s, %d++++\n", e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope);
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
void gencode_global_1(Value _type, Value _id, Value _expr){

    printf("in gencode_1\n");
    fprintf(file, ".field public static");
    printf(".field public static");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    
    switch (_type.symbol_type){
        case B_Type:  
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);  
            break;
        case I_Type:
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);
            break;
        case F_Type:
            sprintf(input_tmp, " %s F = %f\n", _id.id_name, _expr.f);
            break;    
        case S_Type:
            sprintf(input_tmp, " %s Ljava/lang/String; = \"%s\"\n", _id.id_name, _expr.s);
            break;
        default:
            printf("wrong input in type\n");
            break;
    }

    fprintf(file, "%s", input_tmp);
    printf("%s", input_tmp);

}

void gencode_global_2(Value _type, Value _id){
    printf("in gencode_2\n");
    fprintf(file, ".field public static");
    printf(".field public static");

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);  
            break;
        case I_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);
            break;
        case F_Type:
            sprintf(input_tmp, " %s F\n", _id.id_name);
            break;
        case S_Type:
            sprintf(input_tmp, " %s Ljava/lang/String;\n", _id.id_name);
            break;
        default:
            printf("wrong input in type\n");
            break;
    }

    fprintf(file, "%s", input_tmp);
    printf("%s", input_tmp);

}

void gencode_local_1(Value _type, Value _id, Value _expr, int index){
    printf("in gencode_local_1\n");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    /* Exapmle: int d = 3;
        ldc 0
        istore 0
    */
    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
            break;
        case I_Type:
            sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
            break;
        case F_Type:
            sprintf(input_tmp, "\tldc %f\n\tistore %d\n", _expr.f, index);
            break;
        case S_Type:
            sprintf(input_tmp, "\tldc %s\n\tistore %d\n", _expr.s, index);
            break;
        default:
            printf("wrong input in type\n");
            break;
    }

    strcat(func_buf, input_tmp);
    return;
}

void gencode_local_2(Value _type, Value _id, int index){
    printf("in gencode_local_2\n");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    //int a; initial value 0 & empty string
    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, "\tldc 0\nistore %d\n", index);
            break;
        case I_Type:
            sprintf(input_tmp, "\tldc 0\n\tistore %d\n", index);
            break;
        case F_Type:
            sprintf(input_tmp, "\tldc 0.0\n\tistore %d\n", index);
            break;
        case S_Type:
            sprintf(input_tmp, "\tldc \"\"\n\tistore %d\n", index);
            break;
        default:
            printf("wrong input in type\n");
            break;
    }

    strcat(func_buf, input_tmp);
    return;

}

void gencode_func(Value _type, Value _id){
    printf("in gencode_func\n");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    //return_type_checking
    if( _type.symbol_type != return_type){
        printf("return type error !!!!\n");
        //yyerror
    }

    if(strcmp(_id.id_name, "main") == 0){   //if main function
        fprintf(file, ".method public static main([Ljava/lang/String;)V\n");
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
                printf("wrong input in type\n");
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
    
    return_type = v.symbol_type;
    get_id_value(v);

    switch(v.symbol_type){
        case I_Type:
        case B_Type:
            strcat(func_buf, "\tireturn\n");
            break;
        case F_Type:
            strcat(func_buf, "\tfreturn\n");
            break;
        case T_Type:
            strcat(func_buf, "\treturn\n");
            break;
        case ID_Type:
            return_type =  lookup_id_return(v);  
        default:
            printf("wrong return type\n");
            break;
    }
    return;
}

void gencode_print(Value v){ // only print int, float, string variables and constants
    printf("in gencode_print\n");
    //1. getstatic
    //2. put something on TOS
    //3. invokevirtural
    Value tmp = lookup_id(v);
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
            printf("wrong case in gencode_print\n");
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
            // return mod_arirh(v1, v2);
            printf("in MOD_arith\n");
            break;
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
    Value tmp;
    //istore in global ???????????????????

    switch (op){
        case ADD_ASSIGN_OPT:
            tmp = add_arith(v1, v2);
            break;
        case SUB_ASSIGN_OPT:
            tmp = minus_arith(v1, v2);
            break;
        case MUL_ASSIGN_OPT:
            tmp = mul_arith(v1, v2);
            break;
        case DIV_ASSIGN_OPT:
            tmp = div_arith(v1, v2);
            break;
        case ASSIGN_OPT: // b = a + 2;
            tmp = v2;
            break;
        default:
            printf("wrong case in assign_op\n");
            break;
    }

    lookup_id_istore(v1);
    return tmp;
}

Value switch_relation_op(Value v1, Operator op, Value v2){
    printf("in switch_relation_op\n");
    Value tmp;
    tmp.symbol_type = I_Type; // ??????B_Type

    switch (op){
        case MORE_OPT:
            tmp.i = (v1.f > v2.f);
            return tmp;
        case LESS_OPT:
            tmp.i = (v1.f < v2.f);
            return tmp;
        case GE_OPT:
            tmp.i = (v1.f >= v2.f);
            return tmp;
        case LE_OPT:
            tmp.i = (v1.f <= v2.f);
            return tmp;
        case EQ_OPT:
            tmp.i = (v1.f == v2.f);
            return tmp;
        case NE_OPT:
            tmp.i = (v1.f != v2.f);
            return tmp;
        default:
            printf("wrong case in relation_op\n");
            break;
    }
}

Value switch_logic_op(Value v1, Operator op, Value v2){
    printf("in switch_logic_op\n");
    Value tmp;
    tmp.symbol_type = I_Type; // ??????B_Type

    switch (op){
        case AND_OPT:
            tmp.i = (v1.f && v2.f);
            return tmp;
        case OR_OPT:
            tmp.i = (v1.f || v2.f);
            return tmp;
        case NOT_OPT: //??????????????????? !a
            tmp.i = (v1.f >= v2.f);
            return tmp;
        default:
            printf("wrong case in logic_op\n");
            break;
    }
}



//arithmetic function
Value mul_arith(Value A, Value B){
    printf("in mul_arith\n");
    Value v1 = get_id_value(A);
    Value v2 = get_id_value(B);
    Value v_tmp;
    // memset(v_tmp, 0, sizeof(v_tmp));

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){
        v_tmp.symbol_type = I_Type;
        strcat(func_buf, "\timul\n");
        // v_tmp.i = (v1.i)*(v2.i);
    }else{
        v_tmp.symbol_type = F_Type;
        strcat(func_buf, "\tfmul\n");

        // v_tmp.f = (v1.f)*(v2.f);
    }
    return v_tmp;
}

Value div_arith(Value A, Value B){
    printf("in div_arith\n");
    Value v1 = get_id_value(A);
    Value v2 = get_id_value(B);
    Value v_tmp;
    /*
    if(v2.i == 0){
        printf("v2 cannot be zero !!!");
        //yyerror;
        return v1;
    }
    */
    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){
        v_tmp.symbol_type = I_Type;
        strcat(func_buf, "\tidiv\n");

        // v_tmp.i = (v1.i)/(v2.i);
    }else{
        v_tmp.symbol_type = F_Type;
        // v_tmp.f = (v1.f)/(v2.f);
    }
    return v_tmp;
}

Value mod_arith(Value A, Value B){
    printf("in mod_arith\n");
    Value v1 = get_id_value(A);
    Value v2 = get_id_value(B);
    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){
        v_tmp.symbol_type = I_Type;
        strcat(func_buf, "\tirem\n");

        // v_tmp.i = (v1.i)%(v2.i);
        return v_tmp;
    }else{
        printf("v1 v2 need to be I_Type\n");
        //yyerror();
       v_tmp = v1;
    }
    return v_tmp;
}

Value add_arith(Value A, Value B){
    printf("in add_arith\n");
    Value v1 = get_id_value(A);
    Value v2 = get_id_value(B);
    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){
        v_tmp.symbol_type = I_Type;
        strcat(func_buf, "\tiadd\n");

        // v_tmp.i = (v1.i)+(v2.i);
    }else{
        v_tmp.symbol_type = F_Type;
        strcat(func_buf, "\tfadd\n");

        // v_tmp.f = (v1.f)+(v2.f);
    }
    return v_tmp;

}

Value minus_arith(Value A, Value B){
    printf("in minus_arith\n");
    Value v1 = get_id_value(A);
    Value v2 = get_id_value(B);
    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){
        v_tmp.symbol_type = I_Type;
        strcat(func_buf, "\tisub\n");
        // v_tmp.i = (v1.i)-(v2.i);
    }else{
        v_tmp.symbol_type = F_Type;
        strcat(func_buf, "\tfsub\n");
        // v_tmp.f = (v1.f)-(v2.f);
    }
    return v_tmp;
}

Value get_id_value(Value v){
    Value tmp;
    if(v.symbol_type == ID_Type){ //is id
        return lookup_id(v);
    }else{
        char input_tmp[100];
        memset(input_tmp, 0, sizeof(input_tmp));
        switch (v.symbol_type){
            case B_Type:
                sprintf(input_tmp, "\tldc %d\n", v.i);
                break;
            case I_Type:
                sprintf(input_tmp, "\tldc %d\n", v.i);
                break;
            case F_Type:
                sprintf(input_tmp, "\tldc %f\n", v.f);
                break;
            case S_Type:
                sprintf(input_tmp, "\tldc \"%s\"\n", v.s);
                break;
            default:
                printf("wrong input in type\n");
                break;
        }

        strcat(func_buf, input_tmp);
        return v;
    }
}

Value lookup_id(Value v){
    struct Table *ptr = table_current;
    char *name = v.id_name;
    Value tmp;

    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){ //declared variable
                //find id & gencode 
                if(ptr->table_depth == 0){ 
                    //global variable
                    if(strcmp(e_ptr->type, "int") == 0 || strcmp(e_ptr->type, "bool") == 0){
                        sprintf(input_tmp, "\tgetstatic compiler_hw3/%s I\n", e_ptr->name);
                        tmp.symbol_type = I_Type;
                    }else if(strcmp(e_ptr->type, "float") == 0){
                        sprintf(input_tmp, "\tgetstatic compiler_hw3/%s F\n", e_ptr->name);
                        tmp.symbol_type = F_Type;
                    }else if(strcmp(e_ptr->type, "string") == 0){
                        sprintf(input_tmp, "\tgetstatic compiler_hw3/%s Ljava/lang/String;\n", e_ptr->name);
                        tmp.symbol_type = S_Type;
                    }else if(strcmp(e_ptr->type, "bool") == 0){
                        sprintf(input_tmp, "\tgetstatic compiler_hw3/%s I\n", e_ptr->name);
                        tmp.symbol_type = B_Type;
                    }else{
                        printf("the wrong e_ptr->type global\n");
                    }
                }else{
                    //local variable
                    sprintf(input_tmp, "\tiload %d\n", e_ptr->index);
                    printf("\tiload %d\n", e_ptr->index);
                    if(strcmp(e_ptr->type, "int") == 0){
                        tmp.symbol_type = I_Type;
                    }else if(strcmp(e_ptr->type, "float") == 0){
                        tmp.symbol_type = F_Type;
                    }else if(strcmp(e_ptr->type, "string") == 0){
                        tmp.symbol_type = S_Type;
                    }else if(strcmp(e_ptr->type, "bool") == 0){
                        tmp.symbol_type = B_Type;
                    }else{
                        printf("the wrong e_ptr->type loacl\n");
                    }
                }

                strcat(func_buf, input_tmp);
                return tmp;
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }

    printf("Not Find ID -- lookup_id !!!!\n");
    return tmp;

}


Value lookup_id_istore(Value v){  // nothing to return, Void ???
    struct Table *ptr = table_current;
    char *name = v.id_name;
    Value tmp;

    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){ //declared variable
                //find id & gencode 
                // if(ptr->table_depth == 0){ 
                //     //global variable
                //     if(strcmp(e_ptr->type, "int") == 0){
                //         sprintf(input_tmp, "\tgetstatic compiler_hw3/%s I\n", e_ptr->name);
                //         printf("\tgetstatic compiler_hw3/%s I\n", e_ptr->name);
                //         tmp.symbol_type = I_Type;
                //     }else if(strcmp(e_ptr->type, "float") == 0){
                //         sprintf(input_tmp, "\tgetstatic compiler_hw3/%s F\n", e_ptr->name);
                //         printf("\tgetstatic compiler_hw3/%s F\n", e_ptr->name);
                //         tmp.symbol_type = F_Type;
                //     }else if(strcmp(e_ptr->type, "string") == 0){
                //         sprintf(input_tmp, "\tgetstatic compiler_hw3/%s S\n", e_ptr->name);
                //         printf("\tgetstatic compiler_hw3/%s S\n", e_ptr->name);
                //         tmp.symbol_type = S_Type;
                //     }else if(strcmp(e_ptr->type, "bool") == 0){
                //         sprintf(input_tmp, "\tgetstatic compiler_hw3/%s Z\n", e_ptr->name);
                //         printf("\tgetstatic compiler_hw3/%s Z\n", e_ptr->name);
                //         tmp.symbol_type = B_Type;
                //     }else{
                //         printf("the wrong e_ptr->type global\n");
                //     }
                // }else{
                    //local variable
                    sprintf(input_tmp, "\tistore %d\n", e_ptr->index);
                    printf("\tistore %d\n", e_ptr->index);
                    // if(strcmp(e_ptr->type, "int") == 0){
                    //     tmp.symbol_type = I_Type;
                    // }else if(strcmp(e_ptr->type, "float") == 0){
                    //     tmp.symbol_type = F_Type;
                    // }else if(strcmp(e_ptr->type, "string") == 0){
                    //     tmp.symbol_type = S_Type;
                    // }else if(strcmp(e_ptr->type, "bool") == 0){
                    //     tmp.symbol_type = B_Type;
                    // }else{
                    //     printf("the wrong e_ptr->type loacl\n");
                    // }
                // }

                strcat(func_buf, input_tmp);
                return tmp;
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }
    printf("Not Find ID -- loojup_id_istore !!!!\n");
    return tmp;
}


Symbol_type lookup_id_return(Value v){
    printf("in lookup_id_return\n");
    struct Table *ptr = table_current;

    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ //declared variable
                //find id & gencode 
                if(strcmp(e_ptr->type, "int") == 0){
                    strcat(func_buf, "\tireturn\n");
                    return I_Type;
                }else if(strcmp(e_ptr->type, "float") == 0){
                    strcat(func_buf, "\tfreturn\n");
                    return F_Type;
                }else if(strcmp(e_ptr->type, "bool") == 0){
                    strcat(func_buf, "\treturn\n");
                    return B_Type;
                }else{
                    printf("the wrong e_ptr->type loacl\n");
                }
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }

    printf("Not Find ID -- lookup_id_return !!!!\n");
    return T_Type;

}

Symbol_type lookup_id_type(Value v){
    printf("in lookup_id_type\n");
    struct Table *ptr = table_current;

    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ //declared variable
                //find id & gencode 
                
                if(strcmp(e_ptr->type, "int") == 0){
                    return I_Type;
                }else if(strcmp(e_ptr->type, "float") == 0){
                    return F_Type;
                }else if(strcmp(e_ptr->type, "bool") == 0){
                    return B_Type;
                }else if(strcmp(e_ptr->type, "string") == 0){
                    return S_Type;
                }else{
                    printf("the wrong e_ptr->type local\n");
                }
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }

    printf("Not Find ID -- lookup_id_type !!!!\n");
    return T_Type;
}

//error detecting
void input_checking(Value v){     //input parameter checking & gencode function call (invokestatic)
    printf("in input_checking\n");
    struct Entry *e_ptr = table_header->entry_header;

    //cut attribute
    char *delim = ", ";
    char *token;
    char str[50];
    memset(str, 0, sizeof(str));

    //creat function parameter array from symbol table
    Symbol_type tmp[10];
    int tmp_index = 0;

    //gencode for attribute
    char input_tmp[100];
    char attrt_tmp[50];
    memset(input_tmp, 0, sizeof(input_tmp));
    memset(attrt_tmp, 0, sizeof(attrt_tmp));

    while(e_ptr != NULL){
        if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, v.id_name) == 0){ //declared variable
            //find id & gencode 
            //if different ->casting or error
            strcat(str, e_ptr->attribute);
            token = strtok(str, delim);
            while (token != NULL)
            {
                if(strcmp(token, "int") == 0){
                    tmp[tmp_index++] = I_Type;
                    strcat(attrt_tmp, "I");
                }else if(strcmp(token, "float") == 0){
                    tmp[tmp_index++] = F_Type;
                    strcat(attrt_tmp, "F");
                }else if(strcmp(token, "string") == 0){
                    tmp[tmp_index++] = S_Type;
                    strcat(attrt_tmp, "S");
                }else if(strcmp(token, "bool") == 0){
                    tmp[tmp_index++] = B_Type;
                    strcat(attrt_tmp, "I");
                }else{
                    printf("wrong !!!\n");
                }

                token = strtok (NULL, delim);
            } 

            //get function type 
            if(strcmp(e_ptr->type, "int") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)I\n", e_ptr->name, attrt_tmp);
            }else if(strcmp(e_ptr->type, "float") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)F\n", e_ptr->name, attrt_tmp);
            }else if(strcmp(e_ptr->type, "void") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)V\n", e_ptr->name, attrt_tmp);
            }else if(strcmp(e_ptr->type, "bool") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)I\n", e_ptr->name, attrt_tmp);
            }else{
                printf("wrong !!!\n");
            }


            strcat(func_buf, input_tmp);
            break;
        }
        e_ptr = e_ptr->entry_next;
    }

    if(tmp_index != func_input_num){
        printf("different index num %d, %d\n", tmp_index, func_input_num);
        //yyerror
    }

    for(int i=0; i<tmp_index; i++){
        if(func_input[i] != tmp[i]){
            printf("different input type!!!\n");
            //yyerror
        }
    }

    func_input_num = 0;
    return;
}