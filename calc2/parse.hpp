#ifndef MATH_PARSE_HPP
#define MATH_PARSE_HPP

#include "expr.hpp"
#include "token.hpp"

namespace math
{

// constructs nodes in the AST after successful parse
struct Parser
{
  // returns on expression from parsing 
  Expr* on_binary(Token const*, Expr const*, Expr const*);
  Expr* on_unary(Token const*, Expr const*);
  Expr* on_number(Token const*);
  Expr* on_bool(Token const*);
};


// Entry point to the parsing algorithm
// takes a parser object which constructs nodes in the AST
// and a token stream representing the program
Expr* parse(Parser& p, Token_stream&);

}

#endif
