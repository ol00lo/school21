CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

TARGET = cipher
SRCS = cipher.c
BUILD_DIR = ../build/
QUEST1 = $(BUILD_DIR)/$(TARGET)

$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(BUILD_DIR)$@

all: $(TARGET)

clean:
	rm $(QUEST1)

rebuild: clean all
