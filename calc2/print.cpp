#include "print.hpp"

#include <iostream>

namespace math
{

bool
is_integer(Expr const* e)
{
  return dynamic_cast<Number_expr const*>(e);
}


bool
is_bool(Expr const* e)
{
  return dynamic_cast<Bool_expr const*>(e);
}


void
error(char const* c)
{
  std::cout << c << '\n';
}


void
print(char const* c)
{
  std::cout << c << '\n';
}


void
print(Token const* t)
{
  std::cout << *t->str() << ' ';
}


void
print(Number_expr const* e)
{
  std::cout << e->val();
}


void
print(Bool_expr const* e)
{
  (e->value()) ? std::cout << "true" : std::cout << "false";
}


void
print_paren_enclosed(Expr const* e)
{
  std::cout << '(';
  print(e);
  std::cout << ')';
}


void
print(Binary_expr const* e)
{
  if(is_integer(e->lhs()) || is_bool(e->lhs()))
    print(e->lhs());
  else
    print_paren_enclosed(e->lhs());

  std::cout << ' ' << op_name(e->op()) << ' ';

  if(is_integer(e->rhs()) || is_bool(e->rhs()))
    print(e->rhs());
  else
    print_paren_enclosed(e->rhs());

}


void
print(Unary_expr const* e)
{
  switch (e->op()) {
    case pos_op: std::cout << "+"; break;
    case neg_op: std::cout << "-"; break;
    case not_op: std::cout << "!"; break;
  }
  
  std::cout << "(";
  print(e->operand());
  std::cout << ")";
}


void
print(Expr const* e)
{
  if (e)
    switch (e->kind) {
      case number_expr: return print(dynamic_cast<Number_expr const*>(e));
      case bool_expr: return print(dynamic_cast<Bool_expr const*>(e));
      case binary_expr: return print(dynamic_cast<Binary_expr const*>(e));
      case unary_expr: return print(dynamic_cast<Unary_expr const*>(e));
    }
  
  std::cout << "nan";
}


} // namespace math