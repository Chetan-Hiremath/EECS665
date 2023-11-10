/* Directives */
%{
using namespace std;

#include "mylexer.hpp"

#undef YY_DECL
#define YY_DECL int MyLexer::produceToken(Token ** tok)

%}

NPAT 0|([1-9][0-9]*)
%%
[mM]an|[wW]oman|[dD]og { *tok = new NounToken(yytext); return NOUN;}
bites|kicks|loves { *tok = new VerbToken(yytext); return VERB;}
l(o+)ng|tall|short { *tok = new AdjectiveToken(yytext); return ADJECTIVE;}
[ \n\t] {}
.    { std::cerr << "BAD CHARACTER" << yytext << endl; exit(1); }
%%
/* added to the end of the generated file */
