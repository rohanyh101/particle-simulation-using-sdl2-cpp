all:
	g++ -I ./src/include -I ./headers -L ./src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2