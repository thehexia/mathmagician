#ifndef MATH_VALUE_HPP
#define MATH_VALUE_HPP

#include <iostream>

struct Value
{
  // default construction of value shall be error value
  Value()
    : is_number(false), is_bool(false), is_err(true)
  { }

  Value(bool b)
    : b(b), is_number(false), is_bool(true), is_err(false)
  { }

  Value(double d)
    : d(d), is_number(true), is_bool(false), is_err(false)
  { }

  Value(int i)
    : d(i), is_number(true), is_bool(false), is_err(false)
  { }

  bool is_boolean() const { return is_bool; }
  bool is_double() const { return is_number; }
  bool is_error() const { return is_err; }

  double get_double() const { return d; }
  double get_bool() const { return b; }

private:
  union {
    double d;
    bool b;
  };

  bool is_number;
  bool is_bool;
  bool is_err;
};


inline std::ostream& operator<<(std::ostream& os, Value const& v)
{
  if (v.is_boolean()) return (v.get_bool()) ? os << "true" : os << "false";
  if (v.is_double()) return os << std::boolalpha << v.get_double();

  return os << "<error value>";
}

#endif