#include "symbol.hpp"
#include <stdexcept>

namespace math
{

Symbol_table::~Symbol_table()
{
  for (auto pair : map)
    delete pair.second;
}

namespace
{

Symbol_table table;

}


void
install_symbol(Token_kind k, String s)
{
  Symbol* sym = new Symbol(k, s);
  table.insert(s, sym);
}


Symbol const* 
get_symbol(String const s)
{
  auto search = table.find(s);

  if (search) {
    return search;
  }
  
  return nullptr;
}


} // namespace math