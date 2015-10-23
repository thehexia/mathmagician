#include "parse.hpp"
#include "parse-expr.hpp"
#include "print.hpp"
#include "symbol.hpp"
#include "type.hpp"

#include <iostream>

namespace math
{


namespace
{

// if double is an integer
bool
is_int(double i)
{
  return (int)i == i;
}


// ------------------------------------------------ //
//            Unary Expr creation

Expr*
on_negative_op(Expr* e)
{
  // The type of e should be a subset of reals type
  // Type t should be a subset of reals type
  if (Type* t = type_check_negative(e))
    return new Unary_expr(neg_op, e, t);

  return nullptr;
}


Expr*
on_positive_op(Expr* e)
{
  // The type of e should be a subset of reals type
  // Type t should be a subset of reals type
  if (Type* t = type_check_positive(e))
    return new Unary_expr(pos_op, e, t);

  return nullptr;
}


Expr*
on_not_op(Expr* e)
{
  // The type of e should be bool type
  // Type t should be bool
  if (Type* t = type_check_not(e))
    return new Unary_expr(not_op, e, t);

  return nullptr;
}



// ------------------------------------------------ //
//            Binary Expr creation

Expr*
on_arithmetic_op(Binary_op op, Expr* e1, Expr* e2)
{
  // check for same type and reals.
  // e1 and e2 should have a subset of the Reals type.
  // Type t shall either be int type or double type
  // depending on the widest width between e1's type and
  // e2's type.
  if (Type* t = type_check_arithmetic(e1, e2))
    return new Binary_expr(op, e1, e2, t);

  return nullptr;
}


Expr*
on_logical_op(Binary_op op, Expr* e1, Expr* e2)
{
  // check for same type and reals
  // Type t should be bool
  // The type of e1 and e2 should be bool
  if (Type* t = type_check_logical(e1, e2))
    return new Binary_expr(op, e1, e2, t);

  return nullptr;
}


Expr*
on_ordering_op(Binary_op op, Expr* e1, Expr* e2)
{
  // check for same type and reals
  // Type t should be of bool type
  if (Type* t = type_check_ordering(e1, e2))
    return new Binary_expr(op, e1, e2, t);

  return nullptr;
}


Expr*
on_equality_op(Binary_op op, Expr* e1, Expr* e2)
{
  // check for same type and reals
  // Type t should be of bool type
  if (Type* t = type_check_equality(e1, e2))
    return new Binary_expr(op, e1, e2, t);

  return nullptr;
}


} // namespace

// Assuming the token string is a valid integer or decimal representation
//
// FIXME: Making everything a double now for the sake of
// convenience. In the future implement type conversions on real numbers
Expr*
Parser::on_number(Token const* tok)
{
  return new Number_expr(tok->symbol()->value(), get_double_type());
}


Expr*
Parser::on_bool(Token const* tok)
{
  return (*tok->str() == "true") ? new Bool_expr(true, get_bool_type()) : new Bool_expr(false, get_bool_type());
}


// Assuming the token is the arithmetic operator
Expr*
Parser::on_binary(Token const* tok, Expr* e1, Expr* e2)
{
  switch (tok->kind()) {
    // arithmetic operators
    case plus_tok: return on_arithmetic_op(add_op, e1, e2);
    case minus_tok: return on_arithmetic_op(sub_op, e1, e2);
    case star_tok: return on_arithmetic_op(mul_op, e1, e2);
    case fslash_tok: return on_arithmetic_op(div_op, e1, e2);
    case mod_tok: return on_arithmetic_op(mod_op, e1, e2);

    // logical operators
    case log_or_tok: return on_logical_op(lor_op, e1, e2);
    case log_and_tok: return on_logical_op(land_op, e1, e2);

    // equality operators
    case eq_eq_tok: return on_equality_op(eq_op, e1, e2);
    case bang_eq_tok: return on_equality_op(not_eq_op, e1, e2);

    // ordering
    case less_tok: return on_ordering_op(less_op, e1, e2);
    case less_eq_tok: return on_ordering_op(less_eq_op, e1, e2);
    case great_tok: return on_ordering_op(greater_op, e1, e2);
    case great_eq_tok: return on_ordering_op(greater_eq_op, e1, e2); 
    default:
      return nullptr;
  }
}


// Handles the negative operator
Expr*
Parser::on_unary(Token const* tok, Expr* e)
{
  switch  (tok->kind()) {
    case plus_tok: return on_positive_op(e);
    case minus_tok: return on_negative_op(e);
    case bang_tok: return on_not_op(e);
    default:
      return nullptr;
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
  if (!tl.eof()) {
    error("Unexpected tokens remaining in expression.");
    return nullptr;
  }

  return e;
}


} // namespace math
