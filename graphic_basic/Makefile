CC = g++

BREW = $(shell brew --prefix)

CFLAGS = -g -std=c++11 -Wno-deprecated-declarations
INCFLAGS = -Iinclude -I$(BREW)/include
LDFLAGS = -framework OpenGL -L$(BREW)/lib -lglfw

RM = /bin/rm -f
all: menv
menv: main.o Camera.o Cube.o Shader.o Tokenizer.o Window.o DOF.o Joint.o Skeleton.o imgui_demo.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_tables.o imgui_widgets.o imgui.o GUI.o Vertex.o Skin.o Animation.o Channel.o Keyframe.o
	$(CC) -o menv main.o Camera.o Cube.o Shader.o Tokenizer.o Window.o DOF.o Joint.o Skeleton.o imgui_demo.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_tables.o imgui_widgets.o imgui.o GUI.o Vertex.o Skin.o Animation.o Channel.o Keyframe.o $(LDFLAGS)
main.o: main.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp

imgui_demo.o: 
	cp imgui/*.o .
GUI.o: src/GUI.cpp include/GUI.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/GUI.cpp
Animation.o: src/Animation.cpp include/Animation.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Animation.cpp
Channel.o: src/Channel.cpp include/Channel.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Channel.cpp

Keyframe.o: src/Keyframe.cpp include/Keyframe.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Keyframe.cpp
Cube.o: src/Cube.cpp include/Cube.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Cube.cpp

Joint.o: src/Joint.cpp include/Joint.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Joint.cpp

Skeleton.o: src/Skeleton.cpp include/Skeleton.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Skeleton.cpp

Skin.o: src/Skin.cpp include/Skin.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Skin.cpp

Vertex.o: src/Vertex.cpp include/Vertex.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Vertex.cpp

DOF.o: src/DOF.cpp include/DOF.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/DOF.cpp
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
Tokenizer.o: src/Tokenizer.cpp include/Tokenizer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Tokenizer.cpp
Window.o: src/Window.cpp include/Window.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Window.cpp

clean: 
	$(RM) *.o menv
