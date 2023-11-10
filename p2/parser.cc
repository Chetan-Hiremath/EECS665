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
#line 32 "jeff.yy"

   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex

#line 61 "parser.cc"


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
#line 135 "parser.cc"

  /// Build a parser object.
  Parser::Parser (jeff::Scanner &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
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
#line 160 "jeff.yy"
                 {}
#line 592 "parser.cc"
    break;

  case 3: // globals: globals varDecl SEMICOL
#line 162 "jeff.yy"
                                 {}
#line 598 "parser.cc"
    break;

  case 4: // globals: globals FN COLON fnDecl
#line 163 "jeff.yy"
                                 {}
#line 604 "parser.cc"
    break;

  case 5: // globals: %empty
#line 164 "jeff.yy"
                       {}
#line 610 "parser.cc"
    break;

  case 6: // varDecl: type id
#line 166 "jeff.yy"
                 {}
#line 616 "parser.cc"
    break;

  case 7: // type: primType
#line 168 "jeff.yy"
               {}
#line 622 "parser.cc"
    break;

  case 8: // type: arrayType
#line 169 "jeff.yy"
                {}
#line 628 "parser.cc"
    break;

  case 9: // primType: INT
#line 171 "jeff.yy"
              {}
#line 634 "parser.cc"
    break;

  case 10: // primType: BOOL
#line 172 "jeff.yy"
               {}
#line 640 "parser.cc"
    break;

  case 11: // primType: VOID
#line 173 "jeff.yy"
               {}
#line 646 "parser.cc"
    break;

  case 12: // primType: FILE
#line 174 "jeff.yy"
               {}
#line 652 "parser.cc"
    break;

  case 13: // arrayType: primType LBRACE INTLITERAL RBRACE
#line 176 "jeff.yy"
                                             {}
#line 658 "parser.cc"
    break;

  case 14: // fnDecl: LPAREN formals RPAREN type id LCURLY stmtList RCURLY
#line 178 "jeff.yy"
                                                             {}
#line 664 "parser.cc"
    break;

  case 15: // fnDecl: LPAREN RPAREN type id LCURLY stmtList RCURLY
#line 179 "jeff.yy"
                                                     {}
#line 670 "parser.cc"
    break;

  case 16: // formals: formalDecl
#line 181 "jeff.yy"
                    {}
#line 676 "parser.cc"
    break;

  case 17: // formals: formals COMMA formalDecl
#line 182 "jeff.yy"
                                  {}
#line 682 "parser.cc"
    break;

  case 18: // formalDecl: type id
#line 184 "jeff.yy"
                    {}
#line 688 "parser.cc"
    break;

  case 19: // stmtList: stmtList stmt SEMICOL
#line 186 "jeff.yy"
                                {}
#line 694 "parser.cc"
    break;

  case 20: // stmtList: stmtList blockStmt
#line 187 "jeff.yy"
                             {}
#line 700 "parser.cc"
    break;

  case 21: // stmtList: %empty
#line 188 "jeff.yy"
                        {}
#line 706 "parser.cc"
    break;

  case 22: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 190 "jeff.yy"
                                                          {}
#line 712 "parser.cc"
    break;

  case 23: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 191 "jeff.yy"
                                                       {}
#line 718 "parser.cc"
    break;

  case 24: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 192 "jeff.yy"
                                                                                   {}
#line 724 "parser.cc"
    break;

  case 25: // stmt: varDecl
#line 194 "jeff.yy"
              {}
#line 730 "parser.cc"
    break;

  case 26: // stmt: id ASSIGN exp
#line 195 "jeff.yy"
                    {}
#line 736 "parser.cc"
    break;

  case 27: // stmt: OPEN READ loc STRINGLITERAL
#line 196 "jeff.yy"
                                  {}
#line 742 "parser.cc"
    break;

  case 28: // stmt: OPEN WRITE loc STRINGLITERAL
#line 197 "jeff.yy"
                                   {}
#line 748 "parser.cc"
    break;

  case 29: // stmt: CLOSE loc
#line 198 "jeff.yy"
                {}
#line 754 "parser.cc"
    break;

  case 30: // stmt: loc POSTDEC
#line 199 "jeff.yy"
                  {}
#line 760 "parser.cc"
    break;

  case 31: // stmt: loc POSTINC
#line 200 "jeff.yy"
                  {}
#line 766 "parser.cc"
    break;

  case 32: // stmt: loc READ loc
#line 201 "jeff.yy"
                   {}
#line 772 "parser.cc"
    break;

  case 33: // stmt: loc WRITE exp
#line 202 "jeff.yy"
                    {}
#line 778 "parser.cc"
    break;

  case 34: // stmt: RETURN exp
#line 203 "jeff.yy"
                 {}
#line 784 "parser.cc"
    break;

  case 35: // stmt: RETURN
#line 204 "jeff.yy"
             {}
#line 790 "parser.cc"
    break;

  case 36: // stmt: callExp
#line 205 "jeff.yy"
              {}
#line 796 "parser.cc"
    break;

  case 37: // exp: exp DASH exp
#line 207 "jeff.yy"
                  {}
#line 802 "parser.cc"
    break;

  case 38: // exp: exp CROSS exp
#line 208 "jeff.yy"
                   {}
#line 808 "parser.cc"
    break;

  case 39: // exp: exp STAR exp
#line 209 "jeff.yy"
                  {}
#line 814 "parser.cc"
    break;

  case 40: // exp: exp SLASH exp
#line 210 "jeff.yy"
                   {}
#line 820 "parser.cc"
    break;

  case 41: // exp: LPAREN exp QUESTION exp COLON exp RPAREN
#line 211 "jeff.yy"
                                              {}
#line 826 "parser.cc"
    break;

  case 42: // exp: exp AND exp
#line 212 "jeff.yy"
                 {}
#line 832 "parser.cc"
    break;

  case 43: // exp: exp OR exp
#line 213 "jeff.yy"
                {}
#line 838 "parser.cc"
    break;

  case 44: // exp: exp EQUALS exp
#line 214 "jeff.yy"
                    {}
#line 844 "parser.cc"
    break;

  case 45: // exp: exp NOTEQUALS exp
#line 215 "jeff.yy"
                       {}
#line 850 "parser.cc"
    break;

  case 46: // exp: exp GREATER exp
#line 216 "jeff.yy"
                     {}
#line 856 "parser.cc"
    break;

  case 47: // exp: exp GREATEREQ exp
#line 217 "jeff.yy"
                       {}
#line 862 "parser.cc"
    break;

  case 48: // exp: exp LESS exp
#line 218 "jeff.yy"
                  {}
#line 868 "parser.cc"
    break;

  case 49: // exp: exp LESSEQ exp
#line 219 "jeff.yy"
                    {}
#line 874 "parser.cc"
    break;

  case 50: // exp: NOT exp
#line 220 "jeff.yy"
             {}
#line 880 "parser.cc"
    break;

  case 51: // exp: DASH term
#line 221 "jeff.yy"
               {}
#line 886 "parser.cc"
    break;

  case 52: // exp: term
#line 222 "jeff.yy"
          {}
#line 892 "parser.cc"
    break;

  case 53: // callExp: id LPAREN RPAREN
#line 224 "jeff.yy"
                          {}
#line 898 "parser.cc"
    break;

  case 54: // callExp: id LPAREN actualsList RPAREN
#line 225 "jeff.yy"
                                      {}
#line 904 "parser.cc"
    break;

  case 55: // actualsList: exp
#line 227 "jeff.yy"
                 {}
#line 910 "parser.cc"
    break;

  case 56: // actualsList: actualsList COMMA exp
#line 228 "jeff.yy"
                                   {}
#line 916 "parser.cc"
    break;

  case 57: // term: loc
#line 231 "jeff.yy"
          {}
#line 922 "parser.cc"
    break;

  case 58: // term: INTLITERAL
#line 232 "jeff.yy"
                 {}
#line 928 "parser.cc"
    break;

  case 59: // term: STRINGLITERAL
#line 233 "jeff.yy"
                    {}
#line 934 "parser.cc"
    break;

  case 60: // term: TRUE
#line 234 "jeff.yy"
           {}
#line 940 "parser.cc"
    break;

  case 61: // term: FALSE
#line 235 "jeff.yy"
            {}
#line 946 "parser.cc"
    break;

  case 62: // term: LPAREN exp RPAREN
#line 236 "jeff.yy"
                        {}
#line 952 "parser.cc"
    break;

  case 63: // term: callExp
#line 237 "jeff.yy"
              {}
#line 958 "parser.cc"
    break;

  case 64: // loc: id
#line 239 "jeff.yy"
        {}
#line 964 "parser.cc"
    break;

  case 65: // loc: id LBRACE exp RBRACE
#line 240 "jeff.yy"
                          {}
#line 970 "parser.cc"
    break;

  case 66: // id: ID
#line 242 "jeff.yy"
       {}
#line 976 "parser.cc"
    break;

  case 67: // id: CONSOLE
#line 243 "jeff.yy"
            {}
#line 982 "parser.cc"
    break;


#line 986 "parser.cc"

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


  const signed char Parser::yypact_ninf_ = -36;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -36,     7,    16,   -36,   -36,   -36,     1,   -36,   -36,   -26,
      39,    -1,   -36,    -3,   -36,   -36,   -36,   -36,    25,     4,
     -36,    -8,    36,    39,    -4,   -36,   -36,    39,   -36,    36,
      36,    29,   -36,    39,   -36,    37,    71,   -36,    39,    38,
      47,   452,   -36,    53,   -36,   -36,    43,   -36,    93,     8,
     113,   -36,    58,   452,    39,    39,   190,   -36,   -36,   452,
     452,   -36,   -36,   416,   -36,   -36,   -36,   -20,   452,   -36,
     -36,   -36,    39,   452,   452,   425,   452,   -36,   240,    44,
      49,   452,   -36,   207,   443,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   273,   -36,   416,
     416,   -36,   416,     3,   306,    57,   -36,   -36,   328,   452,
     -36,   443,   -36,   466,   466,   466,   466,   466,   466,   443,
      17,   -36,    17,    64,   452,   -36,   -36,   -36,   361,   -36,
     416,   136,   452,   159,    82,   383,   -36,    73,   -36,   -36,
     182,   -36
  };

  const signed char
  Parser::yydefact_[] =
  {
       5,     0,     2,     1,    10,    12,     0,     9,    11,     0,
       0,     7,     8,     0,     3,    67,    66,     6,     0,     0,
       4,     0,     0,     0,     0,    16,    13,     0,    18,     0,
       0,     0,    17,     0,    21,     0,     0,    21,     0,     0,
       0,    35,    15,     0,    25,    20,     0,    36,     0,    64,
       0,    29,    64,     0,     0,     0,     0,    61,    58,     0,
       0,    59,    60,    34,    63,    52,    57,    64,     0,    19,
      30,    31,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,    51,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
      26,    53,    55,     0,     0,     0,    27,    28,     0,     0,
      62,    42,    37,    44,    46,    47,    48,    49,    45,    43,
      38,    40,    39,     0,     0,    54,    65,    21,     0,    21,
      56,     0,     0,     0,    23,     0,    22,     0,    41,    21,
       0,    24
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -36,   -36,   -36,   102,   117,   -36,   -36,   -36,   -36,    79,
     -27,   -36,   -36,   -21,   -34,   -36,    54,   -35,   -10
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,    44,    10,    11,    12,    20,    24,    25,
      36,    45,    46,    63,    64,   103,    65,    66,    67
  };

  const short
  Parser::yytable_[] =
  {
      17,    48,    47,    51,    29,    75,    76,     3,    13,     4,
      50,   124,    74,    28,    14,    48,    47,    31,     5,    79,
      80,     4,    19,    35,     7,    18,    49,    86,    52,    26,
       5,     6,    78,    75,    76,    30,     7,    98,    83,    84,
      49,     4,   125,    22,    52,    52,    21,    97,    15,     8,
       5,    34,    99,   100,   102,   104,     7,    16,    95,    37,
     108,     8,    52,    53,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,     4,    38,    68,   127,
      15,     8,    54,    69,    76,     5,   129,   106,   128,    16,
      39,     7,   107,   137,    55,   139,    48,    47,    48,    47,
     131,    40,   133,   130,     9,    48,    47,    41,    32,    42,
      82,   135,   140,     0,     0,     0,     8,    43,     4,    38,
       0,    49,    15,    49,     0,    70,    71,     5,    72,     0,
      49,    16,    39,     7,     0,     0,    23,     0,     0,    27,
      73,     4,    38,    40,     0,    15,    23,    33,     0,    41,
       5,    77,     0,     0,    16,    39,     7,     0,     8,    43,
       0,     0,     0,     0,     4,    38,    40,     0,    15,     0,
       0,     0,    41,     5,   134,     0,     0,    16,    39,     7,
       0,     8,    43,     0,     0,     0,     0,     4,    38,    40,
       0,    15,     0,     0,     0,    41,     5,   136,     0,    15,
      16,    39,     7,    57,     8,    43,     0,     0,    16,     0,
      85,    58,    40,     0,     0,    81,     0,    86,    41,    87,
     141,     0,     0,    88,    89,     0,     0,     8,    43,     0,
      90,    91,     0,    61,    62,    92,    93,     0,    94,     0,
       0,   109,     0,    85,     0,     0,   110,     0,    95,    96,
      86,     0,    87,     0,     0,     0,    88,    89,     0,     0,
       0,     0,     0,    90,    91,     0,     0,     0,    92,    93,
       0,    94,     0,     0,     0,     0,    85,     0,     0,   105,
       0,    95,    96,    86,     0,    87,     0,     0,     0,    88,
      89,     0,     0,     0,     0,     0,    90,    91,     0,     0,
       0,    92,    93,     0,    94,     0,     0,     0,     0,    85,
       0,     0,   123,     0,    95,    96,    86,     0,    87,     0,
       0,     0,    88,    89,     0,     0,     0,     0,     0,    90,
      91,    85,     0,     0,    92,    93,     0,    94,    86,     0,
      87,     0,     0,   126,    88,    89,     0,    95,    96,     0,
       0,    90,    91,     0,     0,     0,    92,    93,     0,    94,
       0,     0,     0,     0,    85,     0,     0,   110,   132,    95,
      96,    86,     0,    87,     0,     0,     0,    88,    89,     0,
       0,     0,     0,     0,    90,    91,    85,     0,     0,    92,
      93,     0,    94,    86,     0,    87,     0,     0,     0,    88,
      89,     0,    95,    96,     0,     0,    90,    91,     0,     0,
       0,    92,    93,     0,    94,     0,     0,     0,     0,    85,
       0,     0,   138,     0,    95,    96,    86,     0,    87,     0,
       0,     0,    88,    89,    15,    56,     0,     0,    57,    90,
      91,     0,     0,    16,    92,    93,    58,    94,     0,     0,
      59,     0,    60,    86,     0,    87,     0,    95,    96,    88,
      89,    15,    56,     0,   101,    57,    90,    91,    61,    62,
      16,    92,     0,    58,    94,     0,    86,    59,    -1,    60,
       0,     0,    -1,    -1,    95,    96,     0,     0,     0,    -1,
      -1,     0,     0,     0,    -1,    61,    62,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96
  };

  const short
  Parser::yycheck_[] =
  {
      10,    36,    36,    38,     8,    25,    26,     0,     7,     5,
      37,     8,     4,    23,    40,    50,    50,    27,    14,    54,
      55,     5,    25,    33,    20,    26,    36,    10,    38,    37,
      14,    15,    53,    25,    26,    39,    20,    72,    59,    60,
      50,     5,    39,    39,    54,    55,    21,    68,     9,    45,
      14,    22,    73,    74,    75,    76,    20,    18,    41,    22,
      81,    45,    72,    25,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     5,     6,    25,    22,
       9,    45,    35,    40,    26,    14,    22,    43,   109,    18,
      19,    20,    43,    11,    47,    22,   131,   131,   133,   133,
     127,    30,   129,   124,     2,   140,   140,    36,    29,    38,
      56,   132,   139,    -1,    -1,    -1,    45,    46,     5,     6,
      -1,   131,     9,   133,    -1,    32,    33,    14,    35,    -1,
     140,    18,    19,    20,    -1,    -1,    19,    -1,    -1,    22,
      47,     5,     6,    30,    -1,     9,    29,    30,    -1,    36,
      14,    38,    -1,    -1,    18,    19,    20,    -1,    45,    46,
      -1,    -1,    -1,    -1,     5,     6,    30,    -1,     9,    -1,
      -1,    -1,    36,    14,    38,    -1,    -1,    18,    19,    20,
      -1,    45,    46,    -1,    -1,    -1,    -1,     5,     6,    30,
      -1,     9,    -1,    -1,    -1,    36,    14,    38,    -1,     9,
      18,    19,    20,    13,    45,    46,    -1,    -1,    18,    -1,
       3,    21,    30,    -1,    -1,    25,    -1,    10,    36,    12,
      38,    -1,    -1,    16,    17,    -1,    -1,    45,    46,    -1,
      23,    24,    -1,    43,    44,    28,    29,    -1,    31,    -1,
      -1,    34,    -1,     3,    -1,    -1,    39,    -1,    41,    42,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    31,    -1,    -1,    -1,    -1,     3,    -1,    -1,    39,
      -1,    41,    42,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    39,    -1,    41,    42,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    23,
      24,     3,    -1,    -1,    28,    29,    -1,    31,    10,    -1,
      12,    -1,    -1,    37,    16,    17,    -1,    41,    42,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    39,     7,    41,
      42,    10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    23,    24,     3,    -1,    -1,    28,
      29,    -1,    31,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    -1,    41,    42,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    39,    -1,    41,    42,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,     9,    10,    -1,    -1,    13,    23,
      24,    -1,    -1,    18,    28,    29,    21,    31,    -1,    -1,
      25,    -1,    27,    10,    -1,    12,    -1,    41,    42,    16,
      17,     9,    10,    -1,    39,    13,    23,    24,    43,    44,
      18,    28,    -1,    21,    31,    -1,    10,    25,    12,    27,
      -1,    -1,    16,    17,    41,    42,    -1,    -1,    -1,    23,
      24,    -1,    -1,    -1,    28,    43,    44,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    49,    50,     0,     5,    14,    15,    20,    45,    51,
      52,    53,    54,     7,    40,     9,    18,    66,    26,    25,
      55,    21,    39,    52,    56,    57,    37,    52,    66,     8,
      39,    66,    57,    52,    22,    66,    58,    22,     6,    19,
      30,    36,    38,    46,    51,    59,    60,    62,    65,    66,
      58,    65,    66,    25,    35,    47,    10,    13,    21,    25,
      27,    43,    44,    61,    62,    64,    65,    66,    25,    40,
      32,    33,    35,    47,     4,    25,    26,    38,    61,    65,
      65,    25,    64,    61,    61,     3,    10,    12,    16,    17,
      23,    24,    28,    29,    31,    41,    42,    61,    65,    61,
      61,    39,    61,    63,    61,    39,    43,    43,    61,    34,
      39,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    39,     8,    39,    37,    22,    61,    22,
      61,    58,     7,    58,    38,    61,    38,    11,    39,    22,
      58,    38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    50,    51,    52,    52,    53,
      53,    53,    53,    54,    55,    55,    56,    56,    57,    58,
      58,    58,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    66,    66
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     3,     4,     0,     2,     1,     1,     1,
       1,     1,     1,     4,     8,     7,     1,     3,     2,     3,
       2,     0,     7,     7,    11,     1,     3,     4,     4,     2,
       2,     2,     3,     3,     2,     1,     1,     3,     3,     3,
       3,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     4,     1,     1
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
  "globals", "varDecl", "type", "primType", "arrayType", "fnDecl",
  "formals", "formalDecl", "stmtList", "blockStmt", "stmt", "exp",
  "callExp", "actualsList", "term", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   160,   160,   162,   163,   164,   166,   168,   169,   171,
     172,   173,   174,   176,   178,   179,   181,   182,   184,   186,
     187,   188,   190,   191,   192,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   224,   225,   227,   228,   231,   232,   233,
     234,   235,   236,   237,   239,   240,   242,   243
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
#line 1663 "parser.cc"

#line 247 "jeff.yy"


void jeff::Parser::error(const std::string& msg){
	//For the project, we will only be checking std::cerr for 
	// correctness. You might choose to uncomment the following
	// Line to help you debug, since it gives slightly more 
	// descriptive error messages 
	//std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
