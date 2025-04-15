%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex();
    int yyerror();
    typedef struct node
    {
        char* token;
        struct node* left;
        struct node* right;
    } node;
    node* mknode(char* token, node* left, node* right);
    void printTree(node* tree, int level);
    #define YYSTYPE struct node*
%}

%union {
    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
}

%token <intVal> INTEGER
%token <realVal> REAL
%token <charVal> CHAR_LITERAL
%token <stringVal> STRING_LITERAL IDENTIFIER

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR TYPE
%token IF ELIF ELSE WHILE FOR VAR PAR RETURN NULL DO RETURNS BEGIN END DEF CALL AND NOT OR
%token EQ NE GE LE GT LT ASSIGN PLUS MINUS MULT DIV AMPERSAND

%left OR
%left AND
%left EQ NE
%left GE LE GT LT
%left PLUS MINUS
%left MULT DIV
%right NOT

%%

code: functions {$$ = mknode("code", $1, NULL);};

functions: function {$$ = $1;}
        | function functions {$$ = mknode("functions", $1, $2);}
        ;

function: DEF IDENTIFIER '(' parameters ')' RETURNS type var BEGIN statements END {$$ = mknode("FUNC", mknode($2, $4, mknode("ret", $6, $7)), mknode("body", $10, NULL));} 
        | DEF '_main_' '(' ')' ':' var BEGIN statements END {$$ = mknode("FUNC", mknode("main", NULL, $5), mknode("body", $7, NULL));}
        ;

parameters: /* empty */ {$$ = NULL;}
        parameter_list {$$ = $1;};
        ;

parameter_list: parameter {$$ = $1;}
        | parameter ';' parameter_list {$$ = mknode("PARAMS", $1, $3);}
        ;

parameter: PAR type ':' IDENTIFIER {$$ = mknode($4, $2, NULL);};

var: /* empty */ {$$ = NULL;}
    | VAR declaration_list {$$ = mknode("VAR", $2, NULL);}
    ;

declaration_list: declaration {$$ = $1;}
    | declaration declaration_list {$$ = mknode("decls", $1, $2);}
    ;

declaration: TYPE type ':' id_list ';' {$$ = mknode("DECL", $2, $4);};

type:
    BOOL       { $$ = mknode("BOOL", NULL, NULL); }
    | CHAR       { $$ = mknode("CHAR", NULL, NULL); }
    | INT        { $$ = mknode("INT", NULL, NULL); }
    | REAL_TYPE  { $$ = mknode("REAL", NULL, NULL); }
    | STRING     { $$ = mknode("STRING", NULL, NULL); }
    | INT_PTR    { $$ = mknode("INT_PTR", NULL, NULL); }
    | CHAR_PTR   { $$ = mknode("CHAR_PTR", NULL, NULL); }
    | REAL_PTR   { $$ = mknode("REAL_PTR", NULL, NULL); }
    ;

id_list: IDENTIFIER {$$ = mknode($1, NULL, NULL);}
    | IDENTIFIER ',' id_list {$$ = mknode($1, NULL, $3);}
    | IDENTIFIER ':' expression {$$ = mknode($1, $3, NULL);}
    | IDENTIFIER ':' expression ',' id_list {$$ = mknode($1, $3, $5);}
    | IDENTIFIER '[' INTEGER ']' {$$ = mknode($1, $3, NULL);}
    | IDENTIFIER '[' INTEGER ']' ',' id_list {$$ = mknode($1, $3, $5);}
    | IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL {$$ = mknode($1, $3, mknode($5, NULL, NULL));}
    | IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL ',' id_list {$$ = mknode($1, $3, mknode($5, NULL, $7));}
    ;

statements: statement {$$ = $1;}
    | statement statements {$$ = mknode("statements", $1, $2);}
    ;

statement: assignment_statement {$$ = $1;}
    | if_statement {$$ = $1;}
    | while_statement {$$ = $1;}
    | for_statement {$$ = $1;}
    | do_while_statement {$$ = $1;}
    | block_statement {$$ = $1;}
    | return_statement {$$ = $1;}
    | function_call_statement {$$ = $1;}
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression ';' $$ = mknode("assign", mknode($1, NULL, NULL), $3);
    ;

if_statement:
    IF expression ':' block_statement {$$ = mknode("if", $2, $3);}
    | IF expression ':' block_statement ELSE ':' block_statement {$$ = mknode("if", $2, mknode("else", $4, NULL));}
    | IF expression ':' block_statement ELIF expression ':' block_statement {$$ = mknode("if", $2, mknode("elif", $4, NULL));}
    | IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement {$$ = mknode("if", $2, mknode("elif", $4, mknode("else", $6, NULL)));}
    ;

while_statement:
    WHILE expression ':' block_statement {$$ = mknode("while", $2, $4);}
    ;

do_while_statement:
    DO ':' block_statement WHILE expression ';' {$$ = mknode("do_while", $3, mknode("while", $5, NULL));}
    ;

for_statement:
    FOR '(' assignment_statement expression ';' assignment_statement ')' ':' block_statement {$$ = mknode("for", $3, mknode("assign", mknode($5, NULL, NULL), $7), mknode("assign", mknode($9, NULL, NULL), $11), $13);}
    ;

block_statement:
    BEGIN statements END {$$ = mknode("block", $2, NULL);}
    | var BEGIN statements END {$$ = mknode("block", $3, $1);}
    ;
    
return_statement:
    RETURN expression ';' {$$ = mknode("return", $2, NULL);}
    ;

function_call_statement:
    function_call ';' {$$ = mknode("call", $1, NULL);}
    | IDENTIFIER ASSIGN function_call ';' {$$ = mknode("assign", mknode($1, NULL, NULL), $3);}
    ;

function_call:
    CALL IDENTIFIER '(' parameters ')' {$$ = mknode("call", $2, $4);}
    ;


expression: expression PLUS expression {$$ = mknode("+", $1, $3);}
    | expression MINUS expression {$$ = mknode("-", $1, $3);}
    | expression MULT expression {$$ = mknode("*", $1, $3);}
    | expression DIV expression {$$ = mknode("/", $1, $3);}
    | expression EQ expression {$$ = mknode("==", $1, $3);}
    | expression NE expression {$$ = mknode("!=", $1, $3);}
    | expression GE expression {$$ = mknode(">=", $1, $3);}
    | expression LE expression {$$ = mknode("<=", $1, $3);}
    | expression GT expression {$$ = mknode(">", $1, $3);}
    | expression LT expression {$$ = mknode("<", $1, $3);}
    | expression AND expression {$$ = mknode("and", $1, $3);}
    | expression OR expression {$$ = mknode("or", $1, $3);}
    | expression NOT expression {$$ = mknode("not", $1, $3);}

%%

#include "lex.yy.c"

int main()
{
    return yyparse();
}

void* mknode(char* token, node* left, node* right)
{
    node* newNode = (node*)malloc(sizeof(node));
    char* newStr = (char*)malloc(sizeof(token) + 1);
    strcpy(newStr, token);
    newNode->left = left;
    newNode->right = right;
    newNode->token = newStr;
    return newNode;
}

void printTree(node* tree, int level)
{
    for (int i = 0; i < level; i++, printf("\t"));
    if (strcmp(tree->token, ""))
        printf("%s\n", tree->token);
    if (tree->left)
        printTree(tree->left, level + 1);
    if (tree->right)
        printTree(tree->right, level + 1);
}

int yyerror()
{
    printf("Error\n");
    return 0;
}
