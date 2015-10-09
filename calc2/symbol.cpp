#include "symbol.hpp"

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
  return table.find(s);
}


} // namespace math