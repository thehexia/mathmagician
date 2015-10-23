#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

#include "type.hpp"

namespace math
{

inline bool
is_int_type(Type const* t)
{
  return t->kind() == int_type;
}


inline bool
is_double_type(Type const* t)
{
  return t->kind() == double_type;
}


inline bool
is_reals_type(Type const* t)
{
  return is_int_type(t) || is_double_type(t);
}


inline bool
is_bool_type(Type const* t)
{
  return t->kind() == bool_type;
}

} // namespace math


#endif