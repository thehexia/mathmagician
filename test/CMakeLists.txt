macro(add_test_driver target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} math)
endmacro()


add_test_driver(test-lex test-lex.cpp)
add_test_driver(test-parse test-parse.cpp)
add_test_driver(test-print test-print.cpp)
add_test_driver(test-eval test-eval.cpp)
add_test_driver(test-sexpr test-sexpr.cpp)
add_test_driver(test-postfix test-postfix.cpp)

add_test(test-lex test-lex)
add_test(test-parse test-parse)
add_test(test-print test-print)
add_test(test-eval test-eval)
add_test(test-sexpr test-sexpr)
add_test(test-postfix test-postfix)