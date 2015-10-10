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


bool is_alpha(char const& c)
{
  return std::isalpha(c);
}


bool is_identifier_rest(char const& c)
{
  return std::isalpha(c) || std::isdigit(c);
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

  // install then get
  install_symbol(number_tok, number);
  return Token(loc, get_symbol(number));
}


Token
lex_identifier(int loc, Char_stream& cs)
{
  assert(is_alpha(cs.peek()));

  String id;
  id.append(&cs.get(), 1);

  while (!cs.eof()) {
    // if the next char is part of the identifier
    if (is_identifier_rest(cs.peek())) {
      id.append(&cs.get(), 1);
    }
    // if it is no longer an id char
    else
      break;
  }

  // look things up in the symbol table
  Symbol const* sym = get_symbol(id);

  // if it exists
  if (sym) {
    return Token(loc, sym);
  }
  else {
    install_symbol(identifier_tok, id);
    assert(get_symbol(id));
    return Token(loc, get_symbol(id));
  }
}


// Lex a single character
Token
lex_char(int loc, char const cs)
{
  return Token(loc, get_symbol(String(1, cs)));
}


bool
nth_char_is(Char_stream& cs, int n, char c)
{
  if(char const* nth = cs.peek_n(n))
    return *nth == c;

  return false;
}


// Attempts to lex a digraph
// If fails, lexes a monograph
Token
lex_digraph(int loc, Char_stream& cs, char digraph)
{
  char const& f = cs.get();
  if (!cs.eof()) {
    String s;
    s.append(&f, 1);
    // check next char
    if (cs.peek() == digraph) {
      s.append(&cs.get(), 1);
      if (Symbol const* sym = get_symbol(s))
        return Token(loc, sym);
    }
  }

  return Token(loc, get_symbol("1err"));
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
      case '&':
        if (nth_char_is(cs, 1, '&'))
          return lex_digraph(cs.location(), cs, '&');
        else
          return lex_char(cs.location(), cs.get());
      case '|':
        if (nth_char_is(cs, 1, '|'))
          return lex_digraph(cs.location(), cs, '|');
        else
          return lex_char(cs.location(), cs.get());
      case '<':
        if (nth_char_is(cs, 1, '='))
          return lex_digraph(cs.location(), cs, '=');
        else
          return lex_char(cs.location(), cs.get());
      case '>':
        if (nth_char_is(cs, 1, '='))
          return lex_digraph(cs.location(), cs, '=');
        else
          return lex_char(cs.location(), cs.get());
      case '=':
        if (nth_char_is(cs, 1, '='))
          return lex_digraph(cs.location(), cs, '=');
        else
          return lex_char(cs.location(), cs.get());
      case '!':
        if (nth_char_is(cs, 1, '='))
          return lex_digraph(cs.location(), cs, '=');
        else
          return lex_char(cs.location(), cs.get());

      default:  
        // if it starts with a digit we assume its a number
        if (is_digit(cs.peek()))
          return lex_number(cs.location(), cs);
        // if it starts with an alpha character it is a keyword or an id
        else if(is_alpha(cs.peek()))
          return lex_identifier(cs.location(), cs);
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
