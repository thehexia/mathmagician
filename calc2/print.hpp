#ifndef MATH_PRINT_HPP
#define MATH_PRINT_HPP

#include "expr.hpp"
#include "type.hpp"
#include "value.hpp"
#include "token.hpp"


namespace math
{

void print(Token const*);
void print(Expr const*);
void print(char const*);
void print(Value const&);

void error(char const* c);


inline void
print(Token_list& tl)
{
  for (auto it : tl) {
    std::cout << "[\'" + *it.str() + "\'] " + token_name(it.kind()) + "\n"; 
  }
}

} // namespace math

#endif