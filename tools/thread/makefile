CC = g++
CPPFLAGS = -Wall -g
LIBS     = -lpthread
TARGET   = test

OBJS     = test.o \
           thread.o \
           thread_pool.o

all: ${OBJS}
	${CC} $^ ${LIBS} -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
	%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@
