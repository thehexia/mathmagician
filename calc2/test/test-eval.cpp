#include "../prelude.hpp"
#include "../lexer.hpp"
#include "../parse.hpp"
#include "../file.hpp"
#include "../evaluate-expr.hpp"
#include "../print.hpp"

#include <iostream>

using namespace math;

int main(int argc, char* argv[])
{
  install_tokens();

  if (argc < 2) {
    std::cout << "invalid arguments\n";
    return -1;
  }

  String file = read_file(String(argv[1]));

  Char_stream stream(file);
  Token_list tokens = lex(stream);
  Token_stream ts(tokens);;

  Parser p;

  std::cout << "Parsed: \n";
  Expr* e = parse(p, ts);
  print(e);
  print("\n");

  if(e)
    // evaluate
    std::cout << "Result: " << evaluate(e) << '\n';
}