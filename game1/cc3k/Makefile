CXX=g++

CXXFLAGS=-std=c++14 -Wall -MMD -g

SOURCES=$(wildcard *.cc)

OBJECTS=$(SOURCES:.cc=.o)

DEPENDS=${OBJECTS:.o=.d}

EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPDNDS}

