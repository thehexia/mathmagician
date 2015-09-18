#ifndef MATH_SEXPR_HPP
#define MATH_SEXPR_HPP

#include "expr.hpp"

#include <iostream>

namespace math
{

void sexpr(std::ostream&, Expr const*);

} // namespace math

#endif