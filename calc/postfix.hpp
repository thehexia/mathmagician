#ifndef MATH_POSTFIX_HPP
#define MATH_POSTFIX_HPP

#include "expr.hpp"

#include <iostream>

namespace math
{

// prints postfix exprs
void postfix(std::ostream&, Expr const*);

}

#endif