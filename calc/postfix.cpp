#include "postfix.hpp"
#include "print.hpp"
#include "evaluate-expr.hpp"

#include <cmath>

namespace math
{

void
postfix_integer(std::ostream& os, Number_expr const* e)
{
  os << e->val(); 
}


void
postfix_arithmetic(std::ostream& os, Arithmetic_expr const* e)
{
  // eval and check, if error return with no print
  if (std::isnan(evaluate(e)))
    return;

  postfix(os, e->lhs());
  os << ' ';
  postfix(os, e->rhs());
  os << ' ';
  os << op_name(e->op());
}


// A special operator 'neg' must be used in
// postfix notation. The reason is to disambiguate the
// unary operator - with the binary operator -
// For example, if we used the same symbol
// -(20 + 11) - (-7 * 4) => 20 11 +- 7- 4 * -
// which is actually
// -((-(20 + 11) - 7) * 4)
// which is not correct
void
postfix_neg(std::ostream& os, Neg_expr const* e)
{
  postfix(os, e->operand());
  os << " neg";
}


// Dispatch to the appropriate printer
// using dynamic casts instead of visitor because
// its way easier to do this with only three
// nodes in the tree
void
postfix(std::ostream& os, Expr const* e)
{
  if (Number_expr const* ex = dynamic_cast<Number_expr const*>(e))
    postfix_integer(os, ex);
  else if (Arithmetic_expr const* ex = dynamic_cast<Arithmetic_expr const*>(e))
    postfix_arithmetic(os, ex);
  else if (Neg_expr const* ex = dynamic_cast<Neg_expr const*>(e))
    postfix_neg(os, ex);
  else
    error("Unknown expression in postfix notation.");
}

} // namespace math