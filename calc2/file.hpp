#ifndef MATH_FILE_HPP
#define MATH_FILE_HPP

#include "prelude.hpp"

#include <string>
#include <cstring>


namespace math
{

// Character stream provides interface for
// easily traversing a std::string
struct Char_stream
{
  using Str_it = std::string::iterator;

  Char_stream(String& s)
    : stream_(s), begin_(s.begin()), end_(s.end())
  { }

  char const& peek() const;
  char const& get();
  char const* peek_n(int n) const;

  bool eof() const { return begin_ == end_; }

  Str_it& current() { return begin_; } 

  // location of the current character in the stream
  int location() { return begin_ - stream_.begin(); }

  String stream_;

  Str_it begin_;
  Str_it end_;
};

// Takes a filename and reads file into a string
String read_file(String const&);

}

#endif

