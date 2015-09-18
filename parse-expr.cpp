
#include "prelude.hpp"
#include "token.hpp"
#include "parse-expr.hpp"
#include "print.hpp"

#include <cassert>

namespace math
{

namespace
{
// keeping track of bogus parens
bool in_paren_enclosed = false;

}

bool
is_binary_op(Token_kind k)
{
  switch (k) {
    case star_tok: 
    case fslash_tok:
    case mod_tok:
    case plus_tok:
    case minus_tok:
      return true;
    default:
      return false;
  }

  return false;
}


bool
is_additive_op(Token_kind k)
{
  switch (k) {
    case plus_tok:
    case minus_tok:
      return true;
    default:
      return false;
  }

  return false;
}


bool
is_mult_op(Token_kind k)
{
  switch (k) {
    case star_tok: 
    case fslash_tok:
    case mod_tok:
      return true;
    default:
      return false;
  }

  return false;
}


Expr*
parse_integer(Parser& p, Token_stream& ts)
{
  if (Token const* tok = ts.expect(number_tok)) {
    if(ts.next())
      if(ts.next()->kind() == rparen_tok && !in_paren_enclosed) {
        error("Unexpected token ')'");
        return nullptr;
      }
    return p.on_number(tok);
  }

  return nullptr;
}


Expr*
parse_paren_enclosed(Parser& p, Token_stream& ts)
{
  if (ts.expect(lparen_tok)) {
    in_paren_enclosed = true;
    if (Expr* e = parse_expr(p, ts)) {
      if (ts.expect(rparen_tok)) {
        in_paren_enclosed = false;
        return e;
      }
      // expected r paren fail
      else {
        error("Expected ')' after ");
        print(e);
      }
    }
    // no expression after (
    else {
      error("Expected expression after '('");
    }
  }

  return nullptr;
}


// term ::= digit 
//          ( expr )
Expr*
parse_term(Parser& p, Token_stream& ts)
{
  if (ts.next()) {
    switch (ts.next()->kind()) {
      case number_tok: return parse_integer(p, ts);
      case lparen_tok: return parse_paren_enclosed(p, ts);
      default:
        return nullptr;
    }
  }

  return nullptr;
}


// multi ::=  term '*' term
//            term '/' term
//            term '%' term
//
// assuming the first term has already been parsed
Expr*
parse_mult_expr(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  // look for the next operand
  if (Expr* e2 = parse_term(p, ts)) {
    // if there is another operator after the term
    // and it is a multiplicative operator
    // then consume it.
    // the arithmetic expr so far becomes the lhs operand
    // and we recurse until there are no more multiplicative operators.
    if (Token const* t = ts.next()) {
      if (is_mult_op(t->kind()))
        return parse_mult_expr(p, ts, ts.advance(), p.on_arithmetic(tok, e1, e2));
      // return once we're done eating up multiplicative operators
      else
        return p.on_arithmetic(tok, e1, e2);
    }
    else
      return p.on_arithmetic(tok, e1, e2);
  }

  error("Expected expression after: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// factor ::= factor '*' term
//            factor '/' term
//            factor '%' term
//            term
Expr*
parse_factor(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_term(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        case star_tok: return parse_mult_expr(p, ts, ts.expect(star_tok), e1);
        case fslash_tok: return parse_mult_expr(p, ts, ts.expect(fslash_tok), e1);
        case mod_tok: return parse_mult_expr(p, ts, ts.expect(mod_tok), e1);
        // anything else and we consider e1 a lone term
        default:
          return e1;
      }
    }
    // if it is only the term
    else
      return e1;
  }

  return nullptr;
}


// add-expr ::= factor '+' factor
//              factor '-' factor
// assuming the first expr has already been parsed
Expr*
parse_additive_expr(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  if (Expr const* e2 = parse_factor(p, ts)) {
    if (Token const* t = ts.next()) {
      if (is_additive_op(t->kind()))
        return parse_additive_expr(p, ts, ts.advance(), p.on_arithmetic(tok, e1, e2));
      else
        return p.on_arithmetic(tok, e1, e2);
    }
    else
      return p.on_arithmetic(tok, e1, e2);
  }


  error("Expected expression after: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// expr ::= expr '+' factor
//          expr '-' factor
//          factor
Expr*
parse_expr(Parser& p, Token_stream& ts)
{
  // parse primary expressions
  if (Expr* e1 = parse_factor(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the next expr
        case plus_tok: 
        case minus_tok: 
          return parse_additive_expr(p, ts, ts.advance(), e1);
        default:
          return e1;
      }
    }
    // no operator or rhs means end of expr
    else
      return e1;
  }

  return nullptr;
}


} // namespace math