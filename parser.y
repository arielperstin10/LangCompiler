%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_PARAMS 10

    int yylex();
    int yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    
    typedef enum {
        TYPE_INT, TYPE_CHAR, TYPE_REAL, TYPE_STRING, TYPE_BOOL,
        TYPE_INT_PTR, TYPE_CHAR_PTR, TYPE_REAL_PTR, TYPE_INVALID
    } VarType;

    typedef struct Symbol {
        char* name;
        VarType type;
        int is_function;
        VarType return_type;
        VarType param_types[MAX_PARAMS];
        int param_count;
        int scope_level;
        struct Symbol* next;
    } Symbol;

    typedef struct node
    {
        char* token;
        struct node* left;
        struct node* right;
    } node;
    node* mknode(char* token, node* left, node* right);
    void printTree(node* tree, int level);
    void visualize_ast(node* root, const char* branch_prefix, int is_left_branch);
    VarType string_to_type(const char* str);
    void insert_symbol(char* name, VarType type, int is_function, VarType return_type, VarType* param_types, int param_count);
    void enter_scope();
    void exit_scope();

    node* root = NULL;
    Symbol* symbol_table = NULL;
    int current_scope_level = 0;
    int main_count = 0;
%}

%union {
    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;
    VarType typeVal;
    VarType paramList[MAX_PARAMS];
}

%type <typeVal> type_specifier return_type
%type <paramList> param_list

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
%type <nodePtr> block_statement scope_entry return_statement function_call_statement function_call expression scoped_block
%type <nodePtr> expr_list nested_function

%%

code: functions {root = mknode("code", $1, NULL); $$ = root;};

functions: function {$$ = $1;}
        | function functions {$$ = mknode("functions", $1, $2);}
        ;

function: DEF MAIN '(' ')' ':' var BEGIN_TOKEN statements END {
            node* stmt = $8;
            while (stmt) 
            {
                if (strcmp(stmt->token, "return_val") == 0) 
                {
                    yyerror("Semantic Error: _main_ must not contain return statements.");
                    YYERROR;
                }
                stmt = stmt->right;
            }
            insert_symbol("_main_", TYPE_INVALID, 1, TYPE_INVALID, NULL, 0); 
            $$ = mknode("FUNC", mknode("main", NULL, $6), mknode("body", $8, NULL));
        }
        | DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END {
            // Check if last statement is a return
            node* last_stmt = $11;
            while (last_stmt && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            if (!last_stmt || strcmp(last_stmt->token, "return_val") != 0) {
                yyerror("Error: function with RETURNS must end with a return statement");
                YYERROR;
            }
            if (strcmp($2, "_main_") == 0) 
            {
                yyerror("Semantic Error: _main_ must not return a value.");
                YYERROR;
            }
            VarType ret_type = string_to_type($8->token);
            insert_symbol($2, TYPE_INVALID, 1, ret_type, NULL, 0);
            $$ = mknode("FUNC", mknode($2, $4, mknode("ret", $8, $9)), mknode("body", $11, NULL));
        } 
        | DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END {
            // Check if last statement is a return
            node* last_stmt = $9;
            while (last_stmt && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            if (last_stmt && strcmp(last_stmt->token, "return_val") == 0) {
                yyerror("Error: function without RETURNS must not have a return statement");
                YYERROR;
            }
            if (strcmp($2, "_main_") == 0 && $4 != NULL) 
            {
                yyerror("Semantic Error: _main_ must not have parameters.");
                YYERROR;
            }
            insert_symbol($2, TYPE_INVALID, 1, TYPE_INVALID, NULL, 0);
            $$ = mknode("FUNC", mknode($2, $4, NULL), mknode("body", $9, NULL));
        }
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

declaration: TYPE type ':' id_list ';' {
        VarType vtype = string_to_type($2->token);
        node* ids = $4;
        while (ids) 
        {
            char* var_name = ids->token;
            insert_symbol(var_name, vtype, 0, TYPE_INVALID, NULL, 0);
            ids = ids->right;
        }
        $$ = mknode("DECL", $2, $4);
    };

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
    {
        // Check if last statement is a return
        node* last_stmt = $11;
        while (last_stmt && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        if (!last_stmt || strcmp(last_stmt->token, "return_val") != 0) {
            yyerror("Error: function with RETURNS must end with a return statement");
            YYERROR;
        }
        $$ = mknode("nested_func", mknode($2, $4, mknode("ret", $8, $9)), mknode("body", $11, NULL));
    }
    | DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END
    {
        // Check if last statement is a return
        node* last_stmt = $9;
        while (last_stmt && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        if (last_stmt && strcmp(last_stmt->token, "return_val") == 0) {
            yyerror("Error: function without RETURNS must not have a return statement");
            YYERROR;
        }
        $$ = mknode("nested_func", mknode($2, $4, NULL), mknode("body", $9, NULL));
    }
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

scope_entry: /* nothing */ { enter_scope(); $$ = NULL; };

scoped_block:
    scope_entry BEGIN_TOKEN END {
        exit_scope();
        $$ = mknode("block", NULL, NULL);
    }
  | scope_entry BEGIN_TOKEN statements END {
        exit_scope();
        $$ = mknode("block", $3, NULL);
    }
  | scope_entry var BEGIN_TOKEN END {
        exit_scope();
        $$ = mknode("block", NULL, $2);
    }
  | scope_entry var BEGIN_TOKEN statements END {
        exit_scope();
        $$ = mknode("block", $4, $2);
    }
;

block_statement:
    scoped_block { $$ = $1; }
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
    if (yyparse() == 0) {
        if (main_count == 0) 
        {
            fprintf(stderr, "Semantic Error: Missing '_main_' function.\n");
            return 1;
        } else if (main_count > 1) 
        {
            fprintf(stderr, "Semantic Error: Multiple '_main_' functions are not allowed.\n");
            return 1;
        }
        visualize_ast(root, "", 1);
        printf("Semantic checks passed.\n");
    }

    
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

// Part 2
VarType string_to_type(const char* str) 
{
    if (strcmp(str, "int") == 0) return TYPE_INT;
    if (strcmp(str, "char") == 0) return TYPE_CHAR;
    if (strcmp(str, "real") == 0) return TYPE_REAL;
    if (strcmp(str, "string") == 0) return TYPE_STRING;
    if (strcmp(str, "bool") == 0) return TYPE_BOOL;
    if (strcmp(str, "int*") == 0) return TYPE_INT_PTR;
    if (strcmp(str, "char*") == 0) return TYPE_CHAR_PTR;
    if (strcmp(str, "real*") == 0) return TYPE_REAL_PTR;
    return TYPE_INVALID;
}

void insert_symbol(char* name, VarType type, int is_function, VarType return_type, VarType* param_types, int param_count) 
{
    // Check for redefinition in the same scope
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->scope_level == current_scope_level && strcmp(sym->name, name) == 0) {
            fprintf(stderr, "Semantic Error: Redefinition of '%s' in the same scope.\n", name);
            exit(1);
        }
        sym = sym->next;
    }

    // Create new symbol
    Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->type = type;
    new_sym->is_function = is_function;
    new_sym->return_type = return_type;
    new_sym->param_count = param_count;
    for (int i = 0; i < param_count; i++) {
        new_sym->param_types[i] = param_types[i];
    }
    new_sym->scope_level = current_scope_level;
    new_sym->next = symbol_table;
    symbol_table = new_sym;

    // Handle main function count
    if (is_function && strcmp(name, "_main_") == 0) {
        main_count++;
    }
}

void enter_scope() {
    current_scope_level++;
}

void exit_scope() {
    Symbol* sym = symbol_table;
    while (sym && sym->scope_level == current_scope_level) {
        Symbol* to_delete = sym;
        sym = sym->next;
        free(to_delete->name);
        free(to_delete);
    }
    symbol_table = sym;
    current_scope_level--;
}

