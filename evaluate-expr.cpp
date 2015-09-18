#include "evaluate-expr.hpp"
#include "print.hpp"

#include <cassert>
#include <cmath>

namespace math
{

// because i dont want to deal with doubles
bool
isnan_int(int i)
{
  return i == -2147483648;
}


int 
evaluate(Number_expr const* e)
{
  return e->val();
}


int 
evaluate_add(Arithmetic_expr const* e)
{
  assert(e->op() == add_op);
  int lhs = evaluate(e->lhs());
  int rhs = evaluate(e->rhs());

  if (isnan_int(lhs) || isnan_int(rhs))
    return std::nan("error");

  return lhs + rhs;
}


int 
evaluate_sub(Arithmetic_expr const* e)
{
  assert(e->op() == sub_op);
  int lhs = evaluate(e->lhs());
  int rhs = evaluate(e->rhs());

  if (isnan_int(lhs) || isnan_int(rhs))
    return std::nan("error");

  return lhs - rhs;
}


int 
evaluate_div(Arithmetic_expr const* e)
{
  assert(e->op() == div_op);
  int lhs = evaluate(e->lhs());
  int rhs = evaluate(e->rhs());

  if (isnan_int(lhs) || isnan_int(rhs))
    return std::nan("error");

  if (rhs == 0) {
    error("Error: Division by zero.");
    return std::nan("error");
  }

  return lhs / rhs;
}


int 
evaluate_mul(Arithmetic_expr const* e)
{
  assert(e->op() == mul_op);
  int lhs = evaluate(e->lhs());
  int rhs = evaluate(e->rhs());

  if (isnan_int(lhs) || isnan_int(rhs))
    return std::nan("error");

  return lhs * rhs;
}


int 
evaluate_mod(Arithmetic_expr const* e)
{
  assert(e->op() == mod_op);
  int lhs = evaluate(e->lhs());
  int rhs = evaluate(e->rhs());

  if (isnan_int(lhs) || isnan_int(rhs))
    return std::nan("error");

  if (rhs == 0) {
    error("Error: Modulo by zero.");
    return std::nan("error");
  }

  return lhs % rhs;
}


// Any invalid operators result in undefined behavior
int 
evaluate(Arithmetic_expr const* e)
{
  switch (e->op()) {
    case add_op: return evaluate_add(e);
    case sub_op: return evaluate_sub(e);
    case div_op: return evaluate_div(e);
    case mul_op: return evaluate_mul(e);
    case mod_op: return evaluate_mod(e);
  }

  // error code is -1 million until i get a better solution
  error("Error: invalid operator kind.");
  return std::nan("error");
}


int
evaluate(Expr const* e)
{
  if (Number_expr const* in = dynamic_cast<Number_expr const*>(e))
    return evaluate(in);
  if (Arithmetic_expr const* ar = dynamic_cast<Arithmetic_expr const*>(e))
    return evaluate(ar);

  // error code is -1 million until i get a better solution
  error("Error: invalid expression kind.");
  return std::nan("error");
}

} // namespace math
