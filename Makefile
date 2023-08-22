CC=gcc
WAY=./unit_test/
OS=$(shell uname)
WILD=$(wildcard *.cc)
WILD_SORT=$(shell find . -name "*.cc" ! -name "*test*")
FLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17
GTEST_FLAGS=-lgtest -lgtest_main -pthread
ifeq ($(OS), Linux)
  FLAGS_LCHECK = -lcheck -pthread -lsubunit -lrt -lm
  OPEN=xdg-open
else
  FLAGS_LCHECK = -lcheck
  OPEN=open
endif
FLAGS_GCOV = -coverage -fprofile-arcs -ftest-coverage
FILE_TEST = s21_math_test

all: clean test

.PHONY: test
test: s21_matrix_oop.a
	$(CC) -o test $(WILD) $(FLAGS) $(GTEST_FLAGS)

.PHONY: gcov_report
gcov_report: s21_matrix_oop.a
		$(CC) $(FLAGS) $(WILD) \
		$(FLAGS_LCHECK) $(GTEST_FLAGS) $(FLAGS_GCOV) \
		$(WILD_REPORT) -o info
	./info
	lcov -t "info" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	$(OPEN) report/index.html

s21_matrix_oop.a:
	$(CC) -c -std=c++17 $(WILD_SORT)
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ *.cpp *.h

style:
	clang-format -i *.cpp
	clang-format -i *.h

clean_no_all:
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info

clean:
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info
	rm -f *.a
	rm -f *.out
	rm -rf report
	rm -f test

.PHONY: git
git: style
	rm -rf report
	git add .
	git commit -m "commit"
	git push

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test