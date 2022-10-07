all: game

game: game.cpp 
	g++ -IDependencies/include -o game.exe game.cpp -LDependencies/lib -lmingw32 -lSDL2main -lSDL2
	.\game
