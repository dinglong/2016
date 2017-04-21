CXX      = g++
CXXFLAGS = -g -I.:../util -Wall
CPPFLAGS = -DDEBUG
LIBS     =

VPATH=.:../util

OBJS = avl_tree.o \
	   util.o

exe  = avl 

all: ${exe}

${exe}: ${OBJS}
	${CXX} $^ ${LIBS} -o $@

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	-rm ${OBJS} ${exe}

