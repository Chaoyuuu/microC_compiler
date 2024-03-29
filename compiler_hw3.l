/* Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "y.tab.h"	/* header file generated by bison */
#define BUF_SIZE 256

extern YYSTYPE yylval; //YYSTYPE
extern void yyerror(char *s);
extern void dump_symbol();

char buf[BUF_SIZE];
char error_msg[BUF_SIZE];
char syntax_buf[BUF_SIZE];

/* This macro is used to record code line */
#define CONCAT { strncat(buf, yytext, BUF_SIZE - strlen(buf) - 1); }

int line_num = 1;
int error_flag = 0;
int syntax_flag = 0;
int dump_flag = 0;

%}

/* Define regular expression label */
digit	  	[0-9]
letter		[a-zA-Z]
integer   {digit}+
float     {digit}+"."{digit}+
id			  {letter}+({letter}|{digit})*

%option yylineno

%x COMMENT STRING_STATE

/* Rules section */
%%

 /* Arithmetic */
"+"     { CONCAT; return('+'); }
"-"     { CONCAT; return('-'); }
"*"   	{ CONCAT; return('*'); }
"/"   	{ CONCAT; return('/'); }
"%"     { CONCAT; return('%'); }
"++"    { CONCAT; return(INC_OP); }
"--"    { CONCAT; return(DEC_OP); }

 /* Relational */
">"		{ CONCAT; return('>'); }
"<"		{ CONCAT; return('<'); }
">="	{ CONCAT; return(GE_OP); }
"<="	{ CONCAT; return(LE_OP); }
"=="	{ CONCAT; return(EQ_OP); }
"!="	{ CONCAT; return(NE_OP); }

 /* Assignment */
"="		{ CONCAT; return('='); }
"+="	{ CONCAT; return(ADD_ASSIGN); }
"-="	{ CONCAT; return(SUB_ASSIGN); }
"*="	{ CONCAT; return(MUL_ASSIGN); }
"/="	{ CONCAT; return(DIV_ASSIGN); }
"%="	{ CONCAT; return(MOD_ASSIGN); }

 /* Logical */
"&&"	{ CONCAT; return(AND_OP); }
"||"	{ CONCAT; return(OR_OP); }
"!"		{ CONCAT; return('!'); }

 /* Delimiters */
"("		{ CONCAT; return('('); }
")"		{ CONCAT; return(')'); }
"{"		{ CONCAT; return('{'); }
"}"		{ CONCAT; return('}'); }
"["		{ CONCAT; return('['); }
"]"		{ CONCAT; return(']'); }
","		{ CONCAT; return(','); }

 /* Print Keywords */	
"print"		{ CONCAT; return(PRINT);  }

 /* Condition and Loop Keywords */
"if"		{ CONCAT; return(IF); }
"else"		{ CONCAT; return(ELSE); }
"for"       { CONCAT; return(FOR); }
"while"		{ CONCAT; return(WHILE); }

 /* Declaration Keywords */
"void"      { CONCAT; yylval.val.symbol_type = V_Type; yylval.val.is_arith = 0; return(VOID); }
"int"       { CONCAT; yylval.val.symbol_type = I_Type; yylval.val.is_arith = 0; return(INT);  }
"float"  	{ CONCAT; yylval.val.symbol_type = F_Type; yylval.val.is_arith = 0; return(FLOAT);}
"string"    { CONCAT; yylval.val.symbol_type = S_Type; yylval.val.is_arith = 0; return(STRING);}
"bool"      { CONCAT; yylval.val.symbol_type = B_Type; yylval.val.is_arith = 0; return(BOOL);}

 /* boolean Keywords */
"true"      { CONCAT; yylval.val.i = 1; yylval.val.symbol_type = B_Type; yylval.val.is_arith = 0; return(TRUE); }
"false"     { CONCAT; yylval.val.i = 0; yylval.val.symbol_type = B_Type; yylval.val.is_arith = 0; return(FALSE); }

"return"    { CONCAT; return(RETURN); }

 /* String Constant */
\"            { CONCAT; BEGIN STRING_STATE; return(QUOTA);}
<STRING_STATE>\"        { CONCAT; BEGIN INITIAL; return(QUOTA);}
<STRING_STATE>[^"]*	    { CONCAT; 
                          yylval.val.symbol_type = S_Type; 
                          yylval.val.s = strdup(yytext);
                          yylval.val.is_arith = 0;
                          return(STRING_CONST);
                        }

 /* Number Constant */
{integer}     { CONCAT; 
                yylval.val.symbol_type = I_Type; 
                yylval.val.i = atoi(yytext);
                yylval.val.is_arith = 0;                 
                return(I_CONST); 
              }
{float}       { CONCAT; 
                yylval.val.symbol_type = F_Type; 
                yylval.val.f = atof(yytext);
                yylval.val.is_arith = 0;                  
                return(F_CONST); 
              }

 /* C type Comment */
"/*"				{ CONCAT; BEGIN COMMENT; }
<COMMENT>[^*\n]+	{ CONCAT; }
<COMMENT>\n			{  
                      printf("%d:", line_num);
                      printf(" %s", buf); 
                      printf("\n"); 
                      line_num++; 
                      memset(buf, 0, BUF_SIZE);
                    }
<COMMENT>"*"		{ CONCAT;  }
<COMMENT>"*/"		{ CONCAT; BEGIN INITIAL; }

 /* C++ symbol_type Comment */
\/\/.*	{ CONCAT; }

 /* Variable ID */
 {id}       { CONCAT; 
              yylval.val.symbol_type = ID_Type; 
              yylval.val.id_name = strdup(yytext);
              yylval.val.is_arith = 0;               
              return(ID); 
            }

 /* others */

[;]         { CONCAT; return(SEMICOLON); }
[\n]        {  printf("%d:", line_num);
               if(strlen(buf) != 0){
                    printf(" %s", buf);
                } 
                printf("\n");

                if(error_flag != 0){
                    yyerror(error_msg);
                    error_flag = 0;
                 }

                //if syntax_error, close parser
                if(syntax_flag != 0){
                    yyterminate();
                } 
    
                if(dump_flag == 1){
                    dump_symbol();
                    dump_flag = 0;
                }

                memset(buf, 0, BUF_SIZE);
                line_num++;
            }
[ \t]		{ CONCAT; } /* Ignore */
[^ \t\n] 	{ CONCAT; } /* Ignore other charactor sets */
<<EOF>>     { yyterminate();}

%%

int yywrap()
{
    return 1 ;
}