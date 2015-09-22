#ifndef MATH_SEXPR_HPP
#define MATH_SEXPR_HPP

#include "expr.hpp"

#include <iostream>

namespace math
{

// prints sexpr format
void sexpr(std::ostream&, Expr const*);

} // namespace math

#endif