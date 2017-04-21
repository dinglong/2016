CXX      = g++
CXXFLAGS = -g -I. -Wall
CPPFLAGS = -DDEBUG
LIBS     =

OBJS = example.o \
	   util.o

exe  = example 

all: ${exe}

${exe}: ${OBJS}
	${CXX} $^ ${LIBS} -o $@

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	-rm ${OBJS} ${exe}

