%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"  /* Include the parser's token definitions */

extern YYSTYPE yylval;
/* Define yywrap to avoid linking with -ll */
int yywrap(void) { return 1; }
%}

%option yylineno

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
"par"[0-9]+       { return PAR; }
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
"or"              { return OR; }
"type"            { return TYPE; }
"_main_"          { return MAIN; }

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

\#\-\>([^<]|(\<[^\-])|([\<][\-][^\>]))*\<\-\#  { /* Skip comments */ }

[ \t\r\n]+        { /* Skip whitespace */ }

.                 { fprintf(stderr, "Unrecognized character: %s\n", yytext); }

%%