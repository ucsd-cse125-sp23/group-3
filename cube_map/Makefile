CC = g++

BREW = $(shell brew --prefix)

CFLAGS = -g -std=c++11 -Wno-deprecated-declarations
INCFLAGS = -Iinclude -I$(BREW)/include
LDFLAGS = -framework OpenGL -L$(BREW)/lib -lglfw

RM = /bin/rm -f
all: menv
menv: main.o Camera.o Cube.o Shader.o Tokenizer.o Window.o Ground.o Map.o Submap.o
	$(CC) -o menv main.o Camera.o Cube.o Shader.o Tokenizer.o Window.o Ground.o Map.o Submap.o $(LDFLAGS)
main.o: main.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp
Ground.o: src/Ground.cpp include/Ground.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Ground.cpp
Cube.o: src/Cube.cpp include/Cube.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Cube.cpp
Map.o: src/Map.cpp include/Map.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Map.cpp

Submap.o: src/Submap.cpp include/Submap.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Submap.cpp
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
Tokenizer.o: src/Tokenizer.cpp include/Tokenizer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Tokenizer.cpp
Window.o: src/Window.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Window.cpp

clean: 
	$(RM) *.o menv
