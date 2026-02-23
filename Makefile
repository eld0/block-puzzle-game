build:
	g++ -Wall -std=c++17 ./src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o bpg
build-debug:
	g++ -g -Wall -std=c++17 ./src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o bpg
run:
	./bpg
clean:
	rm bpg
