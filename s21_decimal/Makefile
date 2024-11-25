FILES=other.c arifmetics/s21_add.c arifmetics/s21_sub.c arifmetics/s21_mul.c arifmetics/s21_div.c convertors/convertors.c other/s21_floor.c other/s21_negate.c other/s21_round.c other/s21_truncate.c comparison_operators/s21_is_equal.c comparison_operators/s21_is_greater_or_equal.c comparison_operators/s21_is_less_or_equal.c comparison_operators/s21_is_greater.c comparison_operators/s21_is_less.c comparison_operators/s21_is_not_equal.c
FLAGS=-Wall -Werror -Wextra -std=c11 -lm

all: s21_decimal.a test gcov_report

s21_decimal.a:
				gcc $(FLAGS) -c other.c -o other.o
				gcc $(FLAGS) -c arifmetics/s21_add.c -o s21_add.o
				gcc $(FLAGS) -c arifmetics/s21_sub.c -o s21_sub.o
				gcc $(FLAGS) -c arifmetics/s21_mul.c -o s21_mul.o
				gcc $(FLAGS) -c arifmetics/s21_div.c -o s21_div.o
				gcc $(FLAGS) -c convertors/convertors.c -o convertors.o
				gcc $(FLAGS) -c comparison_operators/s21_is_equal.c -o s21_is_equal.o
				gcc $(FLAGS) -c comparison_operators/s21_is_greater_or_equal.c -o s21_is_greater_or_equal.o
				gcc $(FLAGS) -c comparison_operators/s21_is_less_or_equal.c -o s21_is_less_or_equal.o
				gcc $(FLAGS) -c comparison_operators/s21_is_greater.c -o s21_is_greater.o
				gcc $(FLAGS) -c comparison_operators/s21_is_less.c -o s21_is_less.o
				gcc $(FLAGS) -c comparison_operators/s21_is_not_equal.c -o s21_is_not_equal.o
				gcc $(FLAGS) -c other/s21_floor.c -o s21_floor.o
				gcc $(FLAGS) -c other/s21_negate.c -o s21_negate.o
				gcc $(FLAGS) -c other/s21_round.c -o s21_round.o
				gcc $(FLAGS) -c other/s21_truncate.c -o s21_truncate.o
				ar r s21_decimal.a *.o
				rm *.o

test:
				gcc $(FLAGS) unit_tests.c $(FILES) -lcheck -o test.out
				./test.out

gcov_report:
				gcc -fprofile-arcs -ftest-coverage unit_tests.c $(FILES) $(FLAGS) -lcheck -o tests.out
				-./tests.out
				lcov -t "gcov_report" -o tests.info -c -d .
				genhtml -o report tests.info
				rm -f *.gcno *.gch *.info report.out *.gcov
clean_decimal:
				rm *.a
clean_gcov:
				rm *.out
				rm -f *.gcno *.gcda *.info *.gcov
				rm -rf ./report
				clear
clean_test:
				rm test.out
clean: clean_decimal clean_test clean_gcov

clang_n:
				cp ../materials/linters/.clang-format ./
				clang-format -n arifmetics/*.c
				clang-format -n convertors/*.c
				clang-format -n comparison_operators/*.c
				clang-format -n other/*.c
				clang-format -n *.c
				clang-format -n *.h
				rm .clang-format

clang_i:
				cp ../materials/linters/.clang-format ./
				clang-format -i arifmetics/*.c
				clang-format -i convertors/*.c
				clang-format -i comparison_operators/*.c
				clang-format -i other/*.c
				clang-format -i *.c
				clang-format -i *.h
				rm .clang-format