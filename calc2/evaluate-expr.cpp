#include "evaluate-expr.hpp"
#include "print.hpp"
#include "value.hpp"

#include <cassert>
#include <cmath>

namespace math
{

// if double is an integer
bool
is_int(double i)
{
  return (int)i == i;
}

// Evaluation of a number is itself
Value
evaluate(Number_expr const* e)
{
  return Value(e->val());
}

// Evaluation of a boolean is itself
Value
evaluate(Bool_expr const* e)
{
  return Value(e->val());
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs + rhs
Value
evaluate_add(Binary_expr const* e)
{
  assert(e->op() == add_op);
  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  if (std::isnan(lhs.get_double()) || std::isnan(rhs.get_double()))
    return Value(std::nan("error"));

  return Value(lhs.get_double() + rhs.get_double());
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs - rhs
Value
evaluate_sub(Binary_expr const* e)
{
  assert(e->op() == sub_op);
  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  if (std::isnan(lhs.get_double()) || std::isnan(rhs.get_double()))
    return Value(std::nan("error"));

  return Value(lhs.get_double() - rhs.get_double());
}



// Evaluate the lhs and rhs
// If either are nan then return nan
// If rhs is 0 return nan
// else return lhs / rhs 
Value 
evaluate_div(Binary_expr const* e)
{
  assert(e->op() == div_op);
  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  if (std::isnan(lhs.get_double()) || std::isnan(rhs.get_double()))
    return Value(std::nan("error"));

  if (rhs.get_double() == 0) {
    error("Error: Division by zero.");
    return Value(std::nan("error"));
  }

  return Value(lhs.get_double() / rhs.get_double());
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// else return lhs * rhs
Value
evaluate_mul(Binary_expr const* e)
{
  assert(e->op() == mul_op);
  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  if (std::isnan(lhs.get_double()) || std::isnan(rhs.get_double()))
    return Value(std::nan("error"));

  return Value(lhs.get_double() * rhs.get_double());
}


// Evaluate the lhs and rhs
// If either are nan then return nan
// if rhs == 0 return nan
// if lhs || rhs are not integers return nan
// else return lhs % rhs
Value
evaluate_mod(Binary_expr const* e)
{
  assert(e->op() == mod_op);
  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  if (std::isnan(lhs.get_double()) || std::isnan(rhs.get_double()))
    return Value(std::nan("error"));

  if (rhs.get_double() == 0) {
    error("Error: Modulo by zero.");
    return Value(std::nan("error"));
  }

  if (is_int(lhs.get_double()) && is_int(rhs.get_double()))
    return Value((int)(lhs.get_double()) % (int)(rhs.get_double()));

  error("Error: Modulo by decimal.");
  return Value(std::nan("error"));
}

Value
evaluate_lor(Binary_expr const* e)
{
  assert(e->op() == lor_op);
  assert(e->lhs()->type() == get_bool_type());
  assert(e->rhs()->type() == get_bool_type());  

  Value lhs = evaluate(e->lhs());

  assert(lhs.is_boolean());

  // if lhs is false then continue evaluating
  if (!lhs.get_bool()) {
    // the return depends on if rhs is true or false
    return evaluate(e->rhs());
  }
  // otherwise if lhs is true the return immediately
  return lhs;
}


Value
evaluate_land(Binary_expr const* e)
{
  assert(e->op() == land_op);
  assert(e->lhs()->type() == get_bool_type());
  assert(e->rhs()->type() == get_bool_type());  

  Value lhs = evaluate(e->lhs());

  assert(lhs.is_boolean());

  // if lhs is true
  if (lhs.get_bool()) {
    Value rhs = evaluate(e->rhs());
    assert(rhs.is_boolean());
    // and if rhs is true then the result is true
    if (rhs.get_bool()) {
      return rhs;
    }
    // otherwise false
    return rhs;
  }

  // if lhs is false then the whole expr value is false
  return lhs;
}


Value
evaluate_equal(Binary_expr const* e)
{
  assert(e->op() == eq_op);
  assert(e->lhs()->type() == e->rhs()->type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  if (lhs.is_double()) {
    assert(lhs.is_double());
    assert(rhs.is_double());

    return lhs.get_double() == rhs.get_double();
  }

  if (lhs.is_boolean()) {
    assert(lhs.is_boolean());
    assert(rhs.is_boolean());

    return lhs.get_bool() == rhs.get_bool();
  }

  error("Error: invalid evaluation of ==.");
  return Value(std::nan("error"));
}


Value
evaluate_not_equal(Binary_expr const* e)
{
  assert(e->op() == not_eq_op);
  assert(e->lhs()->type() == e->rhs()->type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  if (lhs.is_double()) {
    assert(lhs.is_double());
    assert(rhs.is_double());

    return lhs.get_double() != rhs.get_double();
  }

  if (lhs.is_boolean()) {
    assert(lhs.is_boolean());
    assert(rhs.is_boolean());

    return lhs.get_bool() != rhs.get_bool();
  }

  error("Error: invalid evaluation of !=.");
  return Value(std::nan("error"));
}


Value
evaluate_less(Binary_expr const* e)
{
  assert(e->op() == less_op);
  assert(e->lhs()->type() == get_double_type());
  assert(e->rhs()->type() == get_double_type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  return lhs.get_double() < rhs.get_double();
}


Value
evaluate_less_equal(Binary_expr const* e)
{
  assert(e->op() == less_eq_op);
  assert(e->lhs()->type() == get_double_type());
  assert(e->rhs()->type() == get_double_type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  return lhs.get_double() <= rhs.get_double();
}


Value
evaluate_greater(Binary_expr const* e)
{
  assert(e->op() == greater_op);
  assert(e->lhs()->type() == get_double_type());
  assert(e->rhs()->type() == get_double_type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  return lhs.get_double() > rhs.get_double();
}


Value
evaluate_greater_equal(Binary_expr const* e)
{
  assert(e->op() == greater_eq_op);
  assert(e->lhs()->type() == get_double_type());
  assert(e->rhs()->type() == get_double_type());

  Value lhs = evaluate(e->lhs());
  Value rhs = evaluate(e->rhs());

  assert(lhs.is_double());
  assert(rhs.is_double());

  return lhs.get_double() >= rhs.get_double();
}


// Any invalid operators result in undefined behavior
Value
evaluate(Binary_expr const* e)
{
  switch (e->op()) {
    case add_op: return evaluate_add(e);
    case sub_op: return evaluate_sub(e);
    case div_op: return evaluate_div(e);
    case mul_op: return evaluate_mul(e);
    case mod_op: return evaluate_mod(e);
    case lor_op: return evaluate_lor(e);
    case land_op: return evaluate_land(e);
    case eq_op: return evaluate_equal(e);
    case not_eq_op: return evaluate_not_equal(e);
    case less_op: return evaluate_less(e);
    case less_eq_op: return evaluate_less_equal(e);
    case greater_op: return evaluate_greater(e);
    case greater_eq_op: return evaluate_greater_equal(e);
  }

  error("Error: invalid operator kind.");
  return Value(std::nan("error"));
}


// Evaluate unary operator -
Value
evaluate_neg(Unary_expr const* e)
{
  assert(e->operand()->type() == get_double_type());

  Value val = evaluate(e->operand());

  assert(val.is_double());

  return Value(-1 * val.get_double());
}


// Evaluate unary operator +
Value
evaluate_pos(Unary_expr const* e)
{
  assert(e->operand()->type() == get_double_type());

  return evaluate(e->operand());
}


// Evaluate unary operator !
Value
evaluate_not(Unary_expr const* e)
{
  assert(e->operand()->type() == get_bool_type());

  Value val = evaluate(e->operand());

  assert(val.is_boolean());

  return Value(!val.get_bool());
}


// Evaluate unary operators + | - | !
Value
evaluate(Unary_expr const* e)
{
  switch (e->op()) {
    case neg_op: return evaluate_neg(e);
    case pos_op: return evaluate_pos(e);
    case not_op: return evaluate_not(e);
  }

  error("Error: invalid operator kind.");
  return Value(std::nan("error"));
}


// Dispatch for evaluation
Value
evaluate(Expr const* e)
{
  switch (e->kind) {
    case number_expr: return evaluate(dynamic_cast<Number_expr const*>(e));
    case bool_expr: return evaluate(dynamic_cast<Bool_expr const*>(e));
    case binary_expr: return evaluate(dynamic_cast<Binary_expr const*>(e));
    case unary_expr: return evaluate(dynamic_cast<Unary_expr const*>(e));
  }

  // error code is -1 million until i get a better solution
  error("Error: invalid expression kind.");
  return Value(std::nan("error"));
}

} // namespace math
