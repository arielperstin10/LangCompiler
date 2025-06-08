%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    //SEMANTIC CHEK SADSADA
    #define MAX_PARAMS 10

    int yylex();
    int yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    
    typedef enum {
        TYPE_INT, TYPE_CHAR, TYPE_REAL, TYPE_STRING, TYPE_BOOL,
        TYPE_INT_PTR, TYPE_CHAR_PTR, TYPE_REAL_PTR, TYPE_INVALID
    } VarType;

    extern int yydebug;
    typedef struct Symbol {
        char* name;
        VarType type;
        int is_function;
        VarType return_type;
        VarType param_types[MAX_PARAMS];
        int param_count;
        int scope_level;
        int function_scope_id;
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
    void print_symbol_table();
    void insert_parameters(node* param_iter);
    static inline void push_func_scope(void);
    static inline void pop_func_scope(void);
    int check_no_return_statements(node* stmt);
    
    // 3AC generation functions
    void generate_3ac(node* ast);

    node* root = NULL;
    Symbol* symbol_table = NULL;
    int current_scope_level = 0;
    int main_count = 0;
    int last_param_number = 0;
    int function_scope_counter = 1;
    int current_function_scope_id = 0;
    int func_scope_stack[128];
    int func_scope_top = -1;
    int is_semantic_error = 0;
%}

%debug
%start code

%union {
    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;
    VarType typeVal;
    VarType paramList[MAX_PARAMS];
}


%token <intVal> INTEGER
%token <realVal> REAL
%token <charVal> CHAR_LITERAL
%token <stringVal> STRING_LITERAL IDENTIFIER

%token BOOL CHAR INT REAL_TYPE STRING INT_PTR CHAR_PTR REAL_PTR TYPE MODULO
%token IF ELIF ELSE WHILE FOR VAR RETURN NULL_TOKEN DO RETURNS BEGIN_TOKEN END DEF CALL AND NOT OR
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
%nonassoc IFX
%nonassoc ELSE ELIF

%type <nodePtr> code functions function parameters parameter_list parameter var declaration_list 
%type <nodePtr> declaration type id_list statements statement assignment_statement  
%type <nodePtr>  for_header update_exp 
%type <nodePtr> block_statement scope_entry return_statement function_call_statement function_call expression scoped_block
%type <nodePtr> expr_list nested_function
%type <nodePtr> stmt_opt elif_unmatched elif_chain unmatched_if matched_if unmatched_statement matched_statement

%%

code: functions {root = mknode("code", $1, NULL); $$ = root;};

functions: function {$$ = $1;}
        | function functions {$$ = mknode("functions", $1, $2);}
        ;

function: 
        DEF MAIN '(' reset_param_counter parameters ')' ':'
        {
            if ($5 != NULL) {
                is_semantic_error = 1;
                yyerror("Semantic Error: _main_ must not have parameters.");
                YYERROR;
            }
        } var BEGIN_TOKEN statements END
        {
            current_function_scope_id = function_scope_counter++;
            if (check_no_return_statements($11)) {
                YYERROR;
            }
            insert_symbol("_main_", TYPE_INVALID, 1, TYPE_INVALID, NULL, 0);
            enter_scope();    

            $$ = mknode("FUNC",
                        mknode("main", NULL, $9),
                        mknode("body", $11, NULL));
            exit_scope();    
        }
        | DEF IDENTIFIER '(' reset_param_counter parameters ')' ':' RETURNS type
        {   
            current_function_scope_id = function_scope_counter++;
            VarType declared_type  = string_to_type($9->token);
            VarType param_types[MAX_PARAMS];
            int     param_count    = count_params($5);
            extract_param_types($5, param_types);
            insert_symbol($2, TYPE_INVALID, 1, declared_type, param_types, param_count);
            enter_scope();
            insert_parameters($5);
        }
        var BEGIN_TOKEN statements END
        {   
            VarType declared_type = string_to_type($9->token);
            node* last_stmt = $13;
            while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->left)
                last_stmt = last_stmt->left; 
            node* final = last_stmt;
            if (!final || (strcmp(final->token,"return_val")!=0 &&
                        strcmp(final->token,"return_void")!=0))
            {
                yyerror("Error: function with RETURNS must end with a return statement");
                YYERROR;
            }
            if (strcmp($2,"_main_")==0)
            {
                yyerror("Semantic Error: _main_ must not return a value.");
                YYERROR;
            }
            if (declared_type == TYPE_STRING)
            {
                fprintf(stderr,
                "Semantic Error: functions cannot return type 'string'.\n");
                exit(1);
            }
            if (strcmp(final->token,"return_void")==0)
            {
                fprintf(stderr,
                "Semantic Error: function declared to return '%s' but returned nothing.\n",
                type_to_string(declared_type));
                exit(1);
            }
            VarType actual_type = infer_type(final->left);
            if (actual_type != declared_type)
            {
                fprintf(stderr,
                "Semantic Error: return type mismatch — expected '%s', got '%s'.\n",
                type_to_string(declared_type), type_to_string(actual_type));
                exit(1);
            }

            $$ = mknode("FUNC",
                        mknode($2, $5, mknode("ret", $9, $11)),
                        mknode("body", $13, NULL));
            exit_scope();     
        }
        | DEF IDENTIFIER '(' reset_param_counter parameters ')' ':'
        {  
            current_function_scope_id = function_scope_counter++;
            VarType param_types[MAX_PARAMS];
            int     param_count = count_params($5);
            extract_param_types($5, param_types);
            insert_symbol($2, TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);
            enter_scope();
            insert_parameters($5);
        }
        var BEGIN_TOKEN statements END
        {   
            node* last_stmt = $11;
            while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->left)
                last_stmt = last_stmt->left; 

            if (last_stmt && strcmp(last_stmt->token, "return_val") == 0)
            {
                yyerror("Error: function without RETURNS must not have a return statement");
                YYERROR;
            }
            if (strcmp($2,"_main_")==0 && $5!=NULL)
            {
                yyerror("Semantic Error: _main_ must not have parameters.");
                YYERROR;
            }

            $$ = mknode("FUNC",
                        mknode($2, $5, NULL),
                        mknode("body", $11, NULL));
            exit_scope();
        }
        ;

reset_param_counter: /* empty */ {last_param_number = 0;};

parameters: /* empty */ {$$ = NULL;}
        | parameter_list {$$ = $1;}
        ;

parameter_list: parameter ';' parameter_list {$$ = mknode("PARAMS", $1, $3);}
        | parameter {$$ = $1;}
        ;

parameter: IDENTIFIER type ':' IDENTIFIER {
    if (strncmp($1, "par", 3) != 0) {
        yyerror("Error: parameter names must start with 'par'.");
        YYERROR;
    }
    fprintf(stderr, "[DEBUG] Matched parameter: %s of type %s with name %s\n", 
            $1, $2->token, $4);

    int current_num = atoi(&$1[3]);
    if (current_num != last_param_number + 1) {
        is_semantic_error = 1;
        yyerror("Semantic Error: parameter numbers must be in strictly increasing order (par1, par2, ...).");
        YYERROR;
    }

    last_param_number = current_num;

    $$ = mknode("parameter", mknode($2->token, NULL, NULL), mknode($4, NULL, NULL));
};

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

statements
    : /* empty */                                    { $$ = NULL;                                    }
    | statements statement                           { $$ = mknode("statements", $2, $1);            }
    | statements nested_function                     { $$ = mknode("statements", $2, $1);            }
    ;


nested_function : 
        DEF IDENTIFIER '(' reset_param_counter parameters ')' ':' RETURNS type
        {
            push_func_scope();                 
            current_function_scope_id = function_scope_counter++;
            VarType ret_type = string_to_type($9->token);
            VarType param_types[MAX_PARAMS];
            int param_count  = count_params($5);
            extract_param_types($5, param_types);
            insert_symbol($2, TYPE_INVALID, 1, ret_type, param_types, param_count);
            enter_scope();
            insert_parameters($5);
        }
        var BEGIN_TOKEN statements END
        {
            $$ = mknode("nested_func", mknode($2, $5, mknode("ret", $9, $11)), mknode("body", $13, NULL));
            exit_scope();
            pop_func_scope();                    
        }
        | DEF IDENTIFIER '(' reset_param_counter parameters ')' ':'
        {
            push_func_scope();                  
            current_function_scope_id = function_scope_counter++;
            VarType param_types[MAX_PARAMS];
            int param_count = count_params($5);
            extract_param_types($5, param_types);
            insert_symbol($2, TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);
            enter_scope();
            insert_parameters($5);
        }
        var BEGIN_TOKEN statements END
        {
            $$ = mknode("nested_func", mknode($2, $5, NULL), mknode("body", $11, NULL));
            exit_scope();
            pop_func_scope();                   
        }
        ;

statement:
    matched_statement {$$ = $1;}
  | unmatched_statement {$$ = $1;}
  ;

  matched_statement:
    matched_if
  | WHILE expression ':' matched_statement {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'while' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("while", $2, $4);
    }
  | FOR for_header ':' matched_statement { $$ = mknode("for", $2, $4); }
  | DO ':' matched_statement WHILE expression ';' {
        VarType cond_type = infer_type($5);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'do-while' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("do-while", $3, mknode("cond", $5, NULL));
    }
  | block_statement
  | assignment_statement
  | return_statement
  | function_call_statement
  ;

unmatched_statement:
    unmatched_if
  | WHILE expression ':' unmatched_statement {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'while' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("while", $2, $4);
    }
  | FOR for_header ':' unmatched_statement { $$ = mknode("for", $2, $4); }
  | DO ':' unmatched_statement WHILE expression ';' {
        VarType cond_type = infer_type($5);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'do-while' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("do-while", $3, mknode("cond", $5, NULL));
    }
  ;

matched_if:
    IF expression ':' matched_statement ELSE ':' matched_statement {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'if' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("if-full", mknode("cond", $2, NULL), mknode("then", $4, mknode("else", $7, NULL)));
    }
  | IF expression ':' matched_statement elif_chain %prec IFX {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'if' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("if-elif", mknode("cond", $2, NULL), mknode("then", $4, $5));
    }
  ;

unmatched_if:   
    IF expression ':' statement %prec IFX {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'if' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
    $$ = mknode("if", $2, $4);
    }
    | IF expression ':' matched_statement elif_unmatched {
        $$ = mknode("if-elif", mknode("cond", $2, NULL), mknode("then", $4, $5));
    }
  ;

elif_chain:
    ELIF expression ':' matched_statement %prec IFX {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'elif' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("elif", mknode("cond", $2, NULL), $4);
    }
    | ELIF expression ':' matched_statement elif_chain {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'elif' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("elif", mknode("cond", $2, NULL), mknode("then", $4, $5));
    }
    | ELIF expression ':' matched_statement ELSE ':' matched_statement
    {
        $$ = mknode("elif-else", mknode("cond", $2, NULL), mknode("then", $4, mknode("else", $7, NULL)));
    }
  ;

elif_unmatched:
    ELIF expression ':' unmatched_statement %prec IFX {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'elif' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("elif", mknode("cond", $2, NULL), $4);
    }
  | ELIF expression ':' matched_statement elif_unmatched {
        VarType cond_type = infer_type($2);
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: 'elif' expects bool, got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        $$ = mknode("elif", mknode("cond", $2, NULL), mknode("then", $4, $5));
    }
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

        if (rhs_type == TYPE_INVALID && strcmp($3->token, "null") == 0) {
            if (lhs_type != TYPE_INT_PTR && lhs_type != TYPE_CHAR_PTR && lhs_type != TYPE_REAL_PTR) {
                fprintf(stderr, "Semantic Error: 'null' can only be assigned to pointer types, got '%s'.\n", type_to_string(lhs_type));
                exit(1);
            }
        } else if (lhs_type != rhs_type) {
            if (lhs_type == TYPE_REAL && rhs_type == TYPE_INT) {
                fprintf(stderr, "[INFO] Implicitly promoting 'int' to 'real' for assignment.\n");
            } else if (lhs_type == TYPE_INT && rhs_type == TYPE_REAL) {
                fprintf(stderr, "[INFO] Implicitly demoting 'real' to 'int' for assignment.\n");
            } else {
                fprintf(stderr, "Semantic Error: cannot assign '%s' to variable of type '%s'.\n",
                        type_to_string(rhs_type), type_to_string(lhs_type));
                exit(1);
            }
        }

        $$ = mknode("assign", mknode($1, NULL, NULL), $3);
    }
    | MULT IDENTIFIER ASSIGN expression ';' 
    {
        if (!is_variable_defined($2)) 
        {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", $2);
            exit(1);
        }

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
    | IDENTIFIER '[' expression ']' ASSIGN expression ';' 
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

        $$ = mknode("array_assign", mknode($1, $3, NULL), $6);
    };










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

scope_entry: /* nothing */ { enter_scope(); $$ = NULL; };

scoped_block
    : scope_entry var BEGIN_TOKEN stmt_opt END
        {
            exit_scope();
            $$ = mknode("block", $4 , $2);
        }
    ;

stmt_opt: statements { $$ = $1; };

block_statement:
    scoped_block { $$ = $1; }
;

return_statement:
    RETURN expression ';' {$$ = mknode("return_val", $2, NULL);}
    | RETURN ';' {$$ = mknode("return_void", NULL, NULL);}
    ;

function_call_statement:
    function_call ';' {$$ = $1;}
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
        char buf[3];
        snprintf(buf, sizeof(buf), "%c", $1);
        $$ = mknode("CHAR_LITERAL", mknode(buf, NULL, NULL), NULL);
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
    | MULT expression {$$ = mknode("*", $2, NULL);}
    | NOT expression 
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
    //yydebug = 1;
    if (yyparse() == 0) {
        if (main_count == 0) 
        {
            fprintf(stderr, "Semantic  Error: Missing '_main_' function.\n");
            return 1;
        } else if (main_count > 1) 
        {
            fprintf(stderr, "Semantic Error: Multiple '_main_' functions are not allowed.\n");
            return 1;
        }
        
        // Generate 3AC code
        generate_3ac(root);
        printf("3AC code generated in output.ac3\n");
        
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
    if (is_semantic_error) {
        fprintf(stderr, "%s\n", s);  
        is_semantic_error = 0;       
    } else {
        fprintf(stderr, "Error: %s at line %d near token '%s'\n", s, yylineno, yytext);
    }
    return 0;
}

void visualize_ast(node* root, const char* branch_prefix, int is_left_branch) {
    if (!root) return;

    // Flatten PARAMS node for pretty printing
    if (strcmp(root->token, "PARAMS") == 0) {
        printf("%s", branch_prefix);
        printf(is_left_branch ? "├── " : "└── ");
        printf("PARAMS\n");

        char child_prefix[1024];
        snprintf(child_prefix, sizeof(child_prefix), "%s%s", 
                 branch_prefix, is_left_branch ? "│   " : "    ");

        node* current = root;
        while (current) {
            if (current->token && strcmp(current->token, "PARAMS") == 0 && current->left) {
                visualize_ast(current->left, child_prefix, 1);
                current = current->right;
            } else {
                visualize_ast(current, child_prefix, 0);
                break;
            }
        }
        return;
    }

    // Regular node printing
    printf("%s", branch_prefix);
    printf(is_left_branch ? "├── " : "└── ");
    printf("%s\n", root->token);

    char child_prefix[1024];
    snprintf(child_prefix, sizeof(child_prefix), "%s%s", 
             branch_prefix, is_left_branch ? "│   " : "    ");

    if (root->left && root->right) {
        visualize_ast(root->left, child_prefix, 1);
        visualize_ast(root->right, child_prefix, 0);
    } else if (root->left) {
        visualize_ast(root->left, child_prefix, 0);
    } else if (root->right) {
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
        if (strcmp(sym->name, name) == 0 && sym->is_function && is_function) {
            fprintf(stderr, "Semantic Error: Redefinition of function '%s'.\n", name);
            exit(1);
        }
        if (!is_function && sym->scope_level == current_scope_level && strcmp(sym->name, name) == 0 && sym->function_scope_id == current_function_scope_id) {
            fprintf(stderr, "Semantic Error: Redefinition of variable '%s' in the same scope.\n", name);
            exit(1);
        }
        sym = sym->next;
    }

    // Create new symbol
    Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->function_scope_id = current_function_scope_id;
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

    fprintf(stderr, "[INSERT] Added symbol '%s' | Type: %s | Scope: %d | FuncScopeID: %d | is_function: %d\n",
            name, type_to_string(type), current_scope_level, current_function_scope_id, is_function);


    // Handle main function count
    if (is_function && strcmp(name, "_main_") == 0) {
        main_count++;
    }
}

void enter_scope() {
    current_scope_level++;
}

void exit_scope() {
    Symbol** curr = &symbol_table;
    while (*curr) {
        if ((*curr)->scope_level == current_scope_level) {
            Symbol* to_delete = *curr;
            *curr = (*curr)->next;  // unlink
            free(to_delete->name);
            free(to_delete);
        } else {
            curr = &(*curr)->next;
        }
    }
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
        if (!sym->is_function &&
            strcmp(sym->name, name) == 0 &&
            sym->scope_level <= current_scope_level &&
            sym->function_scope_id == current_function_scope_id) {
            return 1;
        }
        sym = sym->next;
    }

    // Debug output when variable not found
    fprintf(stderr, "[DEBUG] Variable '%s' not found.\n", name);
    fprintf(stderr, "[DEBUG] Current Scope: %d | Function Scope ID: %d\n", current_scope_level, current_function_scope_id);
    print_symbol_table();  // 🔍 dump the whole table

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
    if (!param_node) return 0;
    if (strcmp(param_node->token, "PARAMS") == 0)
        return count_params(param_node->left) + count_params(param_node->right);
    return 1;
}

void extract_param_types(node* param_node, VarType* types) {
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

    if (strcmp(expr->token, "CHAR_LITERAL") == 0 && expr->left && expr->left->token) {
        return TYPE_CHAR;
    }

    // String literal node
    if (strcmp(expr->token, "STRING_LITERAL") == 0 && expr->left && expr->left->token) {
        return TYPE_STRING;
    }

    // Binary arithmetic operators
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0 ||
        strcmp(expr->token, "%") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        
        // Special handling for modulo
        if (strcmp(expr->token, "%") == 0) {
            if (l == TYPE_INT && r == TYPE_INT) return TYPE_INT;
            fprintf(stderr, "Semantic Error: '%%' operands must be int, got '%s' and '%s'.\n", type_to_string(l), type_to_string(r));
            exit(1);
        }
        
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return (l == TYPE_REAL || r == TYPE_REAL) ? TYPE_REAL : TYPE_INT;
        }
        fprintf(stderr, "Semantic Error: '%s' operands must be int or real, got '%s' and '%s'.\n",
                expr->token, type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Comparison operations
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0 ||
        strcmp(expr->token, "<") == 0 || strcmp(expr->token, ">") == 0 ||
        strcmp(expr->token, "<=") == 0 || strcmp(expr->token, ">=") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return TYPE_BOOL;
        }
        if (l == r) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: Comparison operands type mismatch '%s' and '%s'.\n",
                type_to_string(l), type_to_string(r));
        exit(1);
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


void print_symbol_table() {
    printf("\n---- Symbol Table ----\n");
    Symbol* sym = symbol_table;
    while (sym) {
        printf("Name: %-10s | Type: %-8s | Func: %d | RetType: %-8s | Params: %d | Scope: %d | FuncScopeID: %d\n",
            sym->name,
            type_to_string(sym->type),
            sym->is_function,
            type_to_string(sym->return_type),
            sym->param_count,
            sym->scope_level,
            sym->function_scope_id);
        sym = sym->next;
    }
    printf("----------------------\n");
}

void insert_parameters(node* param_iter) {
    if (!param_iter) return;

    if (strcmp(param_iter->token, "PARAMS") == 0) {
        insert_parameters(param_iter->left);
        insert_parameters(param_iter->right);
    } else if (strcmp(param_iter->token, "parameter") == 0) {
        if (param_iter->left && param_iter->right) {
            VarType param_type = string_to_type(param_iter->left->token);
            char* param_name = param_iter->right->token;
            fprintf(stderr, "[INSERT] Recursive Param '%s' of type %s\n", param_name, type_to_string(param_type));
            insert_symbol(param_name, param_type, 0, TYPE_INVALID, NULL, 0);
        }
    } else {
        fprintf(stderr, "[WARNING] Unexpected param_iter->token = %s\n", param_iter->token);
    }
}

static inline void push_func_scope(void)
{
    func_scope_stack[++func_scope_top] = current_function_scope_id;
}

static inline void pop_func_scope(void)
{
    current_function_scope_id = func_scope_stack[func_scope_top--];
}

int check_no_return_statements(node* stmt) {
    if (!stmt) return 0;

    // If it's a nested function, don't check its subtree
    if (strcmp(stmt->token, "nested_func") == 0)
        return 0;

    if (strcmp(stmt->token, "return_val") == 0) {
        is_semantic_error = 1;
        yyerror("Semantic Error: _main_ must not contain return statements.");
        return 1;
    }

    return check_no_return_statements(stmt->left) || check_no_return_statements(stmt->right);
}

// ==================== 3AC GENERATION ====================
/* =========================  3-ADDRESS-CODE GENERATOR  =========================
   Comprehensive 3AC generation module adapted for this compiler's AST structure
*/
#include <stdarg.h>

/* ---------- instruction list infrastructure ---------- */
typedef struct Instr {
    char *text;
    struct Instr *next;
} Instr;

static Instr *codeHead = NULL, *codeTail = NULL;
static int    tempCnt  = 0;
static int    labelCnt = 1;

static char *newTemp () { char b[32]; sprintf(b,"t%d", tempCnt++);  return strdup(b); }
static char *newLabel() { char b[32]; sprintf(b,"L%d", labelCnt++); return strdup(b); }

static void emit(const char *fmt, ...)
{
    va_list ap; char buf[128];
    va_start(ap, fmt); vsnprintf(buf, sizeof(buf), fmt, ap); va_end(ap);

    Instr *n = (Instr *)malloc(sizeof(Instr));
    n->text = strdup(buf); n->next = NULL;
    if (!codeHead) codeHead = codeTail = n;
    else           codeTail = codeTail->next = n;
}

void dumpCode(FILE *out)
{
    const char *IND = "    ";                 /* 4-spaces indentation */

    for (Instr *p = codeHead; p; p = p->next) {
        const char *txt = p->text;
        size_t      len = strlen(txt);

        /* LABEL or function header - keep left-aligned */
        if (len > 0 && txt[len - 1] == ':')
            fprintf(out, "%s\n", txt);
        else
            fprintf(out, "%s%s\n", IND, txt); /* other instructions indented */
    }
}

/* ---------- helpers --------------------------------------------------------- */
static int isLiteral(const char *tok)
{
    if (!tok) return 0;
    // Check if it's a number (integer or float)
    char *endptr;
    strtod(tok, &endptr);
    return *endptr == '\0' || !strcmp(tok,"TRUE") || !strcmp(tok,"FALSE");
}

/* For our AST, literal values are often directly in the token */
static const char *literalValue(node *lit)
{
    if (!lit || !lit->token) return "0";
    return lit->token;
}

/* fast sizeof for frame calculation (4-byte default) */
static int sizeofType(const char *t)
{
    if (!t) return 4;
    if (!strcasecmp(t,"real") || !strcasecmp(t,"real*")) return 8;
    if (!strcasecmp(t,"string")) return 8;
    return 4;   /* int, char, bool, int*, char* … */
}

/* ===== TEMP-SIZE TRACKING =========================================== */
static int tempBytesInFunc = 0;          /* reset at each genFunction */

/* Simple type inference for expressions */
static const char* inferExprType(node *e)
{
    if (!e || !e->token) return "int";
    
    // Check if it's a literal number
    if (isLiteral(e->token)) {
        if (strchr(e->token, '.')) return "real";
        return "int";
    }
    
    if (!strcmp(e->token, "TRUE") || !strcmp(e->token, "FALSE")) return "bool";
    
    // For variables, look up in symbol table
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, e->token) == 0) {
            return type_to_string(sym->type);
        }
        sym = sym->next;
    }
    
    return "int"; // default
}

/* byte size of the value produced by expression e */
static int resultSize(node *e)
{
    const char *t = inferExprType(e);    /* "int", "real*", …        */
    if (!t) return 4;
    if (!strcasecmp(t,"real") || !strcasecmp(t,"real*") || !strcasecmp(t,"string"))
        return 8;                       /* 8-byte values              */
    return 4;                           /* everything else            */
}

/* allocate a temp for expression e and remember its size */
static char *makeTempFor(node *e)
{
    tempBytesInFunc += resultSize(e);
    char buf[32]; sprintf(buf,"t%d", tempCnt++);
    return strdup(buf);
}

/* Simple symbol lookup */
static int lookupSymbol(const char *name)
{
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, name) == 0) {
            return 1;
        }
        sym = sym->next;
    }
    return 0;
}

/* modify "BeginFunc 0" with real byte count */
static void patchBeginSize(Instr *beginLine, int bytes)
{
    char buf[16]; sprintf(buf, "%d", bytes);
    /* "BeginFunc " is 10 chars, overwrite from there */
    strcpy(beginLine->text + 10, buf);
}

/* ---------- forward decls for mutually recursive generators --------------- */
static char *genExpr(node *e);
static void  genStmt(node *s);

/* ---------- expression → 3AC (returns temp / var name) -------------------- */
/* ===== helpers for conditions ===== */
static int isCmpOp(const char *t)
{
    return !strcmp(t,"==") || !strcmp(t,"!=") ||
           !strcmp(t,"<")  || !strcmp(t,">")  ||
           !strcmp(t,"<=") || !strcmp(t,">=");
}

/* returns operand – if it's a literal returns the value itself, otherwise calls genExpr */
static char *genOperand(node *e)
{
    if (isLiteral(e->token))           /* number/character/string/TRUE/FALSE/NULL */
        return strdup(literalValue(e));/* don't create temporary */
    return genExpr(e);                 /* everything else – as usual */
}

static char *genExpr(node *e)
{
    if (!e) return strdup("0");

    /* 1. terminals ---------------------------------------------------- */
    if (isLiteral(e->token)) {
        char *t = makeTempFor(e);
        emit("%s = %s", t, literalValue(e));
        return t;
    }
    if (!strcmp(e->token,"TRUE")) {
        char *t = makeTempFor(e);
        emit("%s = 1", t);
        return t;
    }
    if (!strcmp(e->token,"FALSE")) {
        char *t = makeTempFor(e);
        emit("%s = 0", t);
        return t;
    }
    if (!strcmp(e->token,"null")) {
        char *t = makeTempFor(e);
        emit("%s = 0", t);
        return t;
    }
    if (lookupSymbol(e->token)) {          /* variable / param */
        return strdup(e->token);           /* already stored */
    }

    /* 2. unary -------------------------------------------------------- */
    if (!strcmp(e->token,"unary-")) {
        char *v = genExpr(e->left);
        char *t = makeTempFor(e); 
        emit("%s = - %s", t, v); 
        return t;
    }
    if (!strcmp(e->token,"not")) {
        char *v = genExpr(e->left);
        char *t = makeTempFor(e); 
        emit("%s = ! %s", t, v); 
        return t;
    }
    if (!strcmp(e->token,"&")) {
        char *v = genExpr(e->left);
        char *t = makeTempFor(e); 
        emit("%s = & %s", t, v); 
        return t;
    }
    if (!strcmp(e->token,"*") && !e->right) { // unary dereference
        char *p = genExpr(e->left);
        char *t = makeTempFor(e); 
        emit("%s = * %s", t, p); 
        return t;
    }

    /* 3. binary arithmetic / logic ----------------------------------- */
    const char *binOps[] = {"+","-","*","/","%","and","or",
                            "==","!=","<",">","<=",">="};
    for (size_t i = 0; i < sizeof(binOps)/sizeof(binOps[0]); ++i) {
        if (!strcmp(e->token, binOps[i])) {
            char *l = genExpr(e->left);
            char *r = genExpr(e->right);
            char *t = makeTempFor(e);
            emit("%s = %s %s %s", t, l, binOps[i], r);
            return t;
        }
    }

    /* 4. array indexing ---------------------------------------------- */
    if (!strcmp(e->token,"index")) {
        char *base = genExpr(e->left);   /* IDENT gives name */
        char *idx  = genExpr(e->right);
        char *t    = makeTempFor(e);
        emit("%s = %s [ %s ]", t, base, idx);
        return t;
    }

    /* 5. function call ----------------------------------------------- */
    if (!strcmp(e->token,"call")) {
        const char *fname = e->left->token;

        /* gather params into stack[] for reverse push                  */
        node *stack[32]; int top = 0;
        for (node *p = e->right; p; p = (!strcmp(p->token,"expr_list")) ? p->right : NULL)
            stack[top++] = (!strcmp(p->token,"expr_list")) ? p->left : p;

        int bytes = 0;
        for (int i = top - 1; i >= 0; --i) {
            char *val = genExpr(stack[i]);
            emit("PushParam %s", val);
            bytes += sizeofType(inferExprType(stack[i]));
        }

        char *ret = makeTempFor(e);
        emit("%s = LCall %s", ret, fname);
        if (bytes) emit("PopParams %d", bytes);
        return ret;
    }

    // For variables not found in symbol table, return as-is (might be identifier)
    return strdup(e->token);
}

/* ---------- statement generator ---------------------------------------- */
static void genStmt(node *s)
{
    if (!s || !s->token) return;

    /* list of statements */
    if (!strcmp(s->token,"statements")) { 
        genStmt(s->right); // Process in reverse order (right first)
        genStmt(s->left); 
        return; 
    }

    /* assignments ----------------------------------------------------- */
    if (!strcmp(s->token,"assign")) {
        char *rhs = genExpr(s->right);
        emit("%s = %s", s->left->token, rhs);
        return;
    }
    if (!strcmp(s->token,"pointer_assign")) {
        char *lhs = genExpr(s->left);
        char *rhs = genExpr(s->right);
        emit("* %s = %s", lhs, rhs);
        return;
    }
    if (!strcmp(s->token,"array_assign")) {
        char *idx = genExpr(s->left->right);
        char *rhs = genExpr(s->right);
        emit("%s [ %s ] = %s", s->left->token, idx, rhs);
        return;
    }
    if (!strcmp(s->token,"null_assign")) { 
        emit("%s = 0", s->left->token); 
        return; 
    }

    /* return ---------------------------------------------------------- */
    if (!strcmp(s->token,"return_val")) { 
        emit("Return %s", genExpr(s->left)); 
        return; 
    }

    /* block ----------------------------------------------------------- */
    if (!strcmp(s->token,"block")) { 
        genStmt(s->left); 
        return; 
    }

    /* IF -------------------------------------------------------------- */
    if (!strcmp(s->token,"if")) {
        node *c = s->left;                             /* condition */
        char *Ltrue = newLabel(), *Lend = newLabel();

        if (isCmpOp(c->token)) {                       /* condition like a < 5 etc */
            char *lhs = genOperand(c->left);
            char *rhs = genOperand(c->right);
            emit("if %s %s %s goto %s", lhs, c->token, rhs, Ltrue);
            emit("goto %s", Lend);
        } else {                                       /* general condition */
            char *t = genExpr(c);
            emit("if %s == 0 goto %s", t, Lend);
            emit("goto %s", Ltrue);
        }

        emit("%s:", Ltrue);
        genStmt(s->right);
        emit("%s:", Lend); 
        return;
    }

    if (!strcmp(s->token,"if-full")) {
        node *cond_wrapper = s->left;          // "cond" wrapper node
        node *cond_node = cond_wrapper->left;  // actual condition (==, !=, etc.)
        node *then_node = s->right->left;  
        node *else_node = s->right->right->left; 
        
        char *Lthen = newLabel(), *Lelse = newLabel(), *Lend = newLabel();

        if (isCmpOp(cond_node->token)) {
            char *lhs = genOperand(cond_node->left);
            char *rhs = genOperand(cond_node->right);
            emit("if %s %s %s goto %s", lhs, cond_node->token, rhs, Lthen);
            emit("goto %s", Lelse);
        } else {
            char *t = genExpr(cond_node);
            emit("if %s != 0 goto %s", t, Lthen);
            emit("goto %s", Lelse);
        }

        emit("%s:", Lthen);  
        genStmt(then_node);  
        emit("goto %s", Lend);
        emit("%s:", Lelse);  
        genStmt(else_node); 
        emit("%s:", Lend);   
        return;
    }

    /* WHILE ----------------------------------------------------------- */
    if (!strcmp(s->token,"while")) {
        char *Lcond = newLabel(), *Lbody = newLabel(), *Lend = newLabel();
        emit("%s:", Lcond);

        node *c = s->left;
        if (isCmpOp(c->token)) {
            char *lhs = genOperand(c->left);
            char *rhs = genOperand(c->right);
            emit("if %s %s %s goto %s", lhs, c->token, rhs, Lbody);
            emit("goto %s", Lend);
        } else {
            char *t = genExpr(c);
            emit("if %s != 0 goto %s", t, Lbody);
            emit("goto %s", Lend);
        }

        emit("%s:", Lbody);  
        genStmt(s->right);   
        emit("goto %s", Lcond);
        emit("%s:", Lend);   
        return;
    }

    /* DO-WHILE -------------------------------------------------------- */
    if (!strcmp(s->token,"do-while")) {
        char *Ls = newLabel();
        emit("%s:", Ls); 
        genStmt(s->left);
        emit("if %s != 0 goto %s", genExpr(s->right->left), Ls); 
        return;
    }

    /* FOR ------------------------------------------------------------- */
    if (!strcmp(s->token,"for")) {
        node *h = s->left;
        node *initVar   = h->left->left;     /* IDENT */
        node *initExpr  = h->left->right;
        node *condExpr  = h->right->left;
        node *updateExp = h->right->right;

        char *Lc = newLabel(), *Le = newLabel();

        emit("%s = %s", initVar->token, genExpr(initExpr));
        emit("%s:", Lc);
        emit("if %s == 0 goto %s", genExpr(condExpr), Le);
        genStmt(s->right);
        emit("%s = %s", updateExp->left->token, genExpr(updateExp->right));
        emit("goto %s", Lc);
        emit("%s:", Le); 
        return;
    }
    
    /* function call as statement */
    if (!strcmp(s->token,"call")) {
        genExpr(s); // Call genExpr to handle the function call
        return;
    }
}

/* ---------- per-function + global traversal ---------------------------- */
static void genFunction(node *f)
{
    if (!f || strcmp(f->token, "FUNC") != 0) return;
    
    node *header = f->left;
    const char *fname = header->token;          
    
    // Convert _main_ to main for output
    if (strcmp(fname, "_main_") == 0) {
        fname = "main";
    }
    
    emit("\n%s:", fname);
    emit("BeginFunc 0");                         /* placeholder */
    Instr *beginLine = codeTail;
    tempBytesInFunc  = 0;          /* start counting for this func */

    node *body = f->right;  // body node
    
    /* statements are in body->left (the statements node) */
    node *stmts = body->left;

    genStmt(stmts);

    /* frame size = locals + total temp bytes we just counted */
    int tempsBytes = tempBytesInFunc;

    /* count local decls - look for VAR declarations in the body structure */
    int localsBytes = 0;
    
    // Look for VAR in function header (for functions with parameters and VAR)
    if (header->right && header->right->right && strcmp(header->right->right->token, "VAR") == 0) {
        node *varNode = header->right->right;
        node *decls = varNode->left;
        while (decls) {
            node *single = (strcmp(decls->token, "decls") == 0) ? decls->left : decls;
            if (single && strcmp(single->token, "DECL") == 0) {
                const char *typ = single->left->token;
                
                // Count identifiers in this declaration
                int nvars = 0;
                node *ids = single->right;
                while (ids) {
                    nvars++;
                    ids = ids->right;
                }
                if (nvars == 0) nvars = 1;
                
                localsBytes += nvars * sizeofType(typ);
            }
            decls = (strcmp(decls->token, "decls") == 0) ? decls->right : NULL;
        }
    }
    // Look for VAR in main function (header->right for main)
    else if (header->right && strcmp(header->right->token, "VAR") == 0) {
        node *varNode = header->right;
        node *decls = varNode->left;
        while (decls) {
            node *single = (strcmp(decls->token, "decls") == 0) ? decls->left : decls;
            if (single && strcmp(single->token, "DECL") == 0) {
                const char *typ = single->left->token;
                
                // Count identifiers in this declaration
                int nvars = 0;
                node *ids = single->right;
                while (ids) {
                    nvars++;
                    ids = ids->right;
                }
                if (nvars == 0) nvars = 1;
                
                localsBytes += nvars * sizeofType(typ);
            }
            decls = (strcmp(decls->token, "decls") == 0) ? decls->right : NULL;
        }
    }
    
    patchBeginSize(beginLine, tempsBytes + localsBytes);
    emit("EndFunc");
}

static void genGlobal(node *n)
{
    if (!n) return;
    if (!strcmp(n->token,"functions")) { 
        genGlobal(n->left); 
        genGlobal(n->right); 
    }
    else if (!strcmp(n->token,"FUNC")) {
        genFunction(n);
    }
}

void generate_3ac(node *root)
{
    if (!root) return;
    
    // Reset global state
    codeHead = codeTail = NULL;
    tempCnt = 0;
    labelCnt = 1;
    
    if (root && !strcmp(root->token,"code")) {
        genGlobal(root->left);
    }
    
    // Write to file
    FILE *out = fopen("output.ac3", "w");
    if (out) {
        dumpCode(out);
        fclose(out);
    }
}