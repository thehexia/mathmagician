#include "file.hpp"

#include <fstream>
#include <cassert>

namespace math
{

char const& 
Char_stream::peek() const 
{ 
  assert(!eof());
  return *begin_; 
}


char const& 
Char_stream::get() 
{ 
  assert(!eof());
  char const& c = *begin_;
  begin_++;
  return c;
}


// Return a string containing the text of the file.
String
read_file(String const& p)
{
  std::ifstream f(p);

  String text;
  f.seekg(0, std::ios::end);   
  text.reserve(f.tellg());
  f.seekg(0, std::ios::beg);

  std::istreambuf_iterator<char> first = f;
  std::istreambuf_iterator<char> last;
  text.assign(first, last);
  
  return text;
}

}