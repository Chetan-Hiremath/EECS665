/* definitions and declarations */
%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace {EECS}
%define api.parser.class {Parser}
%output "parser.cc"
%token-table
%code requires
{
        namespace EECS 
        {
          class Manager;
          class Scanner;
          class MathNode;
        }         
#ifndef YY_NULLPTR
#define YY_NULLPTR 0
#endif
}
%parse-param {Scanner* scanner}
%parse-param {Manager* manager}
%code 
{
        #include <iostream>
        #include "string.h"
        #include <fstream>
        #include <cstdlib> 
        #include "calc.hpp"       
        #undef yylex
        #define yylex scanner->yylex
}
%union 
{
        MathNode* transNode;
        bool transGood = true;
        int intVal;
}
%token END 0
%token LPAR
%token RPAR
%token PLUS
%token MINUS
%token DIV
%token MULT
%token <intVal> INTLIT
%left PLUS MINUS
%left MULT DIV
%precedence NEG
%type <transNode> Expr
%type <transGood> Equation
%%
Equation: Expr END 
{ 
  $$ = true;
  MathNode* child = $1;
  cout << "Expression value: " << child->print() << "\n";
}
Expr: Expr PLUS Expr    {   
                            MathNode* arm1 = $1;
                            MathNode* arm2 = $3;
                            $$ = new AddNode("arm1", arm1, "arm2", arm2);
                        }	
    | Expr MINUS Expr   {   
                            MathNode* arm1 = $1;
                            MathNode* arm2 = $3;
                            $$ = new SubNode("arm1", arm1, "arm2", arm2);
                        }
    | Expr DIV Expr     {   
                            MathNode* arm1 = $1;
                            MathNode* arm2 = $3;
                            $$ = new DivNode("arm1", arm1, "arm2", arm2);
                        }
    | Expr MULT Expr    {
                            MathNode* arm1 = $1;
                            MathNode* arm2 = $3;
                            $$ = new MultNode("arm1", arm1, "arm2", arm2);
                        }
    | NEG Expr          {$$ = new NegNode("arm2", $2);}
    | INTLIT            {$$ = new EECS::IntNode($1);}
    | LPAR Expr RPAR     {$$ = $2;}
/* CF-productions and actions */
%%
/* Program stub -- code at end of the parser.cc */
void EECS::Parser::error(const std::string &err_message)
{
  std::cerr << "Parser Error: " << err_message << "\n";
}
