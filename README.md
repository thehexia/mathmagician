=== The Mathmagician Calculator ===

The mathmagician calculator can evaluate expressions and can translate it into sexpr and postfix notations.
The calculator supports integers, doubles, negative numbers, unary negation, addition, subtraction, multiplication, division, modulus, and arbitrary parenthetization. Any invalid syntax will produce errors.

Directory `calc` contains all of the source code for the calculator.

Directory `calc/cases` contains 37 test cases.

Directory `calc/test` contains a set of test drivers.

4 bash scripts come with the project for testing. (Project has to be built before these actually work)

1. `test-eval.sh` will read all files from `calc/cases`, run them through the evaluator, and output results.
2. `test-sexpr.sh` will read all files from `calc/cases`, run them through the sexpr translator, and output results.
3. `test-postfix.sh` will read all files from `calc/cases`, run them through the postfix translator, and output results.
4. `test-parse.sh` will parse all files from `calc/cases`, run them through the parser, and output parse results with appropriate grouping.

==== Building ===
`cd calc`
`mkdir build`
`cd build`
`cmake ..`
`make`

After this 3 executables should be made and a bunch of test drivers will be made in `build/test`.

`./calc` will run the regular calculator with command line prompts and evaluate the input.
`./calc2post` will run the translation from user input of left infix notation to postfix notation.
`./calc2sexpr` will run the translation from user input of left infix notation to sexpr notation.

Test executables can be run using

`./test-eval <filename>`

`./test-sexpr <filename>`

`./test-postfix <filename>`

These are called by the bash scripts in the /calc directory.

