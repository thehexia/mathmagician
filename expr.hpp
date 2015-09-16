#ifndef MATH_EXPR_HPP
#define MATH_EXPR_HPP

#include <iostream>

namespace math
{


// Base Expr cass
struct Expr
{
  Expr() { }
  virtual ~Expr() { };
};


// Integers
struct Integer_expr : Expr
{
  Integer_expr(int n)
    : first(n)
  { }

  int val() const { return first; }

  int first;
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


} // namespace

#endif
