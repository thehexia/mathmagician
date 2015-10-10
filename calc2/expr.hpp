#ifndef MATH_EXPR_HPP
#define MATH_EXPR_HPP

#include <iostream>

namespace math
{


enum Expr_kind
{
  number_expr,
  bool_expr,
  unary_expr,
  binary_expr
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


struct Bool_expr : Expr
{
  Bool_expr(bool b)
    : Expr(bool_expr), first(b)
  { }

  bool value() const { return first; }

  bool first;
};


enum Unary_op
{
  neg_op,
  pos_op,
  not_op,
};


// Unary negation expr
// -/+/! number
// -/+/! (expr)
struct Unary_expr : Expr
{
  Unary_expr(Expr const* e1)
    : Expr(unary_expr), first(e1)
  { }

  Expr const* operand() const { return first; }

  Expr const* first;
};

// arithmetic operators
enum Binary_op
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
struct Binary_expr : Expr
{
  Binary_expr(Binary_op op, Expr const* e1, Expr const* e2)
    : Expr(binary_expr), first(op), second(e1), third(e2)
  { }

  Binary_op op() const { return first; }
  Expr const* lhs() const { return second; }
  Expr const* rhs() const { return third; }

  Binary_op first;
  Expr const* second;
  Expr const* third;
};



inline char const*
op_name(Binary_op op)
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
