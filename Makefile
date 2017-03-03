CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -Wunreachable-code
GCC = gcc $(CFLAGS)
OBJS =  maze.o path.o pa07.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes 

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
all: pa07
	

pa07: $(OBJS) path.h maze.h
	$(GCC) $(OBJS) -o pa07

test: pa07
	#this should succeed
	./pa07 inputs/maze1 inputs/path1
	#this should fail
	./pa07 inputs/maze1 inputs/path1-bad1
	#this should fail
	./pa07 inputs/maze1 inputs/path1-bad2

%.o: %.c 
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f pa07
