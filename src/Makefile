CC				= gcc -std=c11

C_FILES			= Converter.c
TEST_C_FILES	= Converter_test.c
GUI_C_FILES		= Converter_gui.c

C_FLAGS			= -c -Wall -Wextra 
#-Werror
TEST_C_FLAGS	= -c `pkg-config --cflags check`
GUI_C_FLAGS		= -c -pthread `pkg-config --cflags gtk+-3.0 cairo`

LIB_FLAGS		= -L. -lConverter -L.
GUI_LIB_FLAGS	= `pkg-config --libs gtk+-3.0` 
TEST_LIB_FLAGS	= `pkg-config --libs check`

OUTPUT			= Converter
DEBUG_OUTPUT	= Converter_Debug
TEST_OUTPUT		= Converter_Tests

all: Converter

Converter: libConverter.a
	$(CC) $(C_FLAGS) $(GUI_C_FLAGS) $(GUI_C_FILES)
	$(CC) libConverter.a *.o -o $(OUTPUT) $(LIB_FLAGS) $(GUI_LIB_FLAGS)
	make clean

libConverter.a:
	$(CC) $(C_FLAGS) $(C_FILES)
	ar rcs libConverter.a *.o
	make clean

test: libConverter.a
	$(CC) $(C_FLAGS) $(TEST_C_FLAGS) $(TEST_C_FILES)
	$(CC) libConverter.a *test.o -o $(TEST_OUTPUT) $(LIB_FLAGS) $(TEST_LIB_FLAGS)
	./$(TEST_OUTPUT)
	make clean

gcov_report:
	$(CC) $(C_FLAGS) $(TEST_C_FLAGS) -fprofile-arcs -ftest-coverage $(C_FILES) $(TEST_C_FILES)
	$(CC) *.o -o $(TEST_OUTPUT) --coverage $(TEST_LIB_FLAGS)
	./$(TEST_OUTPUT)
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	make clean

debug:
	$(CC) -g $(C_FLAGS) $(C_FILES) Converter_debug.c
	$(CC) -g *.o -o $(DEBUG_OUTPUT)
	make clean

clean:
	rm -f *.o *.gcno *.gcda *.info

clean_full: clean
	rm -f $(OUTPUT) $(DEBUG_OUTPUT) $(TEST_OUTPUT) libConverter.a
	rm -rf ./report/