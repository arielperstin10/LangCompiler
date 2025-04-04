DIGIT [0-9]
HEXDIGIT [0-9a-fA-F]
ID [A-Za-z][A-Za-z0-9_]*

%%
// Keywords
bool return BOOL;
char return CHAR;
int return INT;
real return REAL_TYPE;
string return STRING;
int* return INT_PTR;
char* return CHAR_PTR;
real* return REAL_PTR;
if return IF;
elif return ELIF;
else return ELSE;
while return WHILE;
for return FOR;
var return VAR;
par[0-9]+ return PAR;
return return RETURN;
null return NULL;
do return DO;
returns return RETURNS;
begin return BEGIN;
end return END;
def return DEF;
call return CALL;
and return AND;
not return NOT;
or return OR;

// Operators
== return EQ;
!= return NE;
\>= return GE;
\<= return LE;
\> return GT;
\< return LT;
= return ASSIGN;
\+ return PLUS;
- return MINUS;
\* return MULT;
/ return DIV;
& return AMPERSAND;

// Numeric Literals
0x{HEXDIGIT}+ {yylval.intVal = (int)strtol(yytext, NULL, 16); return INTEGER;};
{DIGIT}+ {yylval.intVal = atoi(yytext); return INTEGER;};
[+-]?{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)? {yylval.realVal = atof(yytext); return REAL;};
[+-]?\\.{DIGIT}+([eE][+-]?{DIGIT}+)? {yylval.realVal = atof(yytext); return REAL;};

// String Literal
\"[^\n\"]*\" {yylval.stringVal = strdup(yytext); return STRING_LITERAL;};

// Char Literal
\'([^\'\n])\' {yylval.charVal = yytext[1]; return CHAR_LITERAL;};

// Identifier
{ID} {yylval.stringVal = strdup(yytext); return IDENTIFIER;};

// Comments
\#\->([^<]|(\<[^-])|(\<\-))*\<-\# {/* ignore comment */};

// Whitespace
[ \t\r\n]+ {/* ignore whitespace */};
%%
