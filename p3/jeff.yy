%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace{jeff}
%define api.parser.class {Parser}
%define parse.error verbose
%output "parser.cc"
%token-table

%code requires{
	#include <list>
	#include "tokens.hpp"
	#include "ast.hpp"
	namespace jeff {
		class Scanner;
	}

//The following definition is required when 
// we don't have the %locations directive
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

//End "requires" code
}

%parse-param { jeff::Scanner &scanner }
%parse-param { jeff::ProgramNode** root }
%code{
   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex
}

/*
The %union directive is a way to specify the 
set of possible types that might be used as
translation attributes on a symbol.
For this project, only terminals have types (we'll
have translation attributes for non-terminals in the next
project)
*/
%union {
   jeff::Token*                                 lexeme;
   jeff::Token*                     		transToken;
   jeff::IDToken*                   		transIDToken;
   jeff::ProgramNode*               		transProgram;
   std::list<jeff::DeclNode *>*     		transDeclList;
   jeff::DeclNode*                  		transDecl;
   jeff::VarDeclNode*               		transVarDecl;
   jeff::TypeNode*                  		transType;
   jeff::IDNode*                    		transID;
   jeff::FnDeclNode * 				transFnDecl;
   std::list<jeff::FormalDeclNode *>* 	        transFormalsList;
   std::list<jeff::FormalDeclNode *>*   	transFormals;
   jeff::FormalDeclNode* 			transFormalDecl;
   std::list<jeff::StmtNode *>*                 transFnBody;
   std::list<jeff::StmtNode *>*                 transStmtList;
   jeff::StmtNode* 				transStmt;
   jeff::ExpNode* 				transExp;
   jeff::AssignExpNode* 			transAssignExp;
   jeff::CallExpNode* 				transCallExp;
   jeff::ExpNode*                               transTerm;
   jeff::LocNode* 				transLoc;
   jeff::IntLitToken*				transIntToken;
   jeff::StrToken*				transStrToken;
   std::list<jeff::ExpNode*>*			transExpList;	 
}

%define parse.assert


/* Terminals 
 *  No need to touch these, but do note the translation type
 *  of each node. Most are just "transToken", which is defined in
 *  the %union above to mean that the token translation is an instance
 *  of drewgon::Token *, and thus has no fields (other than line and column).
 *  Some terminals, like ID, are "transIDToken", meaning the translation
 *  also has a name field. 
*/
%token                   END	   0 "end file"
%token	<transToken>     AND
%token	<transToken>     ASSIGN
%token	<transToken>     BOOL
%token	<transToken>     CLOSE
%token	<transToken>     COLON
%token	<transToken>     COMMA
%token	<transToken>     CONSOLE
%token	<transToken>     DASH
%token	<transToken>     ELSE
%token	<transToken>     EQUALS
%token	<transToken>     FALSE
%token	<transToken>     FILE
%token	<transToken>     FN
%token	<transToken>     GREATER
%token	<transToken>     GREATEREQ
%token	<transIDToken>   ID
%token	<transToken>     IF
%token	<transToken>     INT
%token	<transIntToken>  INTLITERAL
%token	<transToken>     LCURLY
%token	<transToken>     LESS
%token	<transToken>     LESSEQ
%token	<transToken>     LPAREN
%token	<transToken>     LBRACE
%token	<transToken>     NOT
%token	<transToken>     NOTEQUALS
%token	<transToken>     OR
%token	<transToken>     OPEN
%token	<transToken>     CROSS
%token	<transToken>     POSTDEC
%token	<transToken>     POSTINC
%token	<transToken>     QUESTION
%token	<transToken>     READ
%token	<transToken>     RETURN
%token	<transToken>     RBRACE
%token	<transToken>     RCURLY
%token	<transToken>     RPAREN
%token	<transToken>     SEMICOL
%token	<transToken>     SLASH
%token	<transToken>     STAR
%token	<transStrToken>  STRINGLITERAL
%token	<transToken>     TRUE
%token	<transToken>     VOID
%token	<transToken>     WHILE
%token	<transToken>     WRITE


/* Nonterminals
*  TODO: You will need to add more nonterminals
*  to this list as you add productions to the grammar
*  below (along with indicating the appropriate translation
*  attribute type). Note that the specifier in brackets
*  indicates the type of the translation attribute using
*  the names defined in the %union directive above
*/
/*    (attribute type)    (nonterminal)    */
%type <transProgram>        program
%type <transDeclList>       globals
%type <transDecl>           decl
%type <transVarDecl>        varDecl
%type <transType>           type
%type <transType>           primType
%type <transType>           arrayType
%type <transID>             id
%type <transFnDecl>		    fnDecl
%type <transFormals> 		formals
%type <transFormalsList> 	formalsList
%type <transFormalDecl>		formalDecl
%type <transFnBody> 		fnBody
%type <transStmtList> 		stmtList
%type <transStmt> 		    stmt
%type <transStmt> 		    blockStmt
%type <transExp> 		    exp
%type <transAssignExp> 		assignExp
%type <transCallExp> 		callExp
%type <transExpList>		actualsList
%type <transTerm>		    term
%type <transLoc> 		    loc



%right ASSIGN
%left OR
%left AND
%nonassoc LESS GREATER LESSEQ GREATEREQ EQUALS NOTEQUALS
%left DASH CROSS
%left STAR SLASH
%left NOT 

%%

program 	: globals
		{
			$$ = new ProgramNode($1);
			*root = $$;
		}

globals 	: globals decl 
		{
			$$ = $1;
			DeclNode * declNode = $2;
			$1->push_back(declNode);
		}
		| /* epsilon */
		{
			$$ = new std::list<DeclNode *>();
		} 

decl 		: varDecl SEMICOL { $$ = $1; }
		| fnDecl  { $$ = $1; }

varDecl 	: type id
		{ 
			size_t typeLine = $1->line();
			size_t typeCol = $1->col();
			$$ = new VarDeclNode(typeLine, typeCol, $1, $2);
		}
type		: primType
		{
		  $$ = $1;
		}
                | arrayType
                {
                  $$ = $1;
                }

primType 	: INT
	        {
			$$ = new IntTypeNode($1->line(), $1->col());
	        }
                | BOOL
	        { 
			$$ = new BoolTypeNode($1->line(), $1->col());
	        }
	        | VOID
	        {
			$$ = new VoidTypeNode($1->line(), $1->col()); 
	        }
	        | FILE
	        {
			$$ = new FileTypeNode($1->line(), $1->col()); 	
	        }

arrayType       :primType LBRACE INTLITERAL RBRACE
                {
                        $$ = new ArrayTypeNode($1->line(), $1->col());
                }

fnDecl 		: type id formals fnBody
		{ $$ = new FnDeclNode($1, $2, $3, $4); }

formals 	: LPAREN RPAREN
		{ $$ = new std::list<FormalDeclNode*>; }
	        | LPAREN formalsList RPAREN
		{ $$ = $2; }

formalsList     : formalDecl
		{ 
			$$ = new std::list<FormalDeclNode*>;
			$$->push_back($1);
		}
		| formalDecl COMMA formalsList 
		{ 
			$$ = $3;
			$$->push_front($1);
		}

formalDecl	: type id
		{ $$ = new FormalDeclNode($1, $2); }

fnBody		: LCURLY stmtList RCURLY
		{ $$ = $2; }

stmtList 	: /* epsilon */
		{ 
			std::list<StmtNode *> * startingStmt;
			startingStmt = new std::list<StmtNode *>;
			$$ = startingStmt;
		}
		| stmtList stmt 
		{ 
			$$ = $1;
			$1->push_back($2);
		}	
                | stmtList blockStmt
	  	{
			$$ = $1;
			$1->push_back($2);
	        }
																										
stmt		: varDecl SEMICOL
		{ $$ = $1; }
		| assignExp SEMICOL
		{ $$ = new AssignStmtNode($1); }
		| loc POSTDEC SEMICOL
		{ $$ = new PostDecStmtNode($1); }
		| loc POSTINC SEMICOL
		{ $$ = new PostIncStmtNode($1); }
		| RETURN exp SEMICOL
		{ $$ = new ReturnStmtNode($2, false); }
		| RETURN SEMICOL
		{ $$ = new ReturnStmtNode($2->line(), $2->col(), true); }
		| callExp SEMICOL
		{ $$ = new CallStmtNode($1); }

blockStmt       : IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		{ $$ = new IfStmtNode($3, $6); }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		{ $$ = new IfElseStmtNode($3, $6, $10); }
		| WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		{ $$ = new WhileStmtNode($3, $6); }

exp		: assignExp 
		{ $$ = $1; } 
		| exp DASH exp
		{ $$ = new MinusNode($1, $3); }
		| exp CROSS exp
		{ $$ = new PlusNode($1, $3); }
		| exp STAR exp
		{ $$ = new TimesNode($1, $3); }
		| exp SLASH exp
		{ $$ = new DivideNode($1, $3); }
		| exp AND exp
		{ $$ = new AndNode($1, $3); }
		| exp OR exp
		{ $$ = new OrNode($1, $3); }
		| exp EQUALS exp
		{ $$ = new EqualsNode($1, $3); }
		| exp NOTEQUALS exp
		{ $$ = new NotEqualsNode($1, $3); }
		| exp GREATER exp
		{ $$ = new GreaterNode($1, $3); }
		| exp GREATEREQ exp
		{ $$ = new GreaterEqNode($1, $3); }
		| exp LESS exp
		{ $$ = new LessNode($1, $3); }
		| exp LESSEQ exp
		{ $$ = new LessEqNode($1, $3); }
		| NOT exp
		{ $$ = new NotNode($2); }
		| DASH term
		{ $$ = new NegNode($2); }
		| term 
		{ $$ = $1; }

assignExp	: loc ASSIGN exp
		{
			$$ = new AssignExpNode($1, $3);
		}

callExp		: id LPAREN RPAREN
		{ 
			$$ = new CallExpNode($1, new std::list<ExpNode*>);
		}
		| id LPAREN actualsList RPAREN
		{ 
			$$ = new CallExpNode($1, $3);
		}											

actualsList	: exp
		{
			$$ = new std::list<ExpNode*>;
			$$->push_back($1);
		}
		| actualsList COMMA exp
		{ 
			$$ = $1;
			$$->push_back($3);
		}	

term 	        : loc
		{ $$ = $1; }
		| callExp
		{ $$ = $1; }
		| INTLITERAL 
		{ $$ = new IntLitNode($1->line(), $1->col(), $1); }
		| STRINGLITERAL 
		{ $$ = new StrLitNode($1->line(), $1->col(), $1); }
		| TRUE
		{ $$ = new TrueNode($1); }
		| FALSE
		{ $$ = new FalseNode($1); }
		| LPAREN exp RPAREN
		{ $$ = $2; }

loc	        : id
		{ $$ = new LocNode($1); }
		| id LBRACE exp RBRACE
		{ $$ = new IndexNode($1, $3); }

id		: ID
		{ $$ = new IDNode($1); }
		| CONSOLE
		{ }
	
%%

void jeff::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
