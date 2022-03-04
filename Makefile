###################################
#
#Assignment: 2 - Shell OS
#
#Name: Tyler Desharnais, James Donaldson
#Date: 8 Marh 2022
#
###################################
CC = g++                        # use g++ for compiling c++ code or gcc for c code
CFLAGS = -O3 -Wall	-std=c++11	# compilation flags: -g for debugging. Change to -O2 or -O3 for optimized code.
LIB = -lm                       # linked libraries
LDFLAGS = -L.                   # link flags
PROG = prog1                    # target executable (output)
SRCS = Source.cpp shell.cpp	    # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o)			# object files for the target. Add more to this and next lines if there are more than one source files.


all : $(PROG) depend

$(PROG): $(OBJ) 
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

# cleanup
clean:
	/bin/rm -f *.o $(PROG) .depend

# DO NOT DELETE
