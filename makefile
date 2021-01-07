#This makefile based off of the Canvas lectures and example makefile text file.

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -g

OBJS = main.o Ant.o Critter.o Doodlebug.o Game.o Grid.o inputValidation.o

SRCS = main.cpp Ant.cpp Critter.cpp Doodlebug.cpp Game.cpp Grid.cpp inputValidation.cpp

HEADERS = State.hpp Ant.hpp Critter.hpp Doodlebug.hpp Game.hpp Grid.hpp inputValidation.hpp

Group25: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o Group25

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm Group25 main.o Ant.o Critter.o Doodlebug.o Game.o Grid.o inputValidation.o
