#include "parse.hpp"
#include "parse-expr.hpp"
#include "print.hpp"
#include "symbol.hpp"

#include <iostream>

namespace math
{

// Assuming the token string is a valid integer or decimal representation
Expr*
Parser::on_number(Token const* tok)
{
  return new Number_expr(tok->symbol()->value());
}


Expr*
Parser::on_bool(Token const* tok)
{
  return (*tok->str() == "true") ? new Bool_expr(true) : new Bool_expr(false);
}


// Assuming the token is the arithmetic operator
Expr*
Parser::on_binary(Token const* tok, Expr const* e1, Expr const* e2)
{
  switch (tok->kind()) {
    case plus_tok: return new Binary_expr(add_op, e1, e2);
    case minus_tok: return new Binary_expr(sub_op, e1, e2);
    case star_tok: return new Binary_expr(mul_op, e1, e2);
    case fslash_tok: return new Binary_expr(div_op, e1, e2);
    case mod_tok: return new Binary_expr(mod_op, e1, e2);
    case log_or_tok: return new Binary_expr(lor_op, e1, e2);
    case log_and_tok: return new Binary_expr(land_op, e1, e2);
    case eq_eq_tok: return new Binary_expr(eq_op, e1, e2);
    case bang_eq_tok: return new Binary_expr(not_eq_op, e1, e2);
    case less_tok: return new Binary_expr(less_op, e1, e2);
    case less_eq_tok: return new Binary_expr(less_eq_op, e1, e2);
    case great_tok: return new Binary_expr(greater_op, e1, e2);
    case great_eq_tok: return new Binary_expr(greater_eq_op, e1, e2); 
    default:
      return nullptr;
  }
}


// Handles the negative operator
Expr*
Parser::on_unary(Token const* tok, Expr const* e)
{
  switch  (tok->kind()) {
    case plus_tok: return new Unary_expr(pos_op, e);
    case minus_tok: return new Unary_expr(neg_op, e);
    case bang_tok: return new Unary_expr(not_op, e);
  }

  return nullptr;
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
