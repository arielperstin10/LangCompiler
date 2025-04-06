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

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR
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







// Expressions
assign: IDENTIFIER ASSIGN expr ';' {$$ = mknode($2->token, $1, $3);};

expr: expr PLUS expr {$$ = mknode("+", $1, $3);}
    | expr MINUS expr {$$ = mknode("-", $1, $3);}
    | expr MULT expr {$$ = mknode("*", $1, $3);}
    | expr DIV expr {$$ = mknode("/", $1, $3);}
    | expr EQ expr {$$ = mknode("==", $1, $3);}
    | expr NE expr {$$ = mknode("!=", $1, $3);}
    | expr GE expr {$$ = mknode(">=", $1, $3);}
    | expr LE expr {$$ = mknode("<=", $1, $3);}
    | expr GT expr {$$ = mknode(">", $1, $3);}
    | expr LT expr {$$ = mknode("<", $1, $3);}
    | expr AND expr {$$ = mknode("and", $1, $3);}
    | expr OR expr {$$ = mknode("or", $1, $3);}
    | expr NOT expr {$$ = mknode("not", $1, $3);}
    | AMPERSAND expr {$$ = mknode("address", mknode($2, NULL, NULL), NULL);}
    | '(' expr ')' {$$ = $2;}
    | INTEGER {$$ = mknode("integer", NULL, NULL);}
    | REAL {$$ = mknode("real", NULL, NULL);}
    | CHAR {$$ = mknode("char", NULL, NULL);}
    | STRING {$$ = mknode("string", NULL, NULL);}
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
