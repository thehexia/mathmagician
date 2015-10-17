#ifndef MATH_PRELUDE_HPP
#define MATH_PRELUDE_HPP

#include <string>
#include <vector>


namespace math
{

using String = std::string;

struct Expr;
struct Number_expr;
struct Bool_expr;
struct Binary_expr;
struct Unary_expr;

struct Type;
struct Bool_type;
struct Reals_type;
struct Int_type;
struct Double_type;

} // namespace math

#endif