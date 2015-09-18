#include "../prelude.hpp"
#include "../lexer.hpp"
#include "../parse.hpp"
#include "../file.hpp"
#include "../print.hpp"

#include <iostream>

using namespace math;

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "invalid arguments\n";
    return -1;
  }

  String file = read_file(String(argv[1]));

  Char_stream stream(file);
  Token_list tokens = lex(stream);
  Token_stream ts(tokens);;

  Parser p;
  Expr* e = parse(p, ts);
  print(e);
  print("\n");
}