CC        = g++
CPPFLAGS  = -DLINUX -ansi -I.:../props -Wall -g
LDFLAGS   = -shared -fPCI
TARGET    = liblog4c.so

OBJS      = logger_factory.o \
			logger.o \
			console_appender.o \
			file_appender.o \
			layout.o \
			appender.o \
			log_event.o

all: ${OBJS}
	${CC} ${LDFLAGS} $^ -o ${TARGET}

clean:
	rm -rf *.o ${TARGET} core

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@

