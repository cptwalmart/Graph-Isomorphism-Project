CXXFLAGS=-std=c++14 -g -Wall -Werror
OBJS=main.o
PROG=isomorph
${PROG}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^