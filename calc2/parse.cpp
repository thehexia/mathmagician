#include "parse.hpp"
#include "parse-expr.hpp"
#include "print.hpp"

#include <iostream>

namespace math
{

// Assuming the token string is a valid integer or decimal representation
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


// Handles the negative operator
Expr*
Parser::on_unary(Expr const* e)
{
  return new Neg_expr(e);
}



// Entry point to parser
Expr*
parse(Parser& p, Token_stream& tl)
{
  Expr* e = parse_expr(p, tl);
  // check if there is a random extra expression after the first
  // expression is parsed.
  if (Expr* unexpected = parse_expr(p, tl)) {
    error("Unexpected expression ");
    print(unexpected);
    print(" after ");
    print(e);
    print("\n");
    return nullptr;
  }
  // if no expression was parse to begin with
  if (!e)
    error("Invalid expression at beginning of input.");

  return e;
}


} // namespace math
