%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex();
    int yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    
    typedef struct node
    {
        char* token;
        struct node* left;
        struct node* right;
    } node;
    node* mknode(char* token, node* left, node* right);
    void printTree(node* tree, int level);
    void visualize_ast(node* root, const char* branch_prefix, int is_left_branch);
%}

%union {
    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;
}

%token <intVal> INTEGER
%token <realVal> REAL
%token <charVal> CHAR_LITERAL
%token <stringVal> STRING_LITERAL IDENTIFIER

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR TYPE MODULO
%token IF ELIF ELSE WHILE FOR VAR PAR RETURN NULL_TOKEN DO RETURNS BEGIN_TOKEN END DEF CALL AND NOT OR
%token EQ NE GE LE GT LT ASSIGN PLUS MINUS MULT DIV AMPERSAND TRUE FALSE
%token MAIN

%left OR
%left AND
%left EQ NE
%left GE LE GT LT
%left PLUS MINUS
%left MULT DIV MODULO
%right NOT
%right AMPERSAND

%type <nodePtr> code functions function parameters parameter_list parameter var declaration_list 
%type <nodePtr> declaration type id_list statements statement assignment_statement if_statement 
%type <nodePtr> while_statement do_while_statement for_statement for_header update_exp condition
%type <nodePtr> block_statement return_statement function_call_statement function_call expression
%type <nodePtr> expr_list nested_function

%%

code: functions {$$ = mknode("code", $1, NULL); visualize_ast($1, "", 1);};

functions: function {$$ = $1;}
        | function functions {$$ = mknode("functions", $1, $2);}
        ;

function: DEF MAIN '(' ')' ':' var BEGIN_TOKEN statements END {$$ = mknode("FUNC", mknode("main", NULL, $6), mknode("body", $8, NULL));}
        | DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END {$$ = mknode("FUNC", mknode($2, $4, mknode("ret", $8, $9)), mknode("body", $11, NULL));} 
        | DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END 
          {$$ = mknode("FUNC", mknode($2, $4, NULL), mknode("body", $9, NULL));}
        ;

parameters: /* empty */ {$$ = NULL;}
        | parameter_list {$$ = $1;}
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
    | IDENTIFIER '[' INTEGER ']' {
        char int_str[20];
        sprintf(int_str, "%d", $3);
        $$ = mknode($1, mknode(int_str, NULL, NULL), NULL);
    }
    | IDENTIFIER '[' INTEGER ']' ',' id_list {
        char int_str[20];
        sprintf(int_str, "%d", $3);
        $$ = mknode($1, mknode(int_str, NULL, NULL), $6);
    }
    | IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL {
        char int_str[20];
        sprintf(int_str, "%d", $3);
        $$ = mknode($1, mknode(int_str, NULL, NULL), mknode($6, NULL, NULL));
    }
    | IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL ',' id_list {
        char int_str[20];
        sprintf(int_str, "%d", $3);
        $$ = mknode($1, mknode(int_str, NULL, NULL), mknode($6, NULL, $8));
    }
    ;

statements: statement {$$ = $1;}
    | statement statements {$$ = mknode("statements", $1, $2);}
    | nested_function {$$ = $1;}
    | nested_function statements {$$ = mknode("statements", $1, $2);}
    ;


nested_function: 
    DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END
    {$$ = mknode("nested_func", mknode($2, $4, mknode("ret", $8, $9)), mknode("body", $11, NULL));}
    | DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END
    {$$ = mknode("nested_func", mknode($2, $4, NULL), mknode("body", $9, NULL));}
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
    IDENTIFIER ASSIGN expression ';' {$$ = mknode("assign", mknode($1, NULL, NULL), $3);}
    | IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';' {
        char char_str[2];
        char_str[0] = $6;
        char_str[1] = '\0';
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode(char_str, NULL, NULL));
    }
    | MULT IDENTIFIER ASSIGN expression ';' {$$ = mknode("pointer_assign", mknode($2, NULL, NULL), $4);}
    | IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';' {$$ = mknode("ref_assign", mknode($1, NULL, NULL), mknode($4, NULL, NULL));}
    | IDENTIFIER ASSIGN NULL_TOKEN ';' {$$ = mknode("null_assign", mknode($1, NULL, NULL), mknode("null", NULL, NULL));}
    | IDENTIFIER '[' expression ']' ASSIGN INTEGER ';' {
        char int_str[20];
        sprintf(int_str, "%d", $6);
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode(int_str, NULL, NULL));
    }
    | IDENTIFIER '[' expression ']' ASSIGN STRING_LITERAL ';' {
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode($6, NULL, NULL));
    }
    | IDENTIFIER '[' expression ']' ASSIGN expression ';' {
        $$ = mknode("array_assign", mknode($1, $3, NULL), $6);
    }
    ;

if_statement:
    IF expression ':' block_statement {$$ = mknode("if", $2, $4);}
    | IF expression ':' block_statement ELSE ':' block_statement {$$ = mknode("if-else", $2, mknode("then", $4, mknode("else", $7, NULL)));}
    | IF expression ':' block_statement ELIF expression ':' block_statement {$$ = mknode("if-elif", $2, mknode("then", $4, mknode("elif-cond", $6, $8)));}
    | IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement {$$ = mknode("if-elif-else", $2, mknode("then", $4, mknode("elif-cond", $6, mknode("elif-then", $8, mknode("else", $11, NULL)))));}
    ;

while_statement:
    WHILE expression ':' block_statement {$$ = mknode("while", $2, $4);}
    ;

do_while_statement:
    DO ':' block_statement WHILE expression ';' {$$ = mknode("do-while", $3, mknode("cond", $5, NULL));}
    ;

for_statement:
    FOR for_header ':' block_statement {$$ = mknode("for", $2, $4);}
    | FOR for_header ':' var block_statement {$$ = mknode("for", $2, mknode("block", $5, $4));}
    ;

for_header:
    '(' IDENTIFIER ASSIGN expression ';' expression ';' update_exp ')' 
    {$$ = mknode("for-header", mknode("init", mknode($2, NULL, NULL), $4), 
                             mknode("loop", $6, $8));}
    ;

update_exp:
    IDENTIFIER ASSIGN expression {$$ = mknode("update", mknode($1, NULL, NULL), $3);}
    ;

condition:
    expression {$$ = $1;} // Just pass through the expression
    | NOT condition {$$ = mknode("not", $2, NULL);}
    | '(' condition ')' {$$ = $2;}
    | TRUE {$$ = mknode("true", NULL, NULL);}
    | FALSE {$$ = mknode("false", NULL, NULL);}
    ;

block_statement:
    BEGIN_TOKEN statements END {$$ = mknode("block", $2, NULL);}
    | var BEGIN_TOKEN statements END {$$ = mknode("block", $3, $1);}
    ;
    
return_statement:
    RETURN expression ';' {$$ = mknode("return_val", $2, NULL);}
    | RETURN ';' {$$ = mknode("return_void", NULL, NULL);}
    ;

function_call_statement:
    function_call ';' {$$ = $1;}
    | IDENTIFIER ASSIGN function_call ';' {$$ = mknode("assign", mknode($1, NULL, NULL), $3);}
    ;

function_call:
    CALL IDENTIFIER '(' ')' {$$ = mknode("call", mknode($2, NULL, NULL), NULL);}
    | CALL IDENTIFIER '(' expr_list ')' {$$ = mknode("call", mknode($2, NULL, NULL), $4);}
    ;

expr_list: 
    expression {$$ = $1;}
    | expression ',' expr_list {$$ = mknode("expr_list", $1, $3);}
    ;

expression:
    INTEGER {
        char int_str[20];
        sprintf(int_str, "%d", $1);
        $$ = mknode(int_str, NULL, NULL);
    }
    | REAL {
        char real_str[30];
        sprintf(real_str, "%f", $1);
        $$ = mknode(real_str, NULL, NULL);
    }
    | STRING_LITERAL {$$ = mknode($1, NULL, NULL);}
    | CHAR_LITERAL {
        char char_str[2];
        char_str[0] = $1;
        char_str[1] = '\0';
        $$ = mknode(char_str, NULL, NULL);
    }
    | IDENTIFIER {$$ = mknode($1, NULL, NULL);}
    | expression PLUS expression {$$ = mknode("+", $1, $3);}
    | expression MINUS expression {$$ = mknode("-", $1, $3);}
    | expression MULT expression {$$ = mknode("*", $1, $3);}
    | expression DIV expression {$$ = mknode("/", $1, $3);}
    | expression MODULO expression {$$ = mknode("%", $1, $3);}
    | MINUS expression {$$ = mknode("unary-", $2, NULL);}
    | AMPERSAND IDENTIFIER {$$ = mknode("&", mknode($2, NULL, NULL), NULL);}
    | AMPERSAND IDENTIFIER '[' expression ']' {$$ = mknode("&", mknode("index", mknode($2, NULL, NULL), $4), NULL);}
    | MULT IDENTIFIER {$$ = mknode("deref", mknode($2, NULL, NULL), NULL);}
    | MULT expression {$$ = mknode("*", $2, NULL);}
    | '(' expression ')' {$$ = $2;}
    | expression EQ expression {$$ = mknode("==", $1, $3);}
    | expression NE expression {$$ = mknode("!=", $1, $3);}
    | expression GE expression {$$ = mknode(">=", $1, $3);}
    | expression LE expression {$$ = mknode("<=", $1, $3);}
    | expression GT expression {$$ = mknode(">", $1, $3);}
    | expression LT expression {$$ = mknode("<", $1, $3);}
    | expression AND expression {$$ = mknode("and", $1, $3);}
    | expression OR expression {$$ = mknode("or", $1, $3);}
    | IDENTIFIER '[' expression ']' {$$ = mknode("index", mknode($1, NULL, NULL), $3);}
    | function_call {$$ = $1;} /* Allow function calls in expressions */
    ;

%%

int main()
{
    yyparse();
    return 0;
}

node* mknode(char* token, node* left, node* right)
{
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed for node\n");
        exit(1);
    }
    
    char* newStr = (char*)malloc(strlen(token) + 1);
    if (!newStr) {
        fprintf(stderr, "Memory allocation failed for token\n");
        free(newNode);
        exit(1);
    }
    
    strcpy(newStr, token);
    newNode->left = left;
    newNode->right = right;
    newNode->token = newStr;
    return newNode;
}

void printTree(node* tree, int level)
{
    if (!tree) return;
    
    for (int i = 0; i < level; i++) {
        printf("  "); // Two spaces per level for indentation
    }
    
    if (tree->token) {
        printf("%s\n", tree->token);
    }
    
    if (tree->left) {
        printTree(tree->left, level + 1);
    }
    
    if (tree->right) {
        printTree(tree->right, level + 1);
    }
}

int yyerror(const char* s)
{
    fprintf(stderr, "Error: %s at line %d near token '%s'\n", s, yylineno, yytext);
    return 0;
}

void visualize_ast(node* root, const char* branch_prefix, int is_left_branch) {
    if (!root) return;

    // Print current node with appropriate branch connector
    printf("%s", branch_prefix);
    printf(is_left_branch ? "├── " : "└── ");
    printf("%s\n", root->token);

    // Create new prefix for child nodes
    char child_prefix[1024];
    snprintf(child_prefix, sizeof(child_prefix), "%s%s", 
             branch_prefix, 
             is_left_branch ? "│   " : "    ");

    // Handle different child node cases
    if (root->left && root->right) {
        // Both children exist - left child is not last
        visualize_ast(root->left, child_prefix, 1);
        visualize_ast(root->right, child_prefix, 0);
    } else if (root->left) {
        // Only left child exists
        visualize_ast(root->left, child_prefix, 0);
    } else if (root->right) {
        // Only right child exists
        visualize_ast(root->right, child_prefix, 0);
    }
}