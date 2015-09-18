cmake_minimum_required(VERSION 2.8.12)

project(mathmagician CXX)

# C++ build flags.
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_library(calc STATIC
	expr.cpp
	evaluate-expr.cpp
	token.cpp
	lexer.cpp
	parse.cpp
	parse-expr.cpp
	file.cpp
	print.cpp
	sexpr.cpp
	postfix.cpp)

add_subdirectory(test)
