CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOV=--coverage

TESTFILE = s21_test
SRC = ./Controller/*.cc ./Model/*.cc ./View/*.cc main.cc

ifeq ($(shell uname), Linux)
	LIBS_FOR_CHECK=-lcheck -lsubunit -lrt -lpthread -lm
else
	LIBS_FOR_CHECK=-lcheck
endif

RDIR = ./release
APP = $(RDIR)/SmartCalc

all: clean install

install: uninstall
	mkdir $(RDIR)
	cd $(RDIR); qmake ../SmartCalc.pro
	cd $(RDIR); make
	cd $(RDIR); make clean
	$(APP)


uninstall:
	rm -rf $(RDIR)

clean: uninstall
	rm -f *.a *.o *.so *.out *.info *.gcno *.gcda main $(TESTFILE)
	rm -rf report manual
	rm -rf *.tgz

dvi:
	open ./documentation/dvi.html

dist:
	tar -czf $(RDIR)/SmartCalc.tgz $(APP)

tests: clean
	$(CXX) $(CXXFLAGS) $(GCOV) -c ./Model/*.cc
	$(CXX) $(CXXFLAGS) -c ./Tests/*.cc -lgtest
	$(CXX) $(CXXFLAGS) $(GCOV) -o $(TESTFILE) smartcalc_model.o rpn_conversion.o s21_tests.o -lgtest
	./$(TESTFILE)

gcov_report: tests
	lcov -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info
	open ./report/index.html

leaks: tests
ifeq ($(shell uname), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=no ./$(TESTFILE)
else
	CK_FORK=no leaks --atExit -- ./$(TESTFILE)
endif

style-check:
	clang-format -n -style=google Model/*.cc Model/*.h main.cc
	clang-format -n -style=google View/*.cc View/*.h
	clang-format -n -style=google Controller/*.cc Controller/*.h

style-set:
	clang-format -i -style=google Model/*.cc Model/*.h 
	clang-format -i -style=google View/*.cc View/*.h
	clang-format -i -style=google Controller/*.cc Controller/*.h
