#ifndef MATH_PARSE_HPP
#define MATH_PARSE_HPP

#include "expr.hpp"
#include "token.hpp"

namespace math
{

struct Parser
{
  // returns on expression from parsing 
  Expr* on_arithmetic(Token const*, Expr const*, Expr const*);
  Expr* on_number(Token const*);
  Expr* on_unary(Expr const*);
};


Expr* parse(Parser& p, Token_stream&);

}

#endif