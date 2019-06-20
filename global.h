#ifndef GLOBAL_H
#define GLOBAL_H

typedef enum {V_Type, I_Type, F_Type, S_Type, ID_Type, B_Type, T_Type} Symbol_type;

typedef enum {ADD_OPT, MINUS_OPT, MUL_OPT, DIV_OPT, MOD_OPT, INC_OPT, DEC_OPT,
              MORE_OPT, LESS_OPT, GE_OPT, LE_OPT, EQ_OPT, NE_OPT,
              ASSIGN_OPT, ADD_ASSIGN_OPT, SUB_ASSIGN_OPT, MUL_ASSIGN_OPT, DIV_ASSIGN_OPT, MOD_ASSIGN_OPT,
              AND_OPT, OR_OPT, NOT_OPT } Operator;

typedef struct Value Value;
struct Value
{
    union 
    {
        int i;
        float f;
        char *s;
        
    };
    Symbol_type symbol_type;

    // for ID
    char * id_name;
    union 
    {
        int id_i;
        float id_f;
        char *id_s;
    };
    Symbol_type id_symbol_type;
    int is_global;
    int id_index;
    int is_arith;

};

#endif

