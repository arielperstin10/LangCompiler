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
    void* node;
}

%token <intVal> INTEGER
%token <realVal> REAL
%token <charVal> CHAR_LITERAL
%token <stringVal> STRING_LITERAL IDENTIFIER

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR TYPE MODULO
%token IF ELIF ELSE WHILE FOR VAR PAR RETURN NULL DO RETURNS BEGIN END DEF CALL AND NOT OR
%token EQ NE GE LE GT LT ASSIGN PLUS MINUS MULT DIV AMPERSAND TRUE FALSE

%left OR
%left AND
%left EQ NE
%left GE LE GT LT
%left PLUS MINUS
%left MULT DIV
%right NOT

%type <node> code functions function parameters parameter_list parameter var declaration_list declaration type id_list statements statement assignment_statement if_statement while_statement do_while_statement for_statement for_header update_exp condition comparison block_statement return_statement function_call_statement function_call expression


%%

code: functions {$$ = mknode("code", $1, NULL);};

functions: function {$$ = $1;}
        | function functions {$$ = mknode("functions", $1, $2);}
        ;

function: DEF IDENTIFIER '(' parameters ')' RETURNS type var BEGIN statements END {$$ = mknode("FUNC", mknode($2, $4, mknode("ret", $6, $7)), mknode("body", $10, NULL));} 
        | DEF "_main_" '(' ')' ':' var BEGIN statements END {$$ = mknode("FUNC", mknode("main", NULL, $5), mknode("body", $7, NULL));}
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
    IDENTIFIER ASSIGN expression ';' {$$ = mknode("assign", mknode($1, NULL, NULL), $3)};
    | IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';' {$$ = mknode("array_assign", mknode($1, $3, NULL), mknode($6, NULL, NULL));}
    | '*' IDENTIFIER ASSIGN expression ';' {$$ = mknode("pointer_assign", mknode($2, NULL, NULL), $4);}
    | IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';' {$$ = mknode("ref_assign", mknode($1, NULL, NULL), mknode($4, NULL, NULL));}
    | IDENTIFIER ASSIGN NULL ';' {$$ = mknode("null_assign", mknode($1, NULL, NULL), mknode("null", NULL, NULL));}
    | IDENTIFIER '[' expression ']' ASSIGN INTEGER ';' {char int_to_str[20]; sprintf(int_to_str, "%d", $6); $$ = mknode("array_assign", mknode($1, $3, NULL), mknode(int_to_str, NULL, NULL));}
    ;

if_statement:
    IF expression ':' block_statement {$$ = mknode("if", $2, $3);}
    | IF expression ':' block_statement ELSE ':' block_statement {$$ = mknode("if", mknode("cond", $2, NULL), mknode("then", $4, $7));}
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
    FOR for_header ':' block_statement {$$ = mknode("for", $2, $4);}
    | FOR for_header ':' var block_statement {$$ = mknode("for", $2, $5);}
    ;

for_header:
    '(' IDENTIFIER ASSIGN expression ';' condition ';' update_exp ')' {$$ = mknode("for_header", mknode("assign", mknode($2, NULL, NULL), $4), mknode("loop", $6, $8));}
    ;

update_exp:
    IDENTIFIER ASSIGN expression {$$ = mknode("update", mknode($1, NULL, NULL), $3);}
    ;

condition:
    expression comparison expression {$$ = mknode($2, $1, $3);}
    | NOT condition {$$ = mknode("not", $2, NULL);}
    | expression OR expression {$$ = mknode("or", $1, $3);}
    | expression AND expression {$$ = mknode("and", $1, $3);}
    | '(' condition ')' {$$ = $2;}
    | TRUE {$$ = mknode("true", NULL, NULL);}
    | FALSE {$$ = mknode("false", NULL, NULL);}
    ;

comparison:
    EQ {$$ = mknode("==", NULL, NULL);}
    | NE {$$ = mknode("!=", NULL, NULL);}
    | GE {$$ = mknode(">=", NULL, NULL);}
    | LE {$$ = mknode("<=", NULL, NULL);}
    | GT {$$ = mknode(">", NULL, NULL);}
    | LT {$$ = mknode("<", NULL, NULL);}
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


expression:
    INTEGER {char int_to_str[20]; sprintf(int_to_str, "%d", $1); $$ = mknode(int_to_str, NULL, NULL);}
    | REAL {char real_to_str[20]; sprintf(real_to_str, "%f", $1); $$ = mknode(real_to_str, NULL, NULL);}
    | STRING_LITERAL {$$ = mknode($1, NULL, NULL);}
    | CHAR_LITERAL {char char_to_str[2]; char_to_str[0] = $1; char_to_str[1] = '\0'; $$ = mknode(char_to_str, NULL, NULL);}
    | IDENTIFIER {$$ = mknode($1, NULL, NULL);}
    | expression PLUS expression {$$ = mknode("+", $1, $3);}
    | expression MINUS expression {$$ = mknode("-", $1, $3);}
    | expression MULT expression {$$ = mknode("*", $1, $3);}
    | expression DIV expression {$$ = mknode("/", $1, $3);}
    | expression MODULO expression {$$ = mknode("%", $1, $3);}
    | MINUS expression {$$ = mknode("-", $2, NULL);}
    | AMPERSAND expression {$$ = mknode("&", $2, NULL);}
    ;
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
