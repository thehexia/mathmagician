
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


// Parse true/false
Expr*
parse_bool(Parser& p, Token_stream& ts)
{
  if (Token const* tok = ts.expect(bool_tok)) {
    return p.on_bool(tok);
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


// primary_expr ::= number
//                  bool
//                  ( expr )
//          
Expr*
parse_primary_expr(Parser& p, Token_stream& ts)
{
  if (ts.next()) {
    switch (ts.next()->kind()) {
      case number_tok: return parse_number(p, ts);
      case lparen_tok: return parse_paren_enclosed(p, ts);
      case bool_tok: return parse_bool(p, ts);
      // // negative number
      // case minus_tok: return parse_neg(p, ts);
      default:
        print("Unable to parse primary expr beginning with: ");
        print(ts.next());
        print("\n");
        return nullptr;
    }
  }

  return nullptr;
}


// neg      ::= - unary expr
Expr*
parse_neg(Parser& p, Token_stream& ts)
{
  // eat the minus tok
  assert(ts.advance()->kind() == minus_tok);
  if (Expr* e = parse_unary_expr(p, ts))
    return p.on_unary(e);

  error("Expected primary expr after '-'.");
  return nullptr;
}


// pos ::= + unary expr
Expr*
parse_pos(Parser& p, Token_stream& ts)
{
  // eat the minus tok
  assert(ts.advance()->kind() == plus_tok);
  if (Expr* e = parse_primary_expr(p, ts))
    return p.on_unary(e);

  error("Expected primary expr after '+'.");
  return nullptr;
}


// pos ::= ! unary expr
Expr*
parse_not(Parser& p, Token_stream& ts)
{
  // eat the minus tok
  assert(ts.advance()->kind() == bang_tok);
  if (Expr* e = parse_primary_expr(p, ts))
    return p.on_unary(e);

  error("Expected primary expr after '!'.");
  return nullptr;
}



// unary-expr ::= - unary expr
//                + unary expr
//                ! unary expr
//                primary expr
Expr*
parse_unary_expr(Parser& p, Token_stream& ts)
{
  if(ts.next()) {
    switch (ts.next()->kind()) {
      // negative
      case minus_tok: return parse_neg(p, ts);
      case plus_tok: return parse_pos(p, ts);
      case bang_tok: return parse_not(p, ts);
      default:
        return parse_primary_expr(p, ts);
    }
  }

  return nullptr;
}


// multi-rest ::=  '*' primary expr (multi-rest)
//                 '/' primary expr (multi-rest)
//                 '%' primary expr (multi-rest)
//
// assuming the first primary expr and operator has already been parsed
// this parses the 'rest' of the expression
Expr*
parse_mult_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  // look for the next operand
  if (Expr* e2 = parse_unary_expr(p, ts)) {
    // if there is another operator after the primary expr
    // and it is a multiplicative operator
    // then consume it.
    // the expr so far becomes the lhs operand
    // and we recurse until there are no more multiplicative operators.
    if (Token const* t = ts.next()) {
      if (is_mult_op(t->kind()))
        return parse_mult_rest(p, ts, ts.advance(), p.on_binary(tok, e1, e2));
      // return once we're done eating up multiplicative operators
      else
        return p.on_binary(tok, e1, e2);
    }
    else
      return p.on_binary(tok, e1, e2);
  }

  error("Expected expression after multiplicative expr: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// factor ::= factor '*' primary expr
//            factor '/' primary expr
//            factor '%' primary expr
//            primary expr
//
// or
// factor ::= primary expr (multi-rest)
Expr*
parse_mult_expr(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_unary_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        case star_tok: return parse_mult_rest(p, ts, ts.expect(star_tok), e1);
        case fslash_tok: return parse_mult_rest(p, ts, ts.expect(fslash_tok), e1);
        case mod_tok: return parse_mult_rest(p, ts, ts.expect(mod_tok), e1);
        // anything else and we consider e1 a lone primary expr
        default:
          return e1;
      }
    }
    // if it is only the primary expr
    else
      return e1;
  }

  return nullptr;
}


// add-rest ::= '+' mult_expr (add-rest)
//              '-' mult_expr (add-rest)
//
// assuming the first mult_expr has already been parsed
// we start to parse the 'rest' of the expression
Expr*
parse_add_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  if (Expr const* e2 = parse_mult_expr(p, ts)) {
    if (Token const* t = ts.next()) {
      // keep parsing the 'rest' while we still have a valid operator
      if (is_additive_op(t->kind()))
        return parse_add_rest(p, ts, ts.advance(), p.on_binary(tok, e1, e2));
      else
        return p.on_binary(tok, e1, e2);
    }
    else
      return p.on_binary(tok, e1, e2);
  }


  error("Expected expression after additive expr: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// expr ::= expr '+' multiplicative expr
//          expr '-' multiplicative expr
//          multiplicative expr
//
// or
// expr ::= multi_expr (add-rest)
Expr*
parse_add_expr(Parser& p, Token_stream& ts)
{
  // parse primary expressions
  if (Expr* e1 = parse_mult_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
        case plus_tok: 
        case minus_tok: 
          return parse_add_rest(p, ts, ts.advance(), e1);
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


Expr*
parse_order_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  return nullptr;
}


// order_expr < | <= | > | >= add_expr
// add_expr
//
// add_expr (order_rest)
Expr*
parse_order_expr(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_add_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
        case less_tok: 
        case less_eq_tok:
        case great_tok:
        case great_eq_tok:
          return parse_order_rest(p, ts, ts.advance(), e1);
        default:
          return e1;
      }
    }

    return e1;
  }

  return nullptr;
}


Expr*
parse_eq_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  return nullptr;
}


// eq_expr == | != order_expr
// order_expr
//
// order_expr (eq_rest)
Expr*
parse_eq_expr(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_order_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
        case eq_eq_tok:
        case bang_eq_tok:
          return parse_eq_rest(p, ts, ts.advance(), e1);
        default:
          return e1;
      }
    }

    return e1;
  }

  return nullptr;
}


Expr*
parse_log_and_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  return nullptr;
}


// log_and_expr && order_expr
// order_expr
//
// order_expr (log_and_expr)
Expr*
parse_log_and_expr(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_eq_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
        case log_and_tok: 
          return parse_log_and_rest(p, ts, ts.advance(), e1);
        default:
          return e1;
      }
    }

    return e1;
  }

  return nullptr;
}


Expr*
parse_log_or_rest(Parser& p, Token_stream& ts, Token const* tok, Expr* e1)
{
  if (Expr const* e2 = parse_log_and_expr(p, ts)) {
    if (Token const* t = ts.next()) {
      // keep parsing the 'rest' while we still have a valid operator
      if (t->kind() == log_or_tok)
        return parse_log_or_rest(p, ts, ts.advance(), p.on_binary(tok, e1, e2));
      else
        return p.on_binary(tok, e1, e2);
    }
    
    return p.on_binary(tok, e1, e2);
  }


  error("Expected expression after logical-or expr: ");
  print(e1);
  print(tok);
  print("\n");
  return nullptr;
}


// log_or_expr || log_and_expr
// log_and_expr
//
// log_and_expr (log_or_rest)
Expr*
parse_log_or_expr(Parser& p, Token_stream& ts)
{
  if (Expr* e1 = parse_log_and_expr(p, ts)) {
    if (Token const* tok = ts.next()) {
      switch (tok->kind()) {
        // advance past the operator and move to parse the 'rest' of the expr
        case log_or_tok: 
          return parse_log_or_rest(p, ts, ts.advance(), e1);
        default:
          return e1;
      }
    }

    return e1;
  }

  return nullptr;
}


Expr*
parse_expr(Parser& p, Token_stream& ts)
{
  return parse_log_or_expr(p, ts);
}


} // namespace math