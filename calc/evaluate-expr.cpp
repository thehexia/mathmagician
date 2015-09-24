#include "evaluate-expr.hpp"
#include "print.hpp"

#include <cassert>
#include <cmath>

namespace math
{

// if double is an integer
bool
is_int(double i)
{
  return floorf(i) == i;
}

// evaluation of a number_expr is its double representation
double 
evaluate(Number_expr const* e)
{
  return e->val();
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs + rhs
double 
evaluate_add(Arithmetic_expr const* e)
{
  assert(e->op() == add_op);
  double lhs = evaluate(e->lhs());
  double rhs = evaluate(e->rhs());

  if (std::isnan(lhs) || std::isnan(rhs))
    return std::nan("error");

  return lhs + rhs;
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs - rhs
double 
evaluate_sub(Arithmetic_expr const* e)
{
  assert(e->op() == sub_op);
  double lhs = evaluate(e->lhs());
  double rhs = evaluate(e->rhs());

  if (std::isnan(lhs) || std::isnan(rhs))
    return std::nan("error");

  return lhs - rhs;
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// If rhs is 0 return nan
// else return lhs / rhs 
double 
evaluate_div(Arithmetic_expr const* e)
{
  assert(e->op() == div_op);
  double lhs = evaluate(e->lhs());
  double rhs = evaluate(e->rhs());

  if (std::isnan(lhs) || std::isnan(rhs))
    return std::nan("error");

  if (rhs == 0) {
    error("Error: Division by zero.");
    return std::nan("error");
  }

  return lhs / rhs;
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs * rhs
double 
evaluate_mul(Arithmetic_expr const* e)
{
  assert(e->op() == mul_op);
  double lhs = evaluate(e->lhs());
  double rhs = evaluate(e->rhs());

  if (std::isnan(lhs) || std::isnan(rhs))
    return std::nan("error");

  return lhs * rhs;
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// if rhs == 0 return nan
// if lhs || rhs are not integers return nan
// else return lhs % rhs
double 
evaluate_mod(Arithmetic_expr const* e)
{
  assert(e->op() == mod_op);
  double lhs = evaluate(e->lhs());
  double rhs = evaluate(e->rhs());

  if (std::isnan(lhs) || std::isnan(rhs))
    return std::nan("error");

  if (rhs == 0) {
    error("Error: Modulo by zero.");
    return std::nan("error");
  }

  if (is_int(lhs) && is_int(rhs))
    return (int)lhs % (int)rhs;

  error("Error: Modulo by decimal.");
  return std::nan("error");
}


// Any invalid operators result in undefined behavior
double 
evaluate(Arithmetic_expr const* e)
{
  switch (e->op()) {
    case add_op: return evaluate_add(e);
    case sub_op: return evaluate_sub(e);
    case div_op: return evaluate_div(e);
    case mul_op: return evaluate_mul(e);
    case mod_op: return evaluate_mod(e);
  }

  error("Error: invalid operator kind.");
  return std::nan("error");
}


// Evaluation of a neg_expr is
// multiplying its operand by -1
double
evaluate(Neg_expr const* e)
{
  return -1 * evaluate(e->operand());
}


// Dispatch for evaluation
double
evaluate(Expr const* e)
{
  switch (e->kind) {
    case number_expr: return evaluate(dynamic_cast<Number_expr const*>(e));
    case arithmetic_expr: return evaluate(dynamic_cast<Arithmetic_expr const*>(e));
    case neg_expr: return evaluate(dynamic_cast<Neg_expr const*>(e));
  }

  // error code is -1 million until i get a better solution
  error("Error: invalid expression kind.");
  return std::nan("error");
}

} // namespace math
