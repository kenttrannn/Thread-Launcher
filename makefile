CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread

thread_launcher: thread_launcher.c

clean:
	rm -f thread_launcher

.PHONY: clean