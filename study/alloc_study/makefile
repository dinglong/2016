CC = g++
CPPFLAGS = -Wall -g
LIBS     = 
TARGET   = test

OBJS     = pool.o \
           myallco.o

all: ${OBJS}
	${CC} $^ ${LIBS} -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
	%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@
