#include "print.hpp"

#include <iostream>

namespace math
{

bool
is_integer(Expr const* e)
{
  return dynamic_cast<Number_expr const*>(e);
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
print_paren_enclosed(Expr const* e)
{
  std::cout << '(';
  print(e);
  std::cout << ')';
}


void
print(Binary_expr const* e)
{
  if(is_integer(e->lhs()))
    print(e->lhs());
  else
    print_paren_enclosed(e->lhs());

  std::cout << ' ' << op_name(e->op()) << ' ';

  if(is_integer(e->rhs()))
    print(e->rhs());
  else
    print_paren_enclosed(e->rhs());

}


void
print(Unary_expr const* e)
{
  std::cout << "-(";
  print(e->operand());
  std::cout << ")";
}


void
print(Expr const* e)
{
  if (Number_expr const* ex = dynamic_cast<Number_expr const*>(e))
    print(ex);
  else if (Binary_expr const* ex = dynamic_cast<Binary_expr const*>(e))
    print(ex);
  else if (Unary_expr const* ex = dynamic_cast<Unary_expr const*>(e))
    print(ex);
  else
    std::cout << "nan";
}


} // namespace math