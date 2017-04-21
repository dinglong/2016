CC        = g++
CPPFLAGS  = -DLINUX -ansi -I. -Wall -g
TARGET    = prase

OBJS      = prase_doc.o \
            test.o

all: ${OBJS}
	${CC} $^ -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@

