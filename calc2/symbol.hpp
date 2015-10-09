#ifndef MATH_SYMBOL_HPP
#define MATH_SYMBOL_HPP

#include "token.hpp"

#include <unordered_map>
#include <string>

namespace math
{

using String = std::string;

// Maintain the original string and the token kind
// Optionally maintains a value if that token was a number
struct Symbol
{
  Symbol(Token_kind tok, String s)
    : tok_(tok), str_(s)
  {
    val = (tok_ == number_tok) ? stod(s) : -1; 
  }

  Token_kind kind() const { return tok_; }
  String const* str() const { return &str_; }
  double value() const { return (tok_ == number_tok) ? val : -1; }


  Token_kind tok_;
  String str_;

  double val;
};


// Symbol table maps strings to symbol information
struct Symbol_table
{
  ~Symbol_table();

  void insert(String s, Symbol* sym) { map.insert({s, sym}); }

  Symbol const* find(String const s) const 
  { 
    auto search = map.find(s);
    if (search != map.end())
      return search->second;

    return nullptr;
  }

private:
  std::unordered_map<String, Symbol*> map;
};


void install_symbol(Token_kind, String);

Symbol const* get_symbol(String const);

}

#endif