%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

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
    int is_function_defined(const char* name);
    int is_variable_defined(const char* name);
    int get_function_param_count(const char* name);
    int count_params(node* param_node);
    void extract_param_types(node* param_node, VarType* types);
    VarType infer_type(node* expr);
    const char* type_to_string(VarType type);
    Symbol* find_function_symbol(const char* name);

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
            node* last_stmt = $11;
            while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            node* final = (last_stmt && strcmp(last_stmt->token, "statements") == 0) ? last_stmt->left : last_stmt;

            if (!final || (strcmp(final->token, "return_val") != 0 && strcmp(final->token, "return_void") != 0)) {
                yyerror("Error: function with RETURNS must end with a return statement");
                YYERROR;
            }

            if (strcmp($2, "_main_") == 0) {
                yyerror("Semantic Error: _main_ must not return a value.");
                YYERROR;
            }

            VarType declared_type = string_to_type($8->token);
            VarType param_types[MAX_PARAMS];
            int param_count = count_params($4);
            extract_param_types($4, param_types);
            insert_symbol($2, TYPE_INVALID, 1, declared_type, param_types, param_count);

            if (declared_type == TYPE_STRING) {
                fprintf(stderr, "Semantic Error: functions cannot return type 'string'.\n");
                exit(1);
            }

            if (strcmp(final->token, "return_void") == 0) {
                fprintf(stderr, "Semantic Error: function declared to return '%s' but returned nothing.\n", type_to_string(declared_type));
                exit(1);
            }

            VarType actual_type = infer_type(final->left);
            if (actual_type != declared_type) {
                fprintf(stderr, "Semantic Error: return type mismatch — expected '%s', got '%s'.\n",
                        type_to_string(declared_type), type_to_string(actual_type));
                exit(1);
            }

            
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
            int param_count = count_params($4);
            VarType param_types[MAX_PARAMS];
            extract_param_types($4, param_types);
            insert_symbol($2, TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);
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
    BOOL       { $$ = mknode("bool", NULL, NULL); }
    | CHAR       { $$ = mknode("char", NULL, NULL); }
    | INT        { $$ = mknode("int", NULL, NULL); }
    | REAL_TYPE  { $$ = mknode("real", NULL, NULL); }
    | STRING     { $$ = mknode("string", NULL, NULL); }
    | INT_PTR    { $$ = mknode("int*", NULL, NULL); }
    | CHAR_PTR   { $$ = mknode("char*", NULL, NULL); }
    | REAL_PTR   { $$ = mknode("real*", NULL, NULL); }
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

statements:  /* empty */ { $$ = NULL; } 
    | statement {$$ = $1;}
    | statement statements {$$ = mknode("statements", $1, $2);}
    | nested_function {$$ = $1;}
    | nested_function statements {$$ = mknode("statements", $1, $2);}
    ;


nested_function: 
    DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN 
    {
        VarType ret_type = string_to_type($8->token);
        int param_count = count_params($4);
        VarType param_types[MAX_PARAMS];
        extract_param_types($4, param_types);
        insert_symbol($2, TYPE_INVALID, 1, ret_type, param_types, param_count);

    }
    statements END
    {
        VarType ret_type = string_to_type($8->token);
        int param_count = count_params($4);
        VarType param_types[MAX_PARAMS];
        extract_param_types($4, param_types);
        insert_symbol($2, TYPE_INVALID, 1, ret_type, param_types, param_count);
    }
    statements END
    {
        node* last_stmt = $12;
        while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        node* final = (last_stmt && strcmp(last_stmt->token, "statements") == 0) ? last_stmt->left : last_stmt;

        if (!final || (strcmp(final->token, "return_val") != 0 && strcmp(final->token, "return_void") != 0)) {
            yyerror("Error: function with RETURNS must end with a return statement");
            YYERROR;
        }

        VarType declared_type = string_to_type($8->token);

        if (declared_type == TYPE_STRING) {
            fprintf(stderr, "Semantic Error: functions cannot return type 'string'.\n");
            exit(1);
        }

        if (strcmp(final->token, "return_void") == 0) {
            fprintf(stderr, "Semantic Error: function declared to return '%s' but returned nothing.\n", type_to_string(declared_type));
            exit(1);
        }

        VarType actual_type = infer_type(final->left);
        if (actual_type != declared_type) {
            fprintf(stderr, "Semantic Error: return type mismatch — expected '%s', got '%s'.\n",
                    type_to_string(declared_type), type_to_string(actual_type));
            exit(1);
        }
        $$ = mknode("nested_func", mknode($2, $4, mknode("ret", $8, $9)), mknode("body", $12, NULL));
    }
    | DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN 
    {
        int param_count = count_params($4);
        VarType param_types[MAX_PARAMS];
        extract_param_types($4, param_types);
        insert_symbol($2, TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);

    }
    statements END
    {
        // Check if last statement is a return
        node* last_stmt = $10;
        while (last_stmt && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        if (last_stmt && strcmp(last_stmt->token, "return_val") == 0) {
            yyerror("Error: function without RETURNS must not have a return statement");
            YYERROR;
        }
        $$ = mknode("nested_func", mknode($2, $4, NULL), mknode("body", $10, NULL));
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
    IDENTIFIER ASSIGN expression ';' 
    {
        if (!is_variable_defined($1)) 
        {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }

        VarType lhs_type = TYPE_INVALID;
        Symbol* sym = symbol_table;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                lhs_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        VarType rhs_type = infer_type($3);

        // Allow assignment of NULL to pointer types only
        if (rhs_type == TYPE_INVALID && strcmp($3->token, "null") == 0) {
            if (lhs_type != TYPE_INT_PTR && lhs_type != TYPE_CHAR_PTR && lhs_type != TYPE_REAL_PTR) {
                fprintf(stderr, "Semantic Error: 'null' can only be assigned to pointer types, got '%s'.\n", type_to_string(lhs_type));
                exit(1);
            }
        } else if (lhs_type != rhs_type) {
            fprintf(stderr, "Semantic Error: cannot assign '%s' to variable of type '%s'.\n", type_to_string(rhs_type), type_to_string(lhs_type));
            exit(1);
        }

        $$ = mknode("assign", mknode($1, NULL, NULL), $3);
    }
    | IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';' {

        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }
        
        VarType index_type = infer_type($3);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }
        char char_str[2];
        char_str[0] = $6;
        char_str[1] = '\0';
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode(char_str, NULL, NULL));
    }
    | MULT IDENTIFIER ASSIGN expression ';' 
    {
        if (!is_variable_defined($2)) 
        {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $2);
            exit(1);
        }

        // Check pointer type
        Symbol* sym = symbol_table;
        VarType ptr_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $2) == 0) {
                ptr_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        VarType target_type = TYPE_INVALID;
        switch (ptr_type) {
            case TYPE_INT_PTR: target_type = TYPE_INT; break;
            case TYPE_CHAR_PTR: target_type = TYPE_CHAR; break;
            case TYPE_REAL_PTR: target_type = TYPE_REAL; break;
            default:
                fprintf(stderr, "Semantic Error: '*' applied to non-pointer variable '%s'.\n", $2);
                exit(1);
        }

        VarType expr_type = infer_type($4);
        if (expr_type != target_type) {
            fprintf(stderr, "Semantic Error: cannot assign '%s' to dereferenced '%s'.\n",
                    type_to_string(expr_type), type_to_string(ptr_type));
            exit(1);
        }
        $$ = mknode("pointer_assign", mknode($2, NULL, NULL), $4);
    }
    | IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';' 
    {
        if (!is_variable_defined($1) || !is_variable_defined($4)) {
            fprintf(stderr, "Semantic Error: Undefined variable in reference assignment.\n");
            exit(1);
        }

        // LHS should be pointer to RHS type
        VarType lhs_type = TYPE_INVALID;
        VarType rhs_type = TYPE_INVALID;
        Symbol *sym = symbol_table;

        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) lhs_type = sym->type;
            if (!sym->is_function && strcmp(sym->name, $4) == 0) rhs_type = sym->type;
            sym = sym->next;
        }

        VarType expected_ptr_type = TYPE_INVALID;
        switch (rhs_type) {
            case TYPE_INT: expected_ptr_type = TYPE_INT_PTR; break;
            case TYPE_CHAR: expected_ptr_type = TYPE_CHAR_PTR; break;
            case TYPE_REAL: expected_ptr_type = TYPE_REAL_PTR; break;
            default:
                fprintf(stderr, "Semantic Error: Cannot take address of variable of type '%s'.\n", type_to_string(rhs_type));
                exit(1);
        }

        if (lhs_type != expected_ptr_type) {
            fprintf(stderr, "Semantic Error: cannot assign address of '%s' to variable of type '%s'.\n",
                    type_to_string(rhs_type), type_to_string(lhs_type));
            exit(1);
        }

        $$ = mknode("ref_assign", mknode($1, NULL, NULL), mknode($4, NULL, NULL));
    }
    | IDENTIFIER ASSIGN NULL_TOKEN ';' 
    {
        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType lhs_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                lhs_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (lhs_type != TYPE_INT_PTR && lhs_type != TYPE_CHAR_PTR && lhs_type != TYPE_REAL_PTR) {
            fprintf(stderr, "Semantic Error: 'null' can only be assigned to pointer types, got '%s'.\n", type_to_string(lhs_type));
            exit(1);
        }
        $$ = mknode("null_assign", mknode($1, NULL, NULL), mknode("null", NULL, NULL));
    }
    | IDENTIFIER '[' expression ']' ASSIGN INTEGER ';' {
        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }
        VarType index_type = infer_type($3);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }
        char int_str[20];
        sprintf(int_str, "%d", $6);
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode(int_str, NULL, NULL));
    }
    | IDENTIFIER '[' expression ']' ASSIGN STRING_LITERAL ';' {
        VarType index_type = infer_type($3);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        $$ = mknode("array_assign", mknode($1, $3, NULL), mknode($6, NULL, NULL));
    }
    | IDENTIFIER '[' expression ']' ASSIGN expression ';' {
        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }

        VarType index_type = infer_type($3);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }

        $$ = mknode("array_assign", mknode($1, $3, NULL), $6);
    }
    ;

if_statement:
    IF expression ':' block_statement 
    {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("if", $2, $4);
    }
    | IF expression ':' block_statement ELSE ':' block_statement 
    {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if-else' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("if-else", $2, mknode("then", $4, mknode("else", $7, NULL)));
    }
    | IF expression ':' block_statement ELIF expression ':' block_statement 
    {
        VarType if_cond_type = infer_type($2);
        VarType elif_cond_type = infer_type($6);
        if (if_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(if_cond_type));
            exit(1);
        }
        if (elif_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'elif' must be of type 'bool', got '%s'.\n", type_to_string(elif_cond_type));
            exit(1);
        }
        $$ = mknode("if-elif", $2, mknode("then", $4, mknode("elif-cond", $6, $8)));
    }
    | IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement 
    {
        VarType if_cond_type = infer_type($2);
        VarType elif_cond_type = infer_type($6);
        if (if_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(if_cond_type));
            exit(1);
        }
        if (elif_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'elif' must be of type 'bool', got '%s'.\n", type_to_string(elif_cond_type));
            exit(1);
        }
        $$ = mknode("if-elif-else", $2, mknode("then", $4, mknode("elif-cond", $6, mknode("elif-then", $8, mknode("else", $11, NULL)))));
    }
;

while_statement:
    WHILE expression ':' block_statement 
    {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'while' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("while", $2, $4);
    }
    ;

do_while_statement:
    DO ':' block_statement WHILE expression ';' 
    {
        VarType cond_type = infer_type($5);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'do-while' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("do-while", $3, mknode("cond", $5, NULL));
    }
    ;

for_statement:
    FOR for_header ':' block_statement {$$ = mknode("for", $2, $4);}
    | FOR for_header ':' var block_statement {$$ = mknode("for", $2, mknode("block", $5, $4));}
    ;

for_header:
    '(' IDENTIFIER ASSIGN expression ';' expression ';' update_exp ')' 
    {
        VarType cond_type = infer_type($6);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'for' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("for-header", mknode("init", mknode($2, NULL, NULL), $4), mknode("loop", $6, $8));
    }
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
    CALL IDENTIFIER '(' ')' 
    {
        if (!is_function_defined($2)) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' used before its definition.\n", $2);
            exit(1);
        }
        int expected = get_function_param_count($2);
        if (expected != 0) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' called with incorrect number of arguments (expected %d, got 0).\n", $2, expected);
            exit(1);
        }
        $$ = mknode("call", mknode($2, NULL, NULL), NULL);
    }
    | CALL IDENTIFIER '(' expr_list ')' 
    {
        if (!is_function_defined($2)) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' used before its definition.\n", $2);
            exit(1);
        }

        int count = 1;
        node* temp = $4;
        while (temp && strcmp(temp->token, "expr_list") == 0) 
        {
            count++;
            temp = temp->right;
        }

        Symbol* func = find_function_symbol($2);
        if (!func) {
            fprintf(stderr, "Semantic Error: Function '%s' not found.\n", $2);
            exit(1);
        }

        if (func->param_count != count) {
            fprintf(stderr, "Semantic Error: Function '%s' called with incorrect number of arguments (expected %d, got %d).\n",
                    $2, func->param_count, count);
            exit(1);
        }

        node* expr = $4;
        int i = 0;
        while (expr && i < func->param_count) {
            node* current_expr = (strcmp(expr->token, "expr_list") == 0) ? expr->left : expr;
            VarType actual_type = infer_type(current_expr);
            if (actual_type != func->param_types[i]) {
                fprintf(stderr, "Semantic Error: Function '%s', argument %d type mismatch (expected %s, got %s).\n",
                        $2, i + 1, type_to_string(func->param_types[i]), type_to_string(actual_type));
                exit(1);
            }
            expr = (strcmp(expr->token, "expr_list") == 0) ? expr->right : NULL;
            i++;
        }
        
        $$ = mknode("call", mknode($2, NULL, NULL), $4);
    }
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
    | STRING_LITERAL {$$ = mknode("STRING_LITERAL", mknode($1, NULL, NULL), NULL);}
    | CHAR_LITERAL {
        char char_str[2];
        char_str[0] = $1;
        char_str[1] = '\0';
        $$ = mknode(char_str, NULL, NULL);
    }
    | TRUE { $$ = mknode("TRUE", NULL, NULL); }
    | FALSE { $$ = mknode("FALSE", NULL, NULL); }
    | IDENTIFIER {
        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }
        $$ = mknode($1, NULL, NULL);
    }
    | expression PLUS expression {$$ = mknode("+", $1, $3);}
    | expression MINUS expression {$$ = mknode("-", $1, $3);}
    | expression MULT expression {$$ = mknode("*", $1, $3);}
    | expression DIV expression {$$ = mknode("/", $1, $3);}
    | expression MODULO expression {$$ = mknode("%", $1, $3);}
    | MINUS expression {$$ = mknode("unary-", $2, NULL);}
    | AMPERSAND IDENTIFIER {
        if (!is_variable_defined($2)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $2);
            exit(1);
        }
        $$ = mknode("&", mknode($2, NULL, NULL), NULL);
    }
    | AMPERSAND IDENTIFIER '[' expression ']' 
    {
        if (!is_variable_defined($2)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $2);
            exit(1);
        }
        VarType index_type = infer_type($4);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        $$ = mknode("&", mknode("index", mknode($2, NULL, NULL), $4), NULL);
    }
    | MULT IDENTIFIER {
        if (!is_variable_defined($2)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $2);
            exit(1);
        }
        $$ = mknode("deref", mknode($2, NULL, NULL), NULL);
    }
    | MULT expression {$$ = mknode("*", $2, NULL);}
    | | NOT expression 
    {
        VarType t = infer_type($2);
        if (t != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: '!' operator can only be used on bool, got '%s'.\n", type_to_string(t));
            exit(1);
        }
            $$ = mknode("not", $2, NULL);
    }
    | '(' expression ')' {$$ = $2;}
    | expression EQ expression {$$ = mknode("==", $1, $3);}
    | expression NE expression {$$ = mknode("!=", $1, $3);}
    | expression GE expression {$$ = mknode(">=", $1, $3);}
    | expression LE expression {$$ = mknode("<=", $1, $3);}
    | expression GT expression {$$ = mknode(">", $1, $3);}
    | expression LT expression {$$ = mknode("<", $1, $3);}
    | expression AND expression {$$ = mknode("and", $1, $3);}
    | expression OR expression {$$ = mknode("or", $1, $3);}
    | IDENTIFIER '[' expression ']' 
    {
        if (!is_variable_defined($1)) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $1);
            exit(1);
        }

        VarType index_type = infer_type($3);
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, $1) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }

        $$ = mknode("index", mknode($1, NULL, NULL), $3);
    }
    | '|' expression '|' {
        VarType inner_type = infer_type($2);
        if (inner_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: absolute value operator '||' can only be used on strings, got '%s'.\n", type_to_string(inner_type));
            exit(1);
        }
        $$ = mknode("strlen", $2, NULL);  // or name it "abs" if preferred
    }
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

int is_function_defined(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return 1; // Found
        }
        sym = sym->next;
    }
    return 0; // Not found
}

int is_variable_defined(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, name) == 0) {
            return 1;
        }
        sym = sym->next;
    }
    return 0;
}

int get_function_param_count(const char* name) 
{
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return sym->param_count;
        }
        sym = sym->next;
    }
    return -1; // Not found
}

int count_params(node* param_node) {
    int count = 0;
    node* temp = param_node;
    while (temp) {
        count++;
        temp = temp->right;
    }
    return count;
}

void extract_param_types(node* param_node, VarType* types) 
{
    int i = 0;

    void helper(node* n) {
        if (!n || i >= MAX_PARAMS) return;

        if (strcmp(n->token, "PARAMS") == 0) {
            helper(n->left);
            helper(n->right);
        } else {
            if (n->left && n->left->token)
                types[i++] = string_to_type(n->left->token);
            else
                types[i++] = TYPE_INVALID;
        }
    }

    helper(param_node);
}

VarType infer_type(node* expr) {
    if (!expr || !expr->token) return TYPE_INVALID;

    // Boolean literals
    if (strcmp(expr->token, "TRUE") == 0 || strcmp(expr->token, "FALSE") == 0) {
        return TYPE_BOOL;
    }

    // Integer literal
    if (strspn(expr->token, "0123456789") == strlen(expr->token)) {
        return TYPE_INT;
    }

    // Real literal (e.g., "3.14")
    if (strchr(expr->token, '.') != NULL) {
        return TYPE_REAL;
    }
    /*
    if (strlen(expr->token) == 1 && isprint(expr->token[0])) {
        return TYPE_CHAR;
    }
    */
    // String literal node
    if (strcmp(expr->token, "STRING_LITERAL") == 0 && expr->left && expr->left->token) {
        return TYPE_STRING;
    }

    // Unary minus
    if (strcmp(expr->token, "unary-") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_INT || t == TYPE_REAL) return t;
        fprintf(stderr, "Semantic Error: unary '-' expects int or real, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Logical NOT
    if (strcmp(expr->token, "not") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_BOOL) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: 'not' expects bool, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Absolute value
    if (strcmp(expr->token, "|") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_INT || t == TYPE_REAL || t == TYPE_STRING) return TYPE_INT;
        fprintf(stderr, "Semantic Error: '|' operator expects int, real, or string, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Binary arithmetic operators
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return (l == TYPE_REAL || r == TYPE_REAL) ? TYPE_REAL : TYPE_INT;
        }
        fprintf(stderr, "Semantic Error: '%s' operands must be int or real, got '%s' and '%s'.\n",
                expr->token, type_to_string(l), type_to_string(r));
        exit(1);
    }

    if (strcmp(expr->token, "%") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == TYPE_INT && r == TYPE_INT) return TYPE_INT;
        fprintf(stderr, "Semantic Error: '%%' operands must be int, got '%s' and '%s'.\n", type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Comparison operators
    if (strcmp(expr->token, ">") == 0 || strcmp(expr->token, "<") == 0 ||
        strcmp(expr->token, ">=") == 0 || strcmp(expr->token, "<=") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return TYPE_BOOL;
        }
        fprintf(stderr, "Semantic Error: Comparison requires int or real operands, got '%s' and '%s'.\n",
                type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Equality
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == r) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: Equality operands must match, got '%s' and '%s'.\n",
                type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Absolute value or string length operator (|expr| becomes strlen node)
    if (strcmp(expr->token, "strlen") == 0) {
        VarType inner = infer_type(expr->left);
        if (inner == TYPE_STRING)
            return TYPE_INT;
        return TYPE_INVALID;
    }

    // Logical operators
    if (strcmp(expr->token, "and") == 0 || strcmp(expr->token, "or") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == TYPE_BOOL && r == TYPE_BOOL) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: Logical '%s' expects bool operands, got '%s' and '%s'.\n",
                expr->token, type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Pointer dereference
    if (strcmp(expr->token, "deref") == 0 && expr->left) {
        VarType inner = infer_type(expr->left);
        switch (inner) {
            case TYPE_INT_PTR: return TYPE_INT;
            case TYPE_CHAR_PTR: return TYPE_CHAR;
            case TYPE_REAL_PTR: return TYPE_REAL;
            default:
                fprintf(stderr, "Semantic Error: unary '*' can only be applied to pointer types, got '%s'.\n", type_to_string(inner));
                exit(1);
        }
    }

    // Address-of
    if (strcmp(expr->token, "&") == 0 && expr->left) {
        VarType inner = infer_type(expr->left);
        if (inner == TYPE_INT) return TYPE_INT_PTR;
        if (inner == TYPE_CHAR) return TYPE_CHAR_PTR;
        if (inner == TYPE_REAL) return TYPE_REAL_PTR;
        fprintf(stderr, "Semantic Error: '&' expects int, char or real type, got '%s'.\n", type_to_string(inner));
        exit(1);
    }

    // Indexing
    if (strcmp(expr->token, "index") == 0 && expr->left) {
        return infer_type(expr->left);
    }

    // Function call
    if (strcmp(expr->token, "call") == 0 && expr->left && expr->left->token) {
        Symbol* sym = find_function_symbol(expr->left->token);
        if (sym) return sym->return_type;
    }

    // Variable lookup
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, expr->token) == 0) {
            return sym->type;
        }
        sym = sym->next;
    }

    if (strcmp(expr->token, "&") == 0 && expr->left) {
        VarType inner_type = TYPE_INVALID;

        if (strcmp(expr->left->token, "index") == 0) {
            // Check if this is &something[index]
            node* base = expr->left->left;
            Symbol* sym = symbol_table;
            while (sym) {
                if (!sym->is_function && strcmp(sym->name, base->token) == 0) {
                    inner_type = sym->type;
                    break;
                }
                sym = sym->next;
            }

            if (inner_type != TYPE_STRING) {
                fprintf(stderr, "Semantic Error: '&' can only be applied to indexed strings, got '%s'.\n", type_to_string(inner_type));
                exit(1);
            }

            return TYPE_CHAR_PTR;
        } else {
            // Check for &x
            Symbol* sym = symbol_table;
            while (sym) {
                if (!sym->is_function && strcmp(sym->name, expr->left->token) == 0) {
                    inner_type = sym->type;
                    break;
                }
                sym = sym->next;
            }

            if (inner_type == TYPE_INT) return TYPE_INT_PTR;
            if (inner_type == TYPE_CHAR) return TYPE_CHAR_PTR;
            if (inner_type == TYPE_REAL) return TYPE_REAL_PTR;

            fprintf(stderr, "Semantic Error: '&' operator can only be applied to variables of type int, char, or real, got '%s'.\n", type_to_string(inner_type));
            exit(1);
        }
    }

    return TYPE_INVALID;
}




const char* type_to_string(VarType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_CHAR: return "char";
        case TYPE_REAL: return "real";
        case TYPE_STRING: return "string";
        case TYPE_BOOL: return "bool";
        case TYPE_INT_PTR: return "int*";
        case TYPE_CHAR_PTR: return "char*";
        case TYPE_REAL_PTR: return "real*";
        default: return "unknown";
    }
}

Symbol* find_function_symbol(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}
