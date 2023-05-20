CC = g++

BREW = $(shell brew --prefix)

CFLAGS = -g -std=c++11 -Wno-deprecated-declarations
INCFLAGS = -Iinclude -I$(BREW)/include
LDFLAGS = -framework OpenGL -L$(BREW)/lib -lglfw

RM = /bin/rm -f
all: menv
menv: main.o Camera.o Cube.o Shader.o Tokenizer.o Image.o Window.o Ground.o Map.o Submap.o graphic2D.o CollisionDetection.o Minimap.o Light.o Mult_Lights.o Particles.o
	$(CC) -o menv main.o Camera.o Cube.o Shader.o Tokenizer.o Image.o Window.o Ground.o Map.o Submap.o graphic2D.o CollisionDetection.o Minimap.o Light.o Mult_Lights.o Particles.o $(LDFLAGS)
main.o: main.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
graphic2D.o: src/graphic2D.cpp include/graphic2D.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/graphic2D.cpp

Image.o: src/Image.cpp include/Image.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Image.cpp
Particles.o: src/Particles.cpp include/Particles.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Particles.cpp
Minimap.o: src/Minimap.cpp include/Minimap.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Minimap.cpp
Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp
Ground.o: src/Ground.cpp include/Ground.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Ground.cpp
Cube.o: src/Cube.cpp include/Cube.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Cube.cpp
Map.o: src/Map.cpp include/Map.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Map.cpp

Light.o: src/Light.cpp include/Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Light.cpp

Mult_Lights.o: src/Mult_Lights.cpp include/Mult_Lights.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Mult_Lights.cpp
Submap.o: src/Submap.cpp include/Submap.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Submap.cpp
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
CollisionDetection.o: src/CollisionDetection.cpp include/CollisionDetection.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/CollisionDetection.cpp
Tokenizer.o: src/Tokenizer.cpp include/Tokenizer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Tokenizer.cpp
Window.o: src/Window.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Window.cpp

clean: 
	$(RM) *.o menv
