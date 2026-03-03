CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV_CFLAGS = $(CFLAGS) -fprofile-arcs -ftest-coverage
TARGET = s21_string.a
SRC = s21_string.c s21_sscanf.c s21_sprintf.c
OBJ = $(SRC:.c=.o)
TEST = test
TEST_SRC = tests_run.c tests/*.c
TEST_OBJ = $(TEST_SRC:.c=.o)
HEADERS = *.h

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n $(SRC) $(TEST_SRC)
	clang-format -i $(SRC) $(TEST_SRC)
	rm .clang-format

clean:
	rm -rf $(TARGET) $(TEST) *.o *.gch *.gcda *.gcno *.gcov test_gcov ./gcov_report

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src

$(TEST): $(TEST_SRC) $(TARGET)
	$(CC) $(CFLAGS) $^ -lcheck -lm -o $@
	./$@

rebuild: clean all

gcov_report:
	# Компилируем исходники с флагами gcov
	$(CC) $(GCOV_CFLAGS) -c $(SRC)
	ar rcs $(TARGET) *.o
	# Собираем тесты с флагами gcov
	$(CC) $(GCOV_CFLAGS) $(TEST_SRC) $(TARGET) -lcheck -o test_gcov
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
		genhtml coverage.info --output-directory gcov_report; \
		rm -f *.gcda *.gcno coverage.info; \
		echo "Отчёт gcov в HTML-формате доступен в директории gcov_report/index.html"; \
	else \
		echo "lcov или genhtml не установлены. Файлы .gcov сгенерированы."; \
	fi

.PHONY: all clean rebuild clang gcov_report