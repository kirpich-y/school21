CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra
LDFLAGS = -I/usr/local/include -L/usr/local/lib -lgtest -pthread -lgcov -fprofile-arcs -ftest-coverage
SRC = s21_matrix_oop.cpp test.cpp
TARGET = test.out

.PHONY: clean test

all: s21_matrix_oop.a test gcov

s21_matrix_oop.a:
	$(CXX) $(CXXFLAGS) -c s21_matrix_oop.cpp -o s21_matrix_oop.o
	ar r s21_matrix_oop.a s21_matrix_oop.o
	rm s21_matrix_oop.o

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@


clean:
	rm -f $(TARGET) *.gcno *.gcda *.info
	rm -f s21_matrix_oop.o
	rm -rf report
	rm -f s21_matrix_oop.a


test: $(TARGET)
	./$(TARGET)

gcov: test
	./$(TARGET)
	lcov --ignore-errors inconsistent,usage -t "gcov_report" -o tests.info -c -d . \
	--include "*test.cpp" --include "*s21_matrix_oop.cpp"
	genhtml -o report tests.info
	open report/index.html

clang-n:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cpp
	clang-format -n *.h
	rm .clang-format

clang-i:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cpp
	clang-format -i *.h
	rm .clang-format