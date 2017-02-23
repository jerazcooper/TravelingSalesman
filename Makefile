CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = TSP
OBJECTS = city.o main.o path.o state.o tracker.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
