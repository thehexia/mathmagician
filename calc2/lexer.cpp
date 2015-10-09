#include "lexer.hpp"
#include "symbol.hpp"
#include "print.hpp"

#include <locale>
#include <iostream>
#include <cassert>
#include <cctype>

namespace math
{

namespace
{

// A digit is defined as a single character between
// 0 and 9
bool
is_digit(char const& cs)
{
  return std::isdigit(cs);
}

// Function checks if we're beginning a decimal number
// with a '.' char
bool
is_decimal(char const& c)
{
  return c == '.';
}


// Lexing for numbers
// this handles integers, negative numbers, and decimal numbers
Token
lex_number(int loc, Char_stream& cs)
{
  String number;  
  bool decimal = false;

  // consume until we no longer have a digit
  while (!cs.eof()) {
    if (is_digit(cs.peek()))
      // append exactly 1 character
      number.append(&cs.get(), 1);
    // check if a decimal digit has been found yet
    else if (is_decimal(cs.peek()) && !decimal) {
      decimal = true;
      number.append(&cs.get(), 1);
    }
    // if we get more than one decimal point '.' in the same
    // number than bad things happened
    else if (is_decimal(cs.peek()) && decimal) {
      error("Stray decimal point.");
      return Token(loc, get_symbol("1err"));
    }
    else 
      break;
  }

  install_symbol(number_tok, number);
  return Token(loc, get_symbol(number));
}


// Lex a single character
Token
lex_char(int loc, char const cs)
{
  return Token(loc, get_symbol(String(1, cs)));
}


} // namespace


Token
Lexer::lex()
{
  assert(!cs.eof());

  while (!cs.eof()) {
    switch (cs.peek()) {
      case '\n': 
        std::cout << "Error: unexpected newline \n";
        cs.get();
        return Token(-1, get_symbol("1err"));
      // if its a space, consume and continue
      case ' ': 
        cs.get();
        break;
      // if its a single character token
      case '+':
      case '-':
      case '*':
      case '/':
      case '%': 
      case '(':
      case ')':
        return lex_char(cs.location(), cs.get());
      default:  
        // if its none of those then it has to be a number or identifier
        if (is_digit(cs.peek()))
          return lex_number(cs.location(), cs);
        else {
          std::cout << "ERROR: unrecognized token: " << cs.get() << '\n';
          return Token(-1, get_symbol("1err"));
        }
    }
  }

  // handles trailing spaces which don't end in anything
  return Token(-2, get_symbol("2eof"));
}


Token_list
lex(Char_stream& cs)
{
  Token_list tl;
  Lexer lex(cs);

  while (!cs.eof()) {
    Token tok = lex.lex();
    if (!is_error_tok(tok)) {
      if (!is_eof_tok(tok))
        tl.push_back(tok);
    }
    else {
      tl.clear();
      return tl;
    }
  }

  return tl;
}

} // namespace math
