cmake_minimum_required(VERSION 2.8.12)

project(mathmagician CXX)

# C++ build flags.
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_library(math STATIC
	expr.cpp
	evaluate-expr.cpp
	token.cpp
	symbol.cpp
	lexer.cpp
	parse.cpp
	parse-expr.cpp
	file.cpp
	print.cpp)

add_subdirectory(test)

add_executable(calc calc.cpp)
target_link_libraries(calc math)