#include "prelude.hpp"
#include "lexer.hpp"
#include "parse.hpp"
#include "file.hpp"
#include "evaluate-expr.hpp"
#include "print.hpp"

#include <iostream>
#include <cmath>

using namespace math;


std::istream&
input(String& in)
{
  std::cout << "? ";
  return getline(std::cin, in);
}


int main(int argc, char* argv[])
{
  install_tokens();

  String line;

  while(input(line)) {
    if (line.empty())
      // ignore and move on
      continue;

    Char_stream stream(line);
    Token_list tokens = lex(stream);
    Token_stream ts(tokens);

    Parser p;
    Expr* e = parse(p, ts);

    if(e) {
      // evaluate
      Value res = evaluate(e);
      std::cout << res << '\n';
    }
  } 
}