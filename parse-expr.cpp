
#include "prelude.hpp"
#include "token.hpp"
#include "parse-expr.hpp"

namespace math
{


int
precedence(Token_kind k)
{
  switch (k) {
  case integer_tok:
    return 0; 
  case star_tok: 
  case fslash_tok:
  case mod_tok:
    return 1;
  case plus_tok:
  case minus_tok:
    return 2;
  default:
    return -1;
  }
}


Expr*
parse_paren_enclosed(Parser& p, Token_stream& tl)
{
  return nullptr;
}


Expr* 
parse_integer(Parser& p, Token_stream& tl)
{
  if (Token const* tok = tl.expect(integer_tok))
    return p.on_integer(tok);
  return nullptr;
}


Expr*
parse_unary(Parser& p, Token_stream& tl)
{
  return nullptr;
}


Expr*
parse_primary_expr(Parser& p, Token_stream& tl)
{
  switch (tl.next()->kind()) {
    case integer_tok: return parse_integer(p, tl);
    case plus_tok:
    case minus_tok:
      return parse_unary(p, tl);
    default:
      return nullptr;
  }
}


Expr*
parse_expr(Parser& p, Token_stream& tl)
{
  // parse primary expressions
  return parse_primary_expr(p, tl);
}


} // namespace math