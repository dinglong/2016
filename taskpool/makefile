CC        = g++
CPPFLAGS  = -DLINUX -std=c++11 -Wall -g
LDFLAGS   = -shared
TARGET    = libtaskpool.so

OBJS      = task.o \
            worker.o \
            taskpool.o

all: ${OBJS}
	${CC} ${LDFLAGS} $^ -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@

