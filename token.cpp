#include "token.hpp"

#include <cassert>

namespace math
{

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
    case integer_tok: return "integer_tok";

    // handling error tokens
    case error_tok: return "error_tok";
  }

  return "nothing_tok";
}


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


Token const*
Token_stream::next()
{
  if(eof())
    return nullptr;

  return &*begin_;
}


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