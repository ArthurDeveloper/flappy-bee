CXX = g++

CFLAGS = -IDependencies/include -Wall
LDFLAGS = -LDependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SRC = game.cpp Bee.cpp Pipe.cpp
OBJ = game.o Bee.o Pipe.o


all: game

game: $(OBJ)
	$(CXX) $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)
	.\game

game.o: game.cpp
	$(CXX) -c game.cpp $(CFLAGS)

Bee.o: Bee.cpp
	$(CXX) -c Bee.cpp $(CFLAGS)

Pipe.o: Pipe.cpp
	$(CXX) -c Pipe.cpp $(CFLAGS)

clean:
	DEL $(OBJ)
