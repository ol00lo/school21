CC = gcc
CFLAGS = -std=c11 -D_GNU_SOURCE -Wall -Werror -Wextra
TARGET = s21_grep
SOURCES = main_grep.c grep.c flags.c

all: build

build: $(TARGET)

rebuild: clean build

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

test: $(TARGET)
	./tests.sh

leaks: $(TARGET)
	CK_FORK=no leaks --atExit -- ./$(TARGET)

clean:
	rm -f $(TARGET) *.o *.out

.PHONY: all build rebuild clean cppcheck leaks test