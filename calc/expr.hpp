#ifndef MATH_EXPR_HPP
#define MATH_EXPR_HPP

#include <iostream>

namespace math
{


// Base Expr cass
struct Expr
{
  virtual ~Expr() { };
};


// Numbers
struct Number_expr : Expr
{
  Number_expr(double n)
    : first(n)
  { }

  double val() const { return first; }

  double first;
};


// Unary negation expr
struct Neg_expr : Expr
{
  Neg_expr(Expr const* e1)
    : first(e1)
  { }

  Expr const* operand() const { return first; }

  Expr const* first;
};


enum Arithmetic_op
{
  add_op,
  sub_op,
  div_op,
  mul_op,
  mod_op,
};


// Arithmetic operator
struct Arithmetic_expr : Expr
{
  Arithmetic_expr(Arithmetic_op op, Expr const* e1, Expr const* e2)
    : first(op), second(e1), third(e2)
  { }

  Arithmetic_op op() const { return first; }
  Expr const* lhs() const { return second; }
  Expr const* rhs() const { return third; }

  Arithmetic_op first;
  Expr const* second;
  Expr const* third;
};



inline char const*
op_name(Arithmetic_op op)
{
  switch(op) {
    case add_op: return "+";
    case sub_op: return "-";
    case div_op: return "/";
    case mul_op: return "*";
    case mod_op: return "%";
  }
  return "error";
}


} // namespace

#endif
