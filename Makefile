

lib = ./src/matrix/matrix.c ./src/output/output.c 

tests = ./tests/tests_main.c ./tests/tests_matrix.c ./tests/tests_output.c


program = ./src/main.c

make:
	gcc $(program) $(lib) -o ./build/main.o

clean:
	rm ./build/main.o && rm ./build/tests.o

tests: make
	gcc  ./tests/test_runner.c $(tests) $(lib) -o ./build/tests.o -lcunit


