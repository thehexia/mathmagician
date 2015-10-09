#include "token.hpp"

#include <cassert>

namespace math
{

// prints the token name for debugging reasons
const char*
token_name(Token_kind const k)
{
  switch (k) {
    case lparen_tok: return "lparen_tok";
    case rparen_tok: return "rparen_tok";

    // operators
    case plus_tok: return "plus_tok";
    case minus_tok: return "minus_tok";
    case star_tok: return "star_tok";
    case fslash_tok: return "fslash_tok";
    case mod_tok: return "mod_tok";

    // literal classes
    case number_tok: return "number_tok";

    // handling error tokens
    case error_tok: return "error_tok";
  }

  return "nothing_tok";
}

// if the next token is of kind 'k' return it
// otherwise return nullptr
Token const*
Token_stream::expect(Token_kind k)
{
  if(eof())
    return nullptr;  

  if ((*begin_).kind() == k) {
    Token const* t = &*begin_;
    begin_++;
    return t;
  }

  return nullptr;
}


// return next token without advancing
// return nullptr if eof
Token const*
Token_stream::next()
{
  if(eof())
    return nullptr;

  return &*begin_;
}

// return next token and advance past it
// returns nullptr if eof
Token const*
Token_stream::advance()
{
  if (eof())
    return nullptr;

  Token const* t = &*begin_;
  begin_++;
  return t;
}

}