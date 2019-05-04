CXXFLAGS=-std=c++11 -g -Wall -Werror
OBJS=main.o
PROG=isomorph
${PROG}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^