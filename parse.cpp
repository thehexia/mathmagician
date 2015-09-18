#include "parse.hpp"
#include "parse-expr.hpp"
#include <iostream>

namespace math
{

Expr*
Parser::on_number(Token const* tok)
{
  return new Number_expr(stod(tok->str()));
}


// Assuming the token is the arithmetic operator
Expr*
Parser::on_arithmetic(Token const* tok, Expr const* e1, Expr const* e2)
{
  switch (tok->kind()) {
    case plus_tok: return new Arithmetic_expr(add_op, e1, e2);
    case minus_tok: return new Arithmetic_expr(sub_op, e1, e2);
    case star_tok: return new Arithmetic_expr(mul_op, e1, e2);
    case fslash_tok: return new Arithmetic_expr(div_op, e1, e2);
    case mod_tok: return new Arithmetic_expr(mod_op, e1, e2);
    default:
      return nullptr;
  }
}


Expr*
parse(Parser& p, Token_stream& tl)
{
  return parse_expr(p, tl);
}


} // namespace math
