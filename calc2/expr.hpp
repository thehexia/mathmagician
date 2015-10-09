#ifndef MATH_EXPR_HPP
#define MATH_EXPR_HPP

#include <iostream>

namespace math
{


enum Expr_kind
{
  number_expr,
  neg_expr,
  arithmetic_expr
};


// Base Expr class
struct Expr
{
  Expr(Expr_kind k) 
    : kind(k)
  { }

  virtual ~Expr() { };

  Expr_kind kind;
};


// Numbers
//  integers
//  doubles
struct Number_expr : Expr
{
  Number_expr(double n)
    : Expr(number_expr), first(n)
  { }

  double val() const { return first; }

  double first;
};


// Unary negation expr
// - number
// - (expr)
struct Neg_expr : Expr
{
  Neg_expr(Expr const* e1)
    : Expr(neg_expr), first(e1)
  { }

  Expr const* operand() const { return first; }

  Expr const* first;
};

// arithmetic operators
enum Arithmetic_op
{
  add_op,
  sub_op,
  div_op,
  mul_op,
  mod_op,
};


// Arithmetic exprs
// e1 + e2
// e1 - e2
// e1 * e2
// e1 / e2
// e1 % e2
struct Arithmetic_expr : Expr
{
  Arithmetic_expr(Arithmetic_op op, Expr const* e1, Expr const* e2)
    : Expr(arithmetic_expr), first(op), second(e1), third(e2)
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
