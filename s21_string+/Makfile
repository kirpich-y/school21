CFLAGS = -Wall -Wextra -Werror -c
SOURCES = s21_string.c io/s21_sprintf.c

all: s21_string.a gcov_report test

gcov_report:
	gcc -fprofile-arcs -ftest-coverage functions_tests.c s21_string.a -lm -o tests.out -lcheck
	-./tests.out
	lcov -t "gcov_report" -o tests.info -c -d .
	genhtml -o report tests.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html
	
clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
	
test: clean s21_string.a
	gcc functions_tests.c s21_string.a -o tests.out -lcheck
	-./tests.out
	
s21_string.a:
	gcc $(CFLAGS) $(SOURCES)
	ar r s21_string.a *.o
	rm *.o

check:
	clang-format -style=Google -n *.c
