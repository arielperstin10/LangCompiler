%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARAMS 10

typedef enum {
    TYPE_INT, TYPE_CHAR, TYPE_REAL, TYPE_STRING, TYPE_BOOL,
    TYPE_INT_PTR, TYPE_CHAR_PTR, TYPE_REAL_PTR, TYPE_INVALID
} VarType;

#include "parser.tab.h"

extern YYSTYPE yylval;
int yywrap(void) { return 1; }
%}

%option yylineno
%option noinput nounput

DIGIT [0-9]
HEXDIGIT [0-9a-fA-F]
ID [A-Za-z][A-Za-z0-9_]*

%%
"bool"            { return BOOL; }
"char"            { return CHAR; }
"int"             { return INT; }
"real"            { return REAL_TYPE; }
"string"          { return STRING; }
"int*"            { return INT_PTR; }
"char*"           { return CHAR_PTR; }
"real*"           { return REAL_PTR; }
"if"              { return IF; }
"elif"            { return ELIF; }
"else"            { return ELSE; }
"while"           { return WHILE; }
"for"             { return FOR; }
"var"             { return VAR; }
"return"          { return RETURN; }
"null"            { return NULL_TOKEN; }  /* Changed from NULL to NULL_TOKEN to avoid conflict */
"do"              { return DO; }
"returns"         { return RETURNS; }
"begin"           { return BEGIN_TOKEN; } /* Changed from BEGIN to BEGIN_TOKEN to avoid conflict */
"end"             { return END; }
"def"             { return DEF; }
"call"            { return CALL; }
"and"             { return AND; }
"not"             { return NOT; }
"!"               { return NOT; }
"||"              { return OR; }
"or"              { return OR; }
"type"            { return TYPE; }
"_main_"          { return MAIN; }
"_Main_"|"_MAIN_"|"_mAIN_"|"_mAIn_"|"_maIN_"|"_maiN_"|"_mAiN_"|"_MaiN_"|"_MaIn_"|"_MAiN_"|"_mAiN_"|"_mAIn_"|"_maIN_"|"_maiN_"|"_mAIN_"|"_Main_" {
    fprintf(stderr, "Error: Main function must be exactly '_main_' (case sensitive)\n");
    return YYerror;
}

"=="              { return EQ; }
"!="              { return NE; }
">="              { return GE; }
"<="              { return LE; }
">"               { return GT; }
"<"               { return LT; }
"="               { return ASSIGN; }
"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return MULT; }
"/"               { return DIV; }
"&"               { return AMPERSAND; }
"%"               { return MODULO; }
"TRUE"            { return TRUE; }
"FALSE"           { return FALSE; }

"("               { return '('; }
")"               { return ')'; }
"["               { return '['; }
"]"               { return ']'; }
"{"               { return '{'; }
"}"               { return '}'; }
";"               { return ';'; }
":"               { return ':'; }
","               { return ','; }
\|                { return '|'; }

0x{HEXDIGIT}+     { yylval.intVal = (int)strtol(yytext, NULL, 16); return INTEGER; }
{DIGIT}+          { yylval.intVal = atoi(yytext); return INTEGER; }

[+-]?{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)?    { yylval.realVal = atof(yytext); return REAL; }
[+-]?"."{DIGIT}+([eE][+-]?{DIGIT}+)?            { yylval.realVal = atof(yytext); return REAL; }
[+-]?{DIGIT}+[eE][+-]?{DIGIT}+                  { yylval.realVal = atof(yytext); return REAL; }

\"[^\"\n]*\"      { 
    /* Remove quotes from string literal */
    yytext[strlen(yytext)-1] = '\0';
    yylval.stringVal = strdup(yytext+1); 
    return STRING_LITERAL; 
}

\'[^\'\\]\'       { yylval.charVal = yytext[1]; return CHAR_LITERAL; }
\'\\[nft]\'       { 
    /* Handle escape sequences */
    switch(yytext[2]) {
        case 'n': yylval.charVal = '\n'; break;
        case 'f': yylval.charVal = '\f'; break;
        case 't': yylval.charVal = '\t'; break;
        default: yylval.charVal = yytext[2];
    }
    return CHAR_LITERAL;
}

{ID}              { yylval.stringVal = strdup(yytext); return IDENTIFIER; }

"#->"[^<]*"<-#"    { /* Skip comments */ }

[ \t\r\n]+        { /* Skip whitespace */ }

[\xEF\xBB\xBF]    { /* Skip UTF-8 BOM markers */ }

.                 { fprintf(stderr, "Unrecognized character: %s\n", yytext); }

%%