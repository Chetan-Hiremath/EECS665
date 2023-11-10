/* definitions and declarations */
%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace {EECS}
%define api.parser.class {Parser}
%define parse.error verbose
%output "parser.cc"
%token-table 

%code requires{
	namespace EECS {
		class Manager;
		class Scanner;
	}
	#include <iostream>
	#include "string.h"
	#include "ast.hpp"

#ifndef YY_NULLPTR
#define YY_NULLPTR 0
#endif
}

%parse-param { Scanner &scanner}
%parse-param { Manager& manager}

%code{
	#include <iostream>
	#include "string.h"
	#include <fstream>
	#include <cstdlib>

	#include "calc.hpp"

	#undef yylex
	#define yylex scanner.yylex
}

%union {
	int intVal;
	const char * strVal;
}

%token END  0
%token <strVal> ID
%token <intVal> INTLIT
%token LPAR
%token RPAR
%token PLUS
%token MINUS
%token DIV
%token MULT
%token ORATE
%token CALCULATE

%type <intVal> Program
%type <intVal> Ops
%type <intVal> Op
%type <intVal> Sum
%type <intVal> Sub
%type <intVal> Prod
%type <intVal> Quot
%type <intVal> Base

%%
Program : Ops END           {$$ = $1;} 
Ops     : Ops Op            {$$ = $1;}
        | Op                {$$;}
Op      : CALCULATE ID Sum  {$$;} 
        | ORATE Sum         {$$ = $2;} 
Sum     : Sum PLUS Sub      {$$ = $1 + $3;}
        | Sub		    {$$ = $1;}
Sub     : Sub MINUS Prod    {$$ = $1 - $3;}
        | Prod		    {$$ = $1;}
Prod    : Prod MULT Quot    {$$ = $1 * $3;}
        | Quot 		    {$$ = $1;}
Quot    : Quot DIV Base	    {$$ = $1 / $3;}
        | Base		    {$$ = $1;}
Base    : INTLIT            {$$ = $1;}
        | LPAR Sum RPAR     {$$ = $2;}
        | ID                {$$;}
/* CF-productions and actions */
%%
/* Program stub -- code at end of the parser.cc*/
void 
EECS::Parser::error(const std::string &err_message){
	std::cerr << "Parser Error: " << err_message << "\n";
}
