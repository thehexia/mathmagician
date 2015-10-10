#include "file.hpp"

#include <fstream>
#include <cassert>

namespace math
{

// look at the next character in the string
char const& 
Char_stream::peek() const 
{ 
  assert(!eof());
  return *begin_; 
}


// get the next character in the string and advance
// one character
char const& 
Char_stream::get() 
{ 
  assert(!eof());
  char const& c = *begin_;
  begin_++;
  return c;
}


char const*
Char_stream::peek_n(int n) const
{
  if (begin_ + n != end_);
    return &*(begin_ + n);

  return nullptr;
}


// Return a string containing the text of the file.
// Straight stolen from lingo
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