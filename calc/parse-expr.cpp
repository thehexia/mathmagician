
#include "prelude.hpp"
#include "token.hpp"
#include "parse-expr.hpp"
#include "print.hpp"

#include <cassert>

namespace math
{

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

// '+', '-'
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


// '*', '/', '%'
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


// '(', ')'
bool
is_paren(Token_kind k)
{
  switch(k) {
    case lparen_tok:
    case rparen_tok:
      return true;
    default:
      return false;
  }

  return false;
}


// Parse an integer/decimal number
Expr*
parse_number(Parser& p, Token_stream& ts)
{
  if (Token const* tok = ts.expect(number_tok)) {
    return p.on_number(tok);
  }

  return nullptr;
}


// Parse paren enclosed expressions
// error if no matching beginning and ending paren
Expr*
parse_paren_enclosed(Parser& p, Token_stream& ts)
{
  if (ts.expect(lparen_tok)) {
    // in_paren_enclosed = true;
    if (Expr* e = parse_expr(p, ts)) {
      if (ts.expect(rparen_tok)) {
        // in_paren_enclosed = false;
        return e;
      }
      // expected r paren fail
      else {
        error("Expected ')' after ");
        print(e);
        print("\n");
        return nullptr;
      }
    }
    // no expression after (
    else {
      error("Expected expression after '('");
    }
  }

  return nullptr;
}


// neg      ::= - term
Expr*
parse_neg(Parser& p, Token_stream& ts)
{
  // eat the minus tok
  assert(ts.advance()->kind() == minus_tok);
  if (Expr* e = parse_term(p, ts))
    return p.on_unary(e);

  error("Expected term after '-'.");
  return nullptr;
}


// term ::= number
//          ( expr )
//          neg
Expr*
parse_term(Parser& p, Token_stream& ts)
{
  if (ts.next()) {
    switch (ts.next()->kind()) {
      case number_tok: return parse_number(p, ts);
      case lparen_tok: return parse_paren_enclosed(p, ts);
      // negative number
      case minus_tok: return parse_neg(p, ts);
      default:
        print("Unable to parse term beginning with: ");
        print(ts.next());
        print("\n");
        return nullptr;
    }
  }

  return nullptr;
}


// multi-rest ::=  '*' term (multi-rest)
//                 '/' term (multi-rest)
//                 '%' term (multi-rest)
//
// assuming the first term and operator has already been parsed
// this parses the 'rest' of the expression
Expr*
parse_mult_expr(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  // look for the next operand
  if (Expr* e2 = parse_term(p, ts)) {
    // if there is another operator after the term
    // and it is a multiplicative operator
    // then consume it.
    // the expr so far becomes the lhs operand
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

  error("Expected expression after multiplicative expr: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// factor ::= factor '*' term
//            factor '/' term
//            factor '%' term
//            term
//
// or
// factor ::= term (multi-rest)
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


// add-rest ::= '+' factor (add-rest)
//              '-' factor (add-rest)
//
// assuming the first factor has already been parsed
// we start to parse the 'rest' of the expression
Expr*
parse_additive_expr(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  if (Expr const* e2 = parse_factor(p, ts)) {
    if (Token const* t = ts.next()) {
      // keep parsing the 'rest' while we still have a valid operator
      if (is_additive_op(t->kind()))
        return parse_additive_expr(p, ts, ts.advance(), p.on_arithmetic(tok, e1, e2));
      else
        return p.on_arithmetic(tok, e1, e2);
    }
    else
      return p.on_arithmetic(tok, e1, e2);
  }


  error("Expected expression after additive expr: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// expr ::= expr '+' factor
//          expr '-' factor
//          factor
//
// or
// expr ::= factor (add-rest)
Expr*
parse_expr(Parser& p, Token_stream& ts)
{
  // parse primary expressions
  if (Expr* e1 = parse_factor(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
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