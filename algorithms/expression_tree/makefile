CXX      = g++
CXXFLAGS = -g -Wall
CPPFLAGS = -DDEBUG
LIBS     =

VPATH=.:../util

OBJS = expr_translate.o \
	   tree.o \
	   stack.o \
	   test.o

exe  = expr

all: ${exe}

${exe}: ${OBJS}
	${CXX} $^ ${LIBS} -o $@

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	-rm ${OBJS} ${exe}

