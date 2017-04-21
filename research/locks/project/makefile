TOP_DIR  = ..

CC       = g++
CPPFLAGS = -I${TOP_DIR}/rpc -I${TOP_DIR}/util/ -I${TOP_DIR}/log4c -I${TOP_DIR}/locks_s -I${TOP_DIR}/locks_c -Wall -g
LIBS     = 

SERVER   = s
CLIENT   = c

S_OBJS   = ${TOP_DIR}/util/util.o \
					 ${TOP_DIR}/util/props.o \
					 ${TOP_DIR}/rpc/msg.o \
					 ${TOP_DIR}/rpc/service.o \
					 ${TOP_DIR}/rpc/base_func.o \
					 ${TOP_DIR}/log4c/logger.o \
					 ${TOP_DIR}/locks_s/dir_tree.o \
					 ${TOP_DIR}/locks_s/server.o

C_OBJS   = ${TOP_DIR}/util/util.o \
					 ${TOP_DIR}/util/props.o \
					 ${TOP_DIR}/rpc/msg.o \
					 ${TOP_DIR}/locks_c/locks_c.o \
					 ${TOP_DIR}/locks_c/client.o

all : ${SERVER} ${CLIENT}

${SERVER} : ${S_OBJS}
	${CC} $^ ${LIBS} -o ${SERVER}

${CLIENT} : ${C_OBJS}
	${CC} $^ ${LIBS} -o ${CLIENT}

clean:
	rm -rf ${S_OBJS} ${C_OBJS} ${SERVER} ${CLIENT} core

.SUFFIXES:
.SUFFIXES: .cpp .o
	%.o:%.cpp
	$(CC) -c ${CPPFLAGS} $< -o $@
