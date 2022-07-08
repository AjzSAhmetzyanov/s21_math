CC=gcc
CFLAGS= -std=c11 -Wall -Werror -Wextra
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lgcov --coverage
CHECKFLAGS=$(shell pkg-config --libs check)
SRC=s21_math.c
OBJ=s21_math.o
LIB=s21_math.a
OBJ_TARG=s21_math_test
TARGET=/

.PHONY: help all clean test s21_math.a gcov_report

help:
	@echo "Available targets:"
	@echo "  make test"
	@echo "  make s21_math.a"
	@echo "  make gcov_report"

clean:
	rm -rf s21_math_test test *.gch *.gcda *.gcno *.a *.o *.json coverage.* *.info ./report/ ./s21_math_test.dSYM/
all:	build

build: s21_math.a test
	
rebuild: clean build

s21_math.a: s21_math.c s21_math.h
	$(CC) $(CFLAGS) -c s21_math.c -o s21_math.o
	ar -rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a

s21_math_test.o:	s21_math_test.check
	checkmk ./s21_math_test.check >s21_math_test.c
	$(CC) $(CFLAGS) -c s21_math_test.c -o s21_math_test.o

test:	clean s21_math_test.o s21_math.a
	$(CC) $(CFLAGS) -o s21_math_test s21_math_test.o -L. -ls21_math $(CHECKFLAGS)
	./s21_math_test

gcov_lib:	s21_math.c s21_math.h
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LFLAGS) -c $(SRC)
	ar -rc libs21_math.a $(OBJ)
	ranlib libs21_math.a

gcov_test:	s21_math_test.check gcov_lib
	checkmk ./s21_math_test.check >s21_math_test.c
	$(CC) $(CFLAGS) -c s21_math_test.c -o s21_math_test.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LFLAGS) s21_math_test.o -L./ -ls21_math $(CHECKFLAGS) -o s21_math_test


gcov_report:	clean gcov_lib gcov_test
	./s21_math_test
	lcov -t "s21_math_test" -o s21_math_test.info -c -d .
	genhtml -o report s21_math_test.info
