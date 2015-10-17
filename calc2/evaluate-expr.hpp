#ifndef MATH_EVAL_EXPR_HPP
#define MATH_EVAL_EXPR_HPP

#include "expr.hpp"
#include "type.hpp"
#include "value.hpp"

namespace math
{

// double for future decimal support
Value evaluate(Expr const* e);

} // namespace math

#endif
