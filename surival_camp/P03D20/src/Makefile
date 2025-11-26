CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I include
TARGET = ../build/graph
SRC = ./graph.c ./token.c ./stack.c ./stack_oper.c ./calculation.c ./draw.c
HDR = include/*

all: $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

clean:
	rm -r $(TARGET)

rebuild: clean all