#include "../prelude.hpp"
#include "../lexer.hpp"
#include "../file.hpp"
#include "../print.hpp"

#include <iostream>

using namespace math;

int main()
{
  Integer_expr* e1 = new Integer_expr(1);
  Integer_expr* e2 = new Integer_expr(2);

	Expr* add = new Arithmetic_expr(add_op, e1, e2);

  print(add);
}