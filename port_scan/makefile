####################################################
### compile port_scan project
### dinglonglong
### 2012-10-16
####################################################
CXX      = g++
CXXFLAGS = -g -I. 
CPPFLAGS = -DDEBUG
LIBS     =

obj      = scan_connect.o \
		   util.o

exe      = scan

all: ${exe}

${exe}: ${obj}
	${CXX} $^ ${LIBS} -o $@

.SUFFIXES:
.SUFFIXES: .cpp .o
%.o:%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	-rm *.o ${exe}

