CC        = g++
CPPFLAGS  = -DLINUX -ansi -I. -Wall -g
TARGET    = spider

OBJS      = analysor.o \
			node.o \
			pages.o \
			reply.o \
			request.o \
			filter.o \
			test.o

all: ${OBJS}
	${CC} $^ -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@

