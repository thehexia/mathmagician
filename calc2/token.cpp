#include "token.hpp"
#include "symbol.hpp"

#include <cassert>

namespace math
{

// Token member definitions
Token_kind Token::kind() const { return sym_->kind(); }
Symbol const* Token::symbol() const { return sym_; }
String const* Token::str() const { return sym_->str(); }

// prints the token name for debugging reasons
const char*
token_name(Token_kind const k)
{
  switch (k) {
    case lparen_tok: return "lparen_tok";
    case rparen_tok: return "rparen_tok";

    // operators
    case plus_tok: return "plus_tok";
    case minus_tok: return "minus_tok";
    case star_tok: return "star_tok";
    case fslash_tok: return "fslash_tok";
    case mod_tok: return "mod_tok";

    // literal classes
    case number_tok: return "number_tok";
    case bool_tok: return "bool_tok";

    // handling error tokens
    case error_tok: return "error_tok";
    case eof_tok: return "eof_tok";
  }

  return "nothing_tok";
}

// if the next token is of kind 'k' return it
// otherwise return nullptr
Token const*
Token_stream::expect(Token_kind k)
{
  if(eof())
    return nullptr;  

  if ((*begin_).kind() == k) {
    Token const* t = &*begin_;
    begin_++;
    return t;
  }

  return nullptr;
}


// return next token without advancing
// return nullptr if eof
Token const*
Token_stream::next()
{
  if(eof())
    return nullptr;

  return &*begin_;
}

// return next token and advance past it
// returns nullptr if eof
Token const*
Token_stream::advance()
{
  if (eof())
    return nullptr;

  Token const* t = &*begin_;
  begin_++;
  return t;
}


void
install_tokens()
{
  install_symbol(lparen_tok, "("); // (
  install_symbol(rparen_tok, ")"); // )

  // operators
  install_symbol(plus_tok, "+");   // +
  install_symbol(minus_tok, "-");  // -
  install_symbol(star_tok, "*");   // *
  install_symbol(fslash_tok, "/"); // /
  install_symbol(mod_tok, "%");    // %

  // handling error tokens
  install_symbol(error_tok, "1err");
  install_symbol(eof_tok, "2eof");
}


} // namespace math