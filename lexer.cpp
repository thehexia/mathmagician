#include "lexer.hpp"
#include "print.hpp"

#include <locale>
#include <iostream>
#include <cassert>

namespace math
{

namespace
{

// A digit is defined as a single character between
// 0 and 9
bool
is_digit(char const& cs)
{
  return cs == '0'
      || cs == '1'
      || cs == '2'
      || cs == '3'
      || cs == '4'
      || cs == '5'
      || cs == '6'
      || cs == '7'
      || cs == '8'
      || cs == '9';
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
      return Token(loc, error_tok, "error");
    }
    else 
      break;
  }

  return Token(loc, number_tok, number);
}

// Lex a single character
Token
lex_char(int loc, Token_kind k, char const& cs, int len)
{
  return Token(loc, k, String(len, cs));
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
        return Token(-1, error_tok, "error");
      // if its a space, consume and continue
      case ' ': 
        cs.get();
        break;
      // if its a single character token
      case '+': return lex_char(cs.location(), plus_tok, cs.get(), 1);
      case '-': return lex_char(cs.location(), minus_tok, cs.get(), 1);
      case '*': return lex_char(cs.location(), star_tok, cs.get(), 1);
      case '/': return lex_char(cs.location(), fslash_tok, cs.get(), 1);
      case '%': return lex_char(cs.location(), mod_tok, cs.get(), 1);
      case '(': return lex_char(cs.location(), lparen_tok, cs.get(), 1);
      case ')': return lex_char(cs.location(), rparen_tok, cs.get(), 1);
      default:  
        // if its none of those then it has to be a number or identifier
        if (is_digit(cs.peek()))
          return lex_number(cs.location(), cs);
        else {
          std::cout << "ERROR: unrecognized token: " << cs.get() << '\n';
          return Token(-1, error_tok, "error");
        }
    }
  }

  // handles trailing spaces which don't end in anything
  return Token(-2, error_tok, "eof");
}


Token_list
lex(Char_stream& cs)
{
  Token_list tl;
  Lexer lex(cs);

  while (!cs.eof()) {
    Token tok = lex.lex();
    if (!is_error_tok(tok))
      tl.push_back(tok);
    else {
      tl.clear();
      return tl;
    }
  }

  return tl;
}

} // namespace math
