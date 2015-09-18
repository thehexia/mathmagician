#include "sexpr.hpp"

namespace math
{

void
sexpr_integer(std::ostream& os, Integer_expr const* e)
{
  os << e->val(); 
}


void
sexpr_arithmetic(std::ostream& os, Arithmetic_expr const* e)
{
  os << '(';
  os << op_name(e->op()) << ' ';
  sexpr(os, e->lhs());
  os << ' ';
  sexpr(os, e->rhs());
  os << ')';
}


void
sexpr(std::ostream& os, Expr const* e)
{
  if (Integer_expr const* ex = dynamic_cast<Integer_expr const*>(e))
    sexpr_integer(os, ex);
  else if (Arithmetic_expr const* ex = dynamic_cast<Arithmetic_expr const*>(e))
    sexpr_arithmetic(os, ex);
}

} // namespace math