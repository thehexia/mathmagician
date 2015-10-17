#ifndef MATH_TYPE_HPP
#define MATH_TYPE_HPP

#include "prelude.hpp"

namespace math
{

enum Type_kind
{
  bool_type,
  int_type,
  double_type,
};

// base class for all types
struct Type
{
  Type(Type_kind k)
    : kind_(k)
  { }

  ~Type() { }

  Type_kind kind() const { return kind_; }

  Type_kind kind_;
};


// boolean type
// we don't really need any fancy information
// with the bool type
struct Bool_type : Type 
{
  Bool_type()
    : Type(bool_type)
  { }
};


// all real numbers
struct Reals_type : Type
{
  using Type::Type;
};


// integer type
struct Int_type : Reals_type
{
  Int_type()
    : Reals_type(int_type)
  { }
};


struct Double_type : Reals_type
{
  Double_type()
    : Reals_type(double_type)
  { }
};


Type* get_int_type();
Type* get_double_type();
Type* get_bool_type();

Type* type_check_arithmetic(Expr const*, Expr const*);
Type* type_check_logical(Expr const*, Expr const*);
Type* type_check_ordering(Expr const*, Expr const*);
Type* type_check_equality(Expr const*, Expr const*);


Type* type_check_negative(Expr const*);
Type* type_check_positive(Expr const*);
Type* type_check_not(Expr const*);

} // namespace

#endif