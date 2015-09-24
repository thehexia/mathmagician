#include "sexpr.hpp"
#include "print.hpp"
#include "evaluate-expr.hpp"

#include <cmath>

namespace math
{


void
sexpr_integer(std::ostream& os, Number_expr const* e)
{
  os << e->val(); 
}


void
sexpr_arithmetic(std::ostream& os, Arithmetic_expr const* e)
{
  // eval and check, if error return with no print
  if (std::isnan(evaluate(e)))
    return;

  os << '(';
  os << op_name(e->op()) << ' ';
  sexpr(os, e->lhs());
  os << ' ';
  sexpr(os, e->rhs());
  os << ')';
}


void
sexpr_neg(std::ostream& os, Neg_expr const* e)
{
  os << "(- ";
  sexpr(os, e->operand());
  os << ')';
}


void
sexpr(std::ostream& os, Expr const* e)
{
  switch (e->kind) {
    case number_expr: return sexpr_integer(os, dynamic_cast<Number_expr const*>(e));
    case arithmetic_expr: return sexpr_arithmetic(os, dynamic_cast<Arithmetic_expr const*>(e));
    case neg_expr: return sexpr_neg(os, dynamic_cast<Neg_expr const*>(e));
  }
  error("Unknown expression in sexpr notation.");
}

} // namespace math