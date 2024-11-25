CC = gcc -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
HEADERS = s21_matrix.h
SOURCES = $(wildcard *.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
endif

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

all: gcov_report

s21_matrix.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_matrix.a $(OBJ_LIBRARY)
	ranlib s21_matrix.a
	rm -rf *.o 

test: s21_matrix.a test/s21_matrix_tests.c
ifeq ($(OS), Darwin)
	$(CC) test/s21_matrix_tests.c s21_matrix.a -o test.out $(LIBS)
else
	$(CC) test/s21_matrix_tests.c s21_matrix.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out

gcov_report: s21_matrix.a test/s21_matrix_tests.c
ifeq ($(OS), Darwin)
	gcc $(GCOVFLAGS) test/s21_matrix_tests.c $(SOURCES) -o report.out $(LIBS)
else
	gcc $(GCOVFLAGS) test/s21_matrix_tests.c $(SOURCES) -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o report/ Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

rebuild: clean all

clean:
	rm -rf *.o ./report *.dSYM *.a *.out *.gcov *.info *.gcda *.gcno

check_style:
	clang-format -i --style=Google test/*.c *.h *.c
	clang-format -n --style=Google test/*.c *.h *.c

check_valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test.out
