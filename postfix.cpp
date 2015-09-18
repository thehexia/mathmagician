#include "postfix.hpp"

namespace math
{

void
postfix_integer(std::ostream& os, Integer_expr const* e)
{
  os << e->val(); 
}


void
postfix_arithmetic(std::ostream& os, Arithmetic_expr const* e)
{
  postfix(os, e->lhs());
  os << ' ';
  postfix(os, e->rhs());
  os << ' ';
  os << op_name(e->op());
}


void
postfix(std::ostream& os, Expr const* e)
{
  if (Integer_expr const* ex = dynamic_cast<Integer_expr const*>(e))
    postfix_integer(os, ex);
  else if (Arithmetic_expr const* ex = dynamic_cast<Arithmetic_expr const*>(e))
    postfix_arithmetic(os, ex);
}

} // namespace math