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
  if (Number_expr const* ex = dynamic_cast<Number_expr const*>(e))
    sexpr_integer(os, ex);
  else if (Arithmetic_expr const* ex = dynamic_cast<Arithmetic_expr const*>(e))
    sexpr_arithmetic(os, ex);
  else if (Neg_expr const* ex = dynamic_cast<Neg_expr const*>(e))
    sexpr_neg(os, ex);
}

} // namespace math