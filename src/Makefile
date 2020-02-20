CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = biquadris

GAME = game/game.o game/player.o game/controller.o
BOARD = game/board/block.o game/board/cell.o game/board/board.o game/board/blocktype.o game/board/colour.o
LEVEL = game/levels/level.o game/levels/level0.o game/levels/level1.o game/levels/level2.o game/levels/level3.o game/levels/level4.o
DISPLAY = displays/graphicDisplay.o displays/textDisplay.o displays/window.o displays/subject.o

OBJECTS = main.o ${GAME} ${BOARD} ${LEVEL} ${DISPLAY}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}