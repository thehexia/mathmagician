#ifndef MATH_PARSE_EXPR_HPP
#define MATH_PARSE_EXPR_HPP

#include "parse.hpp"

namespace math
{

// returns the precedence of a given token
int precedence(Token_kind);

// parsing terms in the language
Expr* parse_paren_enclosed(Parser&, Token_stream&);
Expr* parse_binary(Parser&, Token_stream&);
Expr* parse_number(Parser&, Token_stream&);
Expr* parse_primary_expr(Parser&, Token_stream&);
Expr* parse_unary_expr(Parser&, Token_stream&);


Expr* parse_expr(Parser&, Token_stream&);

} // namespace math

#endif