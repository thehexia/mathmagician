#ifndef MATH_LEXER_HPP
#define MATH_LEXER_HPP

#include "file.hpp"
#include "token.hpp"

namespace math
{

// Lexer takes a character stream and transforms it into a sequence of tokens
struct Lexer 
{
  Lexer(Char_stream& s)
    : cs(s)
  { }

  Token lex();

  Char_stream& cs;
};


Token_list lex(Char_stream&);

} // namespace math


#endif
