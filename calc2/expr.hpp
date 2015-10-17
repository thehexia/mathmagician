#ifndef MATH_EXPR_HPP
#define MATH_EXPR_HPP

#include "prelude.hpp"

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
  Expr(Expr_kind k, Type* t) 
    : kind(k), type_(t)
  { }

  virtual ~Expr() { };

  Type const* type() const { return type_; }

  Expr_kind kind;
  Type* type_; 
};


// Numbers
//  integers
//  doubles
struct Number_expr : Expr
{
  Number_expr(double n, Type* t)
    : Expr(number_expr, t), first(n)
  { }

  double val() const { return first; }

  double first;
};


struct Bool_expr : Expr
{
  Bool_expr(bool b, Type* t)
    : Expr(bool_expr, t), first(b)
  { }

  bool val() const { return first; }

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
  Unary_expr(Unary_op op, Expr* e1, Type* t)
    : Expr(unary_expr, t), first(e1), second(op)
  { }

  Expr const* operand() const { return first; }
  Unary_op op() const { return second; }

  Expr* first;
  Unary_op second;
};


// arithmetic operators
enum Binary_op
{
  add_op,
  sub_op,
  div_op,
  mul_op,
  mod_op,
  lor_op,
  land_op,
  eq_op,
  not_eq_op,
  less_op,
  less_eq_op,
  greater_op,
  greater_eq_op
};


// Arithmetic exprs
// e1 + e2
// e1 - e2
// e1 * e2
// e1 / e2
// e1 % e2
struct Binary_expr : Expr
{
  Binary_expr(Binary_op op, Expr* e1, Expr* e2, Type* t)
    : Expr(binary_expr, t), first(op), second(e1), third(e2)
  { }

  Binary_op op() const { return first; }
  Expr const* lhs() const { return second; }
  Expr const* rhs() const { return third; }

  Binary_op first;
  Expr* second;
  Expr* third;
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
    case lor_op: return "||";
    case land_op: return "&&";
    case eq_op: return "==";
    case not_eq_op: return "!=";
    case less_op: return "<";
    case less_eq_op: return "<=";
    case greater_op: return ">";
    case greater_eq_op: return ">=";
  }
  return "error";
}


} // namespace

#endif
