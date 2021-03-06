#ifndef MATH_TOKEN_HPP
#define MATH_TOKEN_HPP

#include "prelude.hpp"

#include <list>
#include <iostream>

namespace math
{

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
  number_tok, // integers

  // handling error tokens
  error_tok,
};

// Retains location, token kind, and original string in the program
struct Token
{
  Token(int loc, Token_kind k, String str)
    : loc_(loc), kind_(k), str_(str)
  { }

  Token_kind kind() const { return kind_; }
  String const str() const { return str_; }

  int loc_;
  Token_kind kind_;
  String str_;
};


// loc_ == -1 on error tokens
// loc_ == -2 to handle bad spaces at end of file
inline bool
is_error_tok(Token const& tok)
{
  return tok.kind() == error_tok && tok.loc_ == -1;
}


inline bool
is_eof_tok(Token const& tok)
{
  return tok.kind() == error_tok && tok.loc_ == -2;
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


} // namespace math


#endif

