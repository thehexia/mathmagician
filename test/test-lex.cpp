
#include "../prelude.hpp"
#include "../lexer.hpp"
#include "../file.hpp"
#include "../print.hpp"

#include <iostream>
#include <locale>

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

  print(tokens);
}