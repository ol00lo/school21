CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

BINDIR = ../../build

TARGET = $(BINDIR)/Quest_3

SRCS = main_executable_module.c \
       ../data_libs/data_io.c \
       ../data_module/data_process.c \
       ../yet_another_decision_module/decision.c \
	   ../data_libs/data_stat.c \
	   data_change.c

OBJS = $(SRCS:.c=.o)

all: $(BINDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
