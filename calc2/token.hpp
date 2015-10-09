#ifndef MATH_TOKEN_HPP
#define MATH_TOKEN_HPP

#include "prelude.hpp"

#include <list>
#include <iostream>

namespace math
{

struct Symbol;

enum Token_kind
{
  lparen_tok, // (
  rparen_tok, // )

  // operators
  plus_tok,   // +
  minus_tok,  // -
  star_tok,   // *
  fslash_tok, // /
  mod_tok,    // %

  // literal classes
  number_tok, // numbers
  bool_tok,   // true / false

  // handling error tokens
  error_tok,
  eof_tok,
};

// Retains location, token kind, and original string in the program
struct Token
{
  Token(int loc, Symbol const* sym)
    : loc_(loc), sym_(sym)
  { }

  Token_kind kind() const;

  Symbol const* symbol() const;
  String const* str() const;

  int loc_;
  Symbol const* sym_;
};


// loc_ == -1 on error tokens

inline bool
is_error_tok(Token const& tok)
{
  return tok.kind() == error_tok;
}


// loc_ == -2 to handle bad spaces at end of file
inline bool
is_eof_tok(Token const& tok)
{
  return tok.kind() == eof_tok;
}


using Token_list = std::vector<Token>;

// Stream of tokens to easily manipulate token list
struct Token_stream
{
  Token_stream(Token_list& tl)
    : tl(tl), begin_(tl.begin()), end_(tl.end())
  { }

  Token const* expect(Token_kind);
  Token const* next();
  Token const* advance();

  bool eof() const { return begin_ == end_; }

  Token_list& tl;
  std::vector<Token>::iterator begin_;
  std::vector<Token>::iterator end_;
};


Token const* expect(Token_list&, Token_kind);

char const* token_name(Token_kind const);

void install_tokens();


} // namespace math


#endif

