= Calc 2 =

Supports boolean logical operators (&& and ||), equality operators (== and !=), relational operators (<, <=, >, >=),
and unary operators (!, -, +) to the language.

Calc 2 supports 2 types (bool and double). Double is supported over int because it is simply more typical of
calculators to produce floating point results in all operations. Type conversions on int to double does not currently
happen and the assumption is that operations on any number results in a value of type double.

Type checking is done on all expressions:

1. Operands of logical operators are required to have bool type and the evaluation is required to have bool type.
2. Operands of equality operators can have either bool type or double type but both operands must have the same type.
The evaluation is required to have bool type.
3. Operands of relation operators are required to have double type. The evaluation is required to have bool type.
4. Unary operator + and - are required to have operands of double type. The evaluation is required to have double type.
5. Unary operator ! is required to have an operand of type bool The evaluation is required to have bool type.
6. Binary operator % is required to have operands whose values are integers.

== Building ==

Building can be done via cmake. ./calc will run the calculator in user input mode.

== Testing ==

A testing script is included with the repository. Call ./test-eval to run provided test cases.

./test-eval
- evaluates all test cases

./test-eval bool
- evaluate only boolean test cases

./test-eval cmp
- evaluates equality and ordering operators

./test-eval case
- evaluates integer binary operators

./test-eval neg
- evaluates test cases using unary operator + and -

./test-eval err
- evaluates a suite of error cases regarding arithmetic operators

./test-eval type_err
- evaluates a suite of type error cases
