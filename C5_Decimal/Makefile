CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV_CFLAGS = $(CFLAGS) -fprofile-arcs -ftest-coverage
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LIB_FLAGS = -lcheck
endif
ifeq ($(UNAME_S), Linux)
	LIB_FLAGS = -lcheck -lm -lsubunit -lpthread -lrt
endif

TARGET = s21_decimal.a
SRC = decimal_helpers.c comparison.c arithmetic.c other.c conversion.c
OBJ = $(SRC:.c=.o)

TESTS_RUN = tests_run
TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)
HEADERS = s21_decimal.h test/test_decimal.h

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

%.o: %.c s21_decimal.h
	$(CC) $(CFLAGS) -c $< -o $@

test/%.o: test/%.c s21_decimal.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_RUN): $(TEST_OBJ) $(TARGET)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(TARGET) $(LIB_FLAGS) -o $@
	./$@

test: $(TESTS_RUN)

clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n $(SRC) $(TEST_SRC) $(HEADERS)
	clang-format -i $(SRC) $(TEST_SRC) $(HEADERS)
	rm .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src

gcov_report: $(TEST_OBJ)
	# Компилируем исходники с флагами gcov
	$(CC) $(GCOV_CFLAGS) -c $(SRC)
	ar rcs $(TARGET) *.o
	# Собираем тесты с флагами gcov
	$(CC) $(GCOV_CFLAGS) $(TEST_OBJ) $(TEST_RUN_SRC) $(TARGET) $(LIB_FLAGS) -o test_gcov
	rm *.o
	# Запускаем тесты
	./test_gcov
	# Генерируем .gcov-файлы
	gcov -b -c $(SRC)
	# Создаём директорию для HTML-отчёта
	mkdir -p gcov_report
	# Проверяем, установлен ли lcov
	@if command -v lcov >/dev/null 2>&1 && command -v genhtml >/dev/null 2>&1; then \
		echo "Генерируем HTML-отчёт..."; \
		lcov --capture --directory . --output-file coverage.info; \
		lcov --extract coverage.info '*/src/*' -o coverage.info; \
		genhtml coverage.info --output-directory gcov_report; \
		rm -f *.gcda *.gcno coverage.info; \
		echo "Отчёт gcov в HTML-формате доступен в директории gcov_report/index.html"; \
	else \
		echo "lcov или genhtml не установлены. Файлы .gcov сгенерированы."; \
	fi

clean:
	rm -f $(TARGET) $(TESTS_RUN) *.o test/*.o *.gcov test_gcov
	rm -rf gcov_report

rebuild: clean all

.PHONY: all clean rebuild test