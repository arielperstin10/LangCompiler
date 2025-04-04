%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex();
    void yyerror(const char* s);
%}

%union {
    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    ASTNode* node;
}

%token <intVal> INTEGER
%token <realVal> REAL
%token <charVal> CHAR_LITERAL
%token <stringVal> STRING_LITERAL IDENTIFIER

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR
%token IF ELIF ELSE WHILE FOR VAR PAR RETURN NULL DO RETURNS BEGIN END DEF CALL AND NOT OR
%token EQ NE GE LE GT LT ASSIGN PLUS MINUS MULT DIV AMPERSAND

%type <node> program functions function parameter_list parameters opt_returns 
%type <node> type declarations decl_list decl identifier_list statements statement expression expression_list 

%%

