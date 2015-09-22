#ifndef MATH_POSTFIX_HPP
#define MATH_POSTFIX_HPP

#include "expr.hpp"

#include <iostream>

namespace math
{

void postfix(std::ostream&, Expr const*);

}

#endif