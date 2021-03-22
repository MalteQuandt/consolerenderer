CC = gcc # the compiler that we use
LINKERFLAGS = -lm # right now only links the math-lib
CFLAGS =  -std=c99 -O2
DEBUGFLAGS =-Wall -Wextra -pg -g -Wunused -Wl,--stack=1024000000
SRCS = main.c util\\drawingutil.c util\\util.c util\\math\\matrix4d.c util\\math\\vector4d.c util\\math\\matrix.c

default: compile
compile:
	$(CC) -o "render.exe" $(CFLAGS) $(LINKERFLAGS) $(SRCS)
debug:
	$(CC) -o "render.exe" $(CFLAGS) $(DEBUGFLAGS) $(LINKERFLAGS) $(SRCS)
clean:
	@echo "Cleaning up"
	rm render.exe analysis.txt gmon.out