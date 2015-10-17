#include "type.hpp"
#include "utility.hpp"
#include "print.hpp"

namespace math
{

namespace
{

// Fundamental types which never change
Bool_type bool_t;
Int_type int_t;
Double_type double_t;

} // namespace

// -------------------------------------------- //
//          Type construction

Type*
get_bool_type()
{
  return &bool_t;
}


Type*
get_int_type()
{
  return &int_t;
}


Type*
get_double_type()
{
  return &double_t;
}


// -------------------------------------------- //
//          Type checking

Type* type_check_arithmetic(Expr const* e1, Expr const* e2)
{
  if (is_reals_type(e1->type())) {
    if (is_reals_type(e2->type()))
      return get_double_type();
    else {
      error("Expression not of integer or double type found in arithmetic expression: ");
      print(e2);
      print("\n");
    }
  }
  else {
      error("Expression not of integer or double type found in arithmetic expression: ");
      print(e1);
      print("\n");
  }

  return nullptr;
}


Type* type_check_logical(Expr const* e1, Expr const* e2)
{
  if (is_bool_type(e1->type())) {
    if (is_bool_type(e2->type()))
      return get_bool_type();
    else {
      error("Expression not of bool type found in logical expression: ");
      print(e2);
      print("\n");
    }
  }
  else {
      error("Expression not of bool type found in logical expression: ");
      print(e1);
      print("\n");
  }

  return nullptr;
}


Type* type_check_ordering(Expr const* e1, Expr const* e2)
{
  if (is_reals_type(e1->type())) {
    if (is_reals_type(e2->type()))
      return get_bool_type();
    else {
      error("Expression not of integer or double type found in ordering expression: ");
      print(e2);
      print("\n");
    }
  }
  else {
      error("Expression not of integer or double type found in ordering expression: ");
      print(e1);
      print("\n");
  }

  return nullptr;
}


Type* type_check_equality(Expr const* e1, Expr const* e2)
{
  if (e1->type() == e2->type())
    return get_bool_type();
  else {
    error("Expressions of mismatched types found in equality expressions: ");
    print(e1);
    print(" and ");
    print(e2);
    print("\n");
  }

  return nullptr;
}


Type* type_check_negative(Expr const* e1)
{
  if (is_reals_type(e1->type()))
    // FIXME: flip between int and doubles correctly
    return get_double_type();

  error("Expression not of integer or double type found in negative expression: ");
  print(e1);
  print("\n");

  return nullptr;
}


Type* type_check_positive(Expr const* e1)
{
  if (is_reals_type(e1->type()))
    // FIXME: flip between int and doubles correctly
    return get_double_type();

  error("Expression not of integer or double type found in positive expression: ");
  print(e1);
  print("\n");

  return nullptr;
}


Type* type_check_not(Expr const* e1)
{ 
  if (is_bool_type(e1->type()))
    return get_bool_type();

  error("Expression not of bool type found in not expression: ");
  print(e1);
  print("\n");

  return nullptr;
}


} // namespace math