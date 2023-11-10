// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "frontend.hh"


// Unqualified %code blocks.
#line 34 "jeff.yy"

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

#line 63 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "jeff.yy"
namespace jeff {
#line 137 "parser.cc"

  /// Build a parser object.
  Parser::Parser (jeff::Scanner &scanner_yyarg, jeff::ProgramNode** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: globals
#line 190 "jeff.yy"
                {
			(yylhs.value.transProgram) = new ProgramNode((yystack_[0].value.transDeclList));
			*root = (yylhs.value.transProgram);
		}
#line 598 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 196 "jeff.yy"
                {
			(yylhs.value.transDeclList) = (yystack_[1].value.transDeclList);
			DeclNode * declNode = (yystack_[0].value.transDecl);
			(yystack_[1].value.transDeclList)->push_back(declNode);
		}
#line 608 "parser.cc"
    break;

  case 4: // globals: %empty
#line 202 "jeff.yy"
                {
			(yylhs.value.transDeclList) = new std::list<DeclNode *>();
		}
#line 616 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOL
#line 206 "jeff.yy"
                                  { (yylhs.value.transDecl) = (yystack_[1].value.transVarDecl); }
#line 622 "parser.cc"
    break;

  case 6: // decl: fnDecl
#line 207 "jeff.yy"
                          { (yylhs.value.transDecl) = (yystack_[0].value.transFnDecl); }
#line 628 "parser.cc"
    break;

  case 7: // varDecl: type id
#line 210 "jeff.yy"
                { 
			size_t typeLine = (yystack_[1].value.transType)->line();
			size_t typeCol = (yystack_[1].value.transType)->col();
			(yylhs.value.transVarDecl) = new VarDeclNode(typeLine, typeCol, (yystack_[1].value.transType), (yystack_[0].value.transID));
		}
#line 638 "parser.cc"
    break;

  case 8: // type: primType
#line 216 "jeff.yy"
                {
		  (yylhs.value.transType) = (yystack_[0].value.transType);
		}
#line 646 "parser.cc"
    break;

  case 9: // type: arrayType
#line 220 "jeff.yy"
                {
                  (yylhs.value.transType) = (yystack_[0].value.transType);
                }
#line 654 "parser.cc"
    break;

  case 10: // primType: INT
#line 225 "jeff.yy"
                {
			(yylhs.value.transType) = new IntTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col());
	        }
#line 662 "parser.cc"
    break;

  case 11: // primType: BOOL
#line 229 "jeff.yy"
                { 
			(yylhs.value.transType) = new BoolTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col());
	        }
#line 670 "parser.cc"
    break;

  case 12: // primType: VOID
#line 233 "jeff.yy"
                {
			(yylhs.value.transType) = new VoidTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col()); 
	        }
#line 678 "parser.cc"
    break;

  case 13: // primType: FILE
#line 237 "jeff.yy"
                {
			(yylhs.value.transType) = new FileTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col()); 	
	        }
#line 686 "parser.cc"
    break;

  case 14: // arrayType: primType LBRACE INTLITERAL RBRACE
#line 242 "jeff.yy"
                {
                        (yylhs.value.transType) = new ArrayTypeNode((yystack_[3].value.transType)->line(), (yystack_[3].value.transType)->col());
                }
#line 694 "parser.cc"
    break;

  case 15: // fnDecl: type id formals fnBody
#line 247 "jeff.yy"
                { (yylhs.value.transFnDecl) = new FnDeclNode((yystack_[3].value.transType), (yystack_[2].value.transID), (yystack_[1].value.transFormals), (yystack_[0].value.transFnBody)); }
#line 700 "parser.cc"
    break;

  case 16: // formals: LPAREN RPAREN
#line 250 "jeff.yy"
                { (yylhs.value.transFormals) = new std::list<FormalDeclNode*>; }
#line 706 "parser.cc"
    break;

  case 17: // formals: LPAREN formalsList RPAREN
#line 252 "jeff.yy"
                { (yylhs.value.transFormals) = (yystack_[1].value.transFormalsList); }
#line 712 "parser.cc"
    break;

  case 18: // formalsList: formalDecl
#line 255 "jeff.yy"
                { 
			(yylhs.value.transFormalsList) = new std::list<FormalDeclNode*>;
			(yylhs.value.transFormalsList)->push_back((yystack_[0].value.transFormalDecl));
		}
#line 721 "parser.cc"
    break;

  case 19: // formalsList: formalDecl COMMA formalsList
#line 260 "jeff.yy"
                { 
			(yylhs.value.transFormalsList) = (yystack_[0].value.transFormalsList);
			(yylhs.value.transFormalsList)->push_front((yystack_[2].value.transFormalDecl));
		}
#line 730 "parser.cc"
    break;

  case 20: // formalDecl: type id
#line 266 "jeff.yy"
                { (yylhs.value.transFormalDecl) = new FormalDeclNode((yystack_[1].value.transType), (yystack_[0].value.transID)); }
#line 736 "parser.cc"
    break;

  case 21: // fnBody: LCURLY stmtList RCURLY
#line 269 "jeff.yy"
                { (yylhs.value.transFnBody) = (yystack_[1].value.transStmtList); }
#line 742 "parser.cc"
    break;

  case 22: // stmtList: %empty
#line 272 "jeff.yy"
                { 
			std::list<StmtNode *> * startingStmt;
			startingStmt = new std::list<StmtNode *>;
			(yylhs.value.transStmtList) = startingStmt;
		}
#line 752 "parser.cc"
    break;

  case 23: // stmtList: stmtList stmt
#line 278 "jeff.yy"
                { 
			(yylhs.value.transStmtList) = (yystack_[1].value.transStmtList);
			(yystack_[1].value.transStmtList)->push_back((yystack_[0].value.transStmt));
		}
#line 761 "parser.cc"
    break;

  case 24: // stmtList: stmtList blockStmt
#line 283 "jeff.yy"
                {
			(yylhs.value.transStmtList) = (yystack_[1].value.transStmtList);
			(yystack_[1].value.transStmtList)->push_back((yystack_[0].value.transStmt));
	        }
#line 770 "parser.cc"
    break;

  case 25: // stmt: varDecl SEMICOL
#line 289 "jeff.yy"
                { (yylhs.value.transStmt) = (yystack_[1].value.transVarDecl); }
#line 776 "parser.cc"
    break;

  case 26: // stmt: assignExp SEMICOL
#line 291 "jeff.yy"
                { (yylhs.value.transStmt) = new AssignStmtNode((yystack_[1].value.transAssignExp)); }
#line 782 "parser.cc"
    break;

  case 27: // stmt: loc POSTDEC SEMICOL
#line 293 "jeff.yy"
                { (yylhs.value.transStmt) = new PostDecStmtNode((yystack_[2].value.transLoc)); }
#line 788 "parser.cc"
    break;

  case 28: // stmt: loc POSTINC SEMICOL
#line 295 "jeff.yy"
                { (yylhs.value.transStmt) = new PostIncStmtNode((yystack_[2].value.transLoc)); }
#line 794 "parser.cc"
    break;

  case 29: // stmt: RETURN exp SEMICOL
#line 297 "jeff.yy"
                { (yylhs.value.transStmt) = new ReturnStmtNode((yystack_[1].value.transExp), false); }
#line 800 "parser.cc"
    break;

  case 30: // stmt: RETURN SEMICOL
#line 299 "jeff.yy"
                { (yylhs.value.transStmt) = new ReturnStmtNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), true); }
#line 806 "parser.cc"
    break;

  case 31: // stmt: callExp SEMICOL
#line 301 "jeff.yy"
                { (yylhs.value.transStmt) = new CallStmtNode((yystack_[1].value.transCallExp)); }
#line 812 "parser.cc"
    break;

  case 32: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 304 "jeff.yy"
                { (yylhs.value.transStmt) = new IfStmtNode((yystack_[4].value.transExp), (yystack_[1].value.transStmtList)); }
#line 818 "parser.cc"
    break;

  case 33: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 306 "jeff.yy"
                { (yylhs.value.transStmt) = new IfElseStmtNode((yystack_[8].value.transExp), (yystack_[5].value.transStmtList), (yystack_[1].value.transStmtList)); }
#line 824 "parser.cc"
    break;

  case 34: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 308 "jeff.yy"
                { (yylhs.value.transStmt) = new WhileStmtNode((yystack_[4].value.transExp), (yystack_[1].value.transStmtList)); }
#line 830 "parser.cc"
    break;

  case 35: // exp: assignExp
#line 311 "jeff.yy"
                { (yylhs.value.transExp) = (yystack_[0].value.transAssignExp); }
#line 836 "parser.cc"
    break;

  case 36: // exp: exp DASH exp
#line 313 "jeff.yy"
                { (yylhs.value.transExp) = new MinusNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 842 "parser.cc"
    break;

  case 37: // exp: exp CROSS exp
#line 315 "jeff.yy"
                { (yylhs.value.transExp) = new PlusNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 848 "parser.cc"
    break;

  case 38: // exp: exp STAR exp
#line 317 "jeff.yy"
                { (yylhs.value.transExp) = new TimesNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 854 "parser.cc"
    break;

  case 39: // exp: exp SLASH exp
#line 319 "jeff.yy"
                { (yylhs.value.transExp) = new DivideNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 860 "parser.cc"
    break;

  case 40: // exp: exp AND exp
#line 321 "jeff.yy"
                { (yylhs.value.transExp) = new AndNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 866 "parser.cc"
    break;

  case 41: // exp: exp OR exp
#line 323 "jeff.yy"
                { (yylhs.value.transExp) = new OrNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 872 "parser.cc"
    break;

  case 42: // exp: exp EQUALS exp
#line 325 "jeff.yy"
                { (yylhs.value.transExp) = new EqualsNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 878 "parser.cc"
    break;

  case 43: // exp: exp NOTEQUALS exp
#line 327 "jeff.yy"
                { (yylhs.value.transExp) = new NotEqualsNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 884 "parser.cc"
    break;

  case 44: // exp: exp GREATER exp
#line 329 "jeff.yy"
                { (yylhs.value.transExp) = new GreaterNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 890 "parser.cc"
    break;

  case 45: // exp: exp GREATEREQ exp
#line 331 "jeff.yy"
                { (yylhs.value.transExp) = new GreaterEqNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 896 "parser.cc"
    break;

  case 46: // exp: exp LESS exp
#line 333 "jeff.yy"
                { (yylhs.value.transExp) = new LessNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 902 "parser.cc"
    break;

  case 47: // exp: exp LESSEQ exp
#line 335 "jeff.yy"
                { (yylhs.value.transExp) = new LessEqNode((yystack_[2].value.transExp), (yystack_[0].value.transExp)); }
#line 908 "parser.cc"
    break;

  case 48: // exp: NOT exp
#line 337 "jeff.yy"
                { (yylhs.value.transExp) = new NotNode((yystack_[0].value.transExp)); }
#line 914 "parser.cc"
    break;

  case 49: // exp: DASH term
#line 339 "jeff.yy"
                { (yylhs.value.transExp) = new NegNode((yystack_[0].value.transTerm)); }
#line 920 "parser.cc"
    break;

  case 50: // exp: term
#line 341 "jeff.yy"
                { (yylhs.value.transExp) = (yystack_[0].value.transTerm); }
#line 926 "parser.cc"
    break;

  case 51: // assignExp: loc ASSIGN exp
#line 344 "jeff.yy"
                {
			(yylhs.value.transAssignExp) = new AssignExpNode((yystack_[2].value.transLoc), (yystack_[0].value.transExp));
		}
#line 934 "parser.cc"
    break;

  case 52: // callExp: id LPAREN RPAREN
#line 349 "jeff.yy"
                { 
			(yylhs.value.transCallExp) = new CallExpNode((yystack_[2].value.transID), new std::list<ExpNode*>);
		}
#line 942 "parser.cc"
    break;

  case 53: // callExp: id LPAREN actualsList RPAREN
#line 353 "jeff.yy"
                { 
			(yylhs.value.transCallExp) = new CallExpNode((yystack_[3].value.transID), (yystack_[1].value.transExpList));
		}
#line 950 "parser.cc"
    break;

  case 54: // actualsList: exp
#line 358 "jeff.yy"
                {
			(yylhs.value.transExpList) = new std::list<ExpNode*>;
			(yylhs.value.transExpList)->push_back((yystack_[0].value.transExp));
		}
#line 959 "parser.cc"
    break;

  case 55: // actualsList: actualsList COMMA exp
#line 363 "jeff.yy"
                { 
			(yylhs.value.transExpList) = (yystack_[2].value.transExpList);
			(yylhs.value.transExpList)->push_back((yystack_[0].value.transExp));
		}
#line 968 "parser.cc"
    break;

  case 56: // term: loc
#line 369 "jeff.yy"
                { (yylhs.value.transTerm) = (yystack_[0].value.transLoc); }
#line 974 "parser.cc"
    break;

  case 57: // term: callExp
#line 371 "jeff.yy"
                { (yylhs.value.transTerm) = (yystack_[0].value.transCallExp); }
#line 980 "parser.cc"
    break;

  case 58: // term: INTLITERAL
#line 373 "jeff.yy"
                { (yylhs.value.transTerm) = new IntLitNode((yystack_[0].value.transIntToken)->line(), (yystack_[0].value.transIntToken)->col(), (yystack_[0].value.transIntToken)); }
#line 986 "parser.cc"
    break;

  case 59: // term: STRINGLITERAL
#line 375 "jeff.yy"
                { (yylhs.value.transTerm) = new StrLitNode((yystack_[0].value.transStrToken)->line(), (yystack_[0].value.transStrToken)->col(), (yystack_[0].value.transStrToken)); }
#line 992 "parser.cc"
    break;

  case 60: // term: TRUE
#line 377 "jeff.yy"
                { (yylhs.value.transTerm) = new TrueNode((yystack_[0].value.transToken)); }
#line 998 "parser.cc"
    break;

  case 61: // term: FALSE
#line 379 "jeff.yy"
                { (yylhs.value.transTerm) = new FalseNode((yystack_[0].value.transToken)); }
#line 1004 "parser.cc"
    break;

  case 62: // term: LPAREN exp RPAREN
#line 381 "jeff.yy"
                { (yylhs.value.transTerm) = (yystack_[1].value.transExp); }
#line 1010 "parser.cc"
    break;

  case 63: // loc: id
#line 384 "jeff.yy"
                { (yylhs.value.transLoc) = new LocNode((yystack_[0].value.transID)); }
#line 1016 "parser.cc"
    break;

  case 64: // loc: id LBRACE exp RBRACE
#line 386 "jeff.yy"
                { (yylhs.value.transLoc) = new IndexNode((yystack_[3].value.transID), (yystack_[1].value.transExp)); }
#line 1022 "parser.cc"
    break;

  case 65: // id: ID
#line 389 "jeff.yy"
                { (yylhs.value.transID) = new IDNode((yystack_[0].value.transIDToken)); }
#line 1028 "parser.cc"
    break;

  case 66: // id: CONSOLE
#line 391 "jeff.yy"
                { }
#line 1034 "parser.cc"
    break;


#line 1038 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -110;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
    -110,    21,    37,  -110,  -110,  -110,  -110,  -110,  -110,   -31,
      -8,   -10,  -110,  -110,  -110,  -110,  -110,    -1,    25,    59,
      31,    19,  -110,    -8,    20,    52,  -110,  -110,  -110,  -110,
    -110,    37,     9,  -110,    33,   308,  -110,    38,    22,    -8,
    -110,  -110,    26,    27,    16,   -14,   345,   195,  -110,  -110,
     345,   345,  -110,  -110,  -110,   131,  -110,  -110,  -110,    67,
     345,  -110,  -110,  -110,  -110,   345,    32,    40,   332,   345,
     153,  -110,  -110,   186,  -110,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,  -110,   345,   345,   219,   274,
    -110,  -110,  -110,   274,    11,   252,    55,  -110,   367,   -11,
     387,   387,   387,   387,   387,   387,   296,   -11,  -110,  -110,
      61,   345,  -110,  -110,  -110,  -110,   274,    56,    91,    73,
    -110,    75,  -110,    94,  -110
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    11,    13,    10,    12,     3,     0,
       0,     8,     9,     6,     5,    66,    65,     7,     0,     0,
       0,     0,    16,     0,     0,    18,    22,    15,    14,    20,
      17,     0,     0,    19,     0,     0,    21,     0,     0,     0,
      23,    24,     0,     0,     0,    63,     0,     0,    61,    58,
       0,     0,    30,    59,    60,     0,    35,    57,    50,    56,
       0,    25,     7,    26,    31,     0,     0,     0,     0,     0,
       0,    49,    56,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,    51,
      27,    28,    52,    54,     0,     0,     0,    62,    40,    36,
      42,    44,    45,    46,    47,    43,    41,    37,    39,    38,
       0,     0,    53,    64,    22,    22,    55,     0,     0,    32,
      34,     0,    22,     0,    33
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -110,  -110,  -110,  -110,    76,    50,  -110,  -110,  -110,  -110,
      84,  -110,  -110,  -109,  -110,  -110,   -43,   -30,   -28,  -110,
      60,   -32,    96
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    38,    39,    11,    12,    13,    20,
      24,    25,    27,    32,    40,    41,    55,    56,    57,    94,
      58,    59,    45
  };

  const signed char
  Parser::yytable_[] =
  {
      44,    15,    42,    70,    43,   117,   118,    73,    74,    14,
      16,    68,    69,   123,     4,    72,    18,    88,    15,   111,
      65,     3,    89,     5,    19,    93,    95,    16,    34,     6,
      86,    87,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     4,   108,   109,    35,    21,    36,    66,    67,
     112,     5,    10,    26,     7,    37,    28,     6,    46,    30,
      31,     4,    61,    60,     4,    15,    63,    64,   116,    23,
       5,    65,    90,     5,    16,    34,     6,   114,     9,     6,
      91,    23,     7,   115,   121,    44,    44,    42,    42,    43,
      43,    44,    35,    42,   119,    43,     4,   122,    22,     4,
      15,     7,    37,    15,     7,     5,    17,    71,     5,    16,
      34,     6,    16,    34,     6,    33,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,    35,     0,   120,
      35,     0,   124,     0,    75,    62,     7,    37,     0,     7,
      37,    76,     0,    77,     0,     0,     0,    78,    79,     0,
       0,     0,     0,     0,    80,    81,    75,     0,     0,    82,
      83,     0,    84,    76,     0,    77,     0,     0,     0,    78,
      79,    85,    86,    87,     0,     0,    80,    81,     0,     0,
       0,    82,    83,     0,    84,     0,     0,     0,     0,    75,
       0,     0,    96,     0,    86,    87,    76,     0,    77,     0,
       0,     0,    78,    79,    15,     0,     0,     0,    48,    80,
      81,     0,     0,    16,    82,    83,    49,    84,     0,     0,
      50,     0,    75,     0,     0,    97,     0,    86,    87,    76,
       0,    77,     0,     0,     0,    78,    79,     0,    53,    54,
       0,     0,    80,    81,     0,     0,     0,    82,    83,     0,
      84,     0,     0,     0,     0,    75,     0,     0,   110,     0,
      86,    87,    76,     0,    77,     0,     0,     0,    78,    79,
       0,     0,     0,     0,     0,    80,    81,    75,     0,     0,
      82,    83,     0,    84,    76,     0,    77,     0,     0,   113,
      78,    79,     0,    86,    87,     0,     0,    80,    81,    75,
       0,     0,    82,    83,     0,    84,    76,     0,    77,     0,
       0,     0,    78,    79,     0,    86,    87,    15,    47,    80,
      81,    48,     0,     0,    82,     0,    16,    84,     0,    49,
       0,     0,     0,    50,     0,    51,     0,    86,    87,     0,
       0,    15,    47,     0,     0,    48,     0,     0,    52,     0,
      16,    53,    54,    49,    15,    47,     0,    50,    48,    51,
       0,     0,     0,    16,     0,     0,    49,     0,     0,     0,
      50,    92,    51,     0,     0,    53,    54,    76,     0,    77,
       0,     0,     0,    78,    79,     0,     0,     0,    53,    54,
      80,    81,     0,     0,     0,    82,     0,    76,    84,    -1,
       0,     0,     0,    -1,    -1,     0,     0,     0,    86,    87,
      -1,    -1,     0,     0,     0,    -1,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,    87
  };

  const signed char
  Parser::yycheck_[] =
  {
      32,     9,    32,    46,    32,   114,   115,    50,    51,    40,
      18,    25,    26,   122,     5,    47,    26,    60,     9,     8,
       4,     0,    65,    14,    25,    68,    69,    18,    19,    20,
      41,    42,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,     5,    86,    87,    36,    21,    38,    32,    33,
      39,    14,     2,    22,    45,    46,    37,    20,    25,    39,
       8,     5,    40,    25,     5,     9,    40,    40,   111,    19,
      14,     4,    40,    14,    18,    19,    20,    22,     2,    20,
      40,    31,    45,    22,    11,   117,   118,   117,   118,   117,
     118,   123,    36,   123,    38,   123,     5,    22,    39,     5,
       9,    45,    46,     9,    45,    14,    10,    47,    14,    18,
      19,    20,    18,    19,    20,    31,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    38,
      36,    -1,    38,    -1,     3,    39,    45,    46,    -1,    45,
      46,    10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    23,    24,     3,    -1,    -1,    28,
      29,    -1,    31,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    40,    41,    42,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    39,    -1,    41,    42,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,     9,    -1,    -1,    -1,    13,    23,
      24,    -1,    -1,    18,    28,    29,    21,    31,    -1,    -1,
      25,    -1,     3,    -1,    -1,    39,    -1,    41,    42,    10,
      -1,    12,    -1,    -1,    -1,    16,    17,    -1,    43,    44,
      -1,    -1,    23,    24,    -1,    -1,    -1,    28,    29,    -1,
      31,    -1,    -1,    -1,    -1,     3,    -1,    -1,    39,    -1,
      41,    42,    10,    -1,    12,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    23,    24,     3,    -1,    -1,
      28,    29,    -1,    31,    10,    -1,    12,    -1,    -1,    37,
      16,    17,    -1,    41,    42,    -1,    -1,    23,    24,     3,
      -1,    -1,    28,    29,    -1,    31,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    41,    42,     9,    10,    23,
      24,    13,    -1,    -1,    28,    -1,    18,    31,    -1,    21,
      -1,    -1,    -1,    25,    -1,    27,    -1,    41,    42,    -1,
      -1,     9,    10,    -1,    -1,    13,    -1,    -1,    40,    -1,
      18,    43,    44,    21,     9,    10,    -1,    25,    13,    27,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
      25,    39,    27,    -1,    -1,    43,    44,    10,    -1,    12,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    43,    44,
      23,    24,    -1,    -1,    -1,    28,    -1,    10,    31,    12,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    41,    42,
      23,    24,    -1,    -1,    -1,    28,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    49,    50,     0,     5,    14,    20,    45,    51,    52,
      53,    54,    55,    56,    40,     9,    18,    70,    26,    25,
      57,    21,    39,    53,    58,    59,    22,    60,    37,    70,
      39,     8,    61,    58,    19,    36,    38,    46,    52,    53,
      62,    63,    65,    66,    69,    70,    25,    10,    13,    21,
      25,    27,    40,    43,    44,    64,    65,    66,    68,    69,
      25,    40,    70,    40,    40,     4,    32,    33,    25,    26,
      64,    68,    69,    64,    64,     3,    10,    12,    16,    17,
      23,    24,    28,    29,    31,    40,    41,    42,    64,    64,
      40,    40,    39,    64,    67,    64,    39,    39,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      39,     8,    39,    37,    22,    22,    64,    61,    61,    38,
      38,    11,    22,    61,    38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    54,    54,    55,    56,    57,    57,    58,    58,
      59,    60,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     4,     4,     2,     3,     1,     3,
       2,     3,     0,     2,     2,     2,     2,     3,     3,     3,
       2,     2,     7,    11,     7,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     3,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     1,     4,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "AND", "ASSIGN", "BOOL",
  "CLOSE", "COLON", "COMMA", "CONSOLE", "DASH", "ELSE", "EQUALS", "FALSE",
  "FILE", "FN", "GREATER", "GREATEREQ", "ID", "IF", "INT", "INTLITERAL",
  "LCURLY", "LESS", "LESSEQ", "LPAREN", "LBRACE", "NOT", "NOTEQUALS", "OR",
  "OPEN", "CROSS", "POSTDEC", "POSTINC", "QUESTION", "READ", "RETURN",
  "RBRACE", "RCURLY", "RPAREN", "SEMICOL", "SLASH", "STAR",
  "STRINGLITERAL", "TRUE", "VOID", "WHILE", "WRITE", "$accept", "program",
  "globals", "decl", "varDecl", "type", "primType", "arrayType", "fnDecl",
  "formals", "formalsList", "formalDecl", "fnBody", "stmtList", "stmt",
  "blockStmt", "exp", "assignExp", "callExp", "actualsList", "term", "loc",
  "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   189,   189,   195,   202,   206,   207,   209,   215,   219,
     224,   228,   232,   236,   241,   246,   249,   251,   254,   259,
     265,   268,   272,   277,   282,   288,   290,   292,   294,   296,
     298,   300,   303,   305,   307,   310,   312,   314,   316,   318,
     320,   322,   324,   326,   328,   330,   332,   334,   336,   338,
     340,   343,   348,   352,   357,   362,   368,   370,   372,   374,
     376,   378,   380,   383,   385,   388,   390
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
    };
    // Last valid token kind.
    const int code_max = 302;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "jeff.yy"
} // jeff
#line 1696 "parser.cc"

#line 393 "jeff.yy"


void jeff::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
