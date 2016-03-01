%option noyywrap

%{

#include <iostream>
#include <vector>
#include "parser.hh"

int isatty(int fd)
{
	return 1;
}

#define YY_DECL extern "C" int yylex()
%}

%%

[a-zA-Z\._\-\+\/]+ { yylval.sval = strdup(yytext); return STRING; }
[\n]
%%
