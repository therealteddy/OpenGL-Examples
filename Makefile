LIBRARY=C:/msys64/mingw64/lib
INCLUDE=C:/msys64/mingw64/include
SRC=./src
BIN=./bin

CC=gcc 
CFLAGS=-I $(INCLUDE) -I ./include 
LIBS=  -L $(LIBRARY) -lglfw3 -lopengl32 -lm -lgdi32

# The following recipies rely on shaders.h
hello_triangle.exe: $(SRC)/hello_triangle.c $(SRC)/glad.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

hello_rectangle.exe: $(SRC)/hello_rectangle.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

vertex_attribs.exe: $(SRC)/vertex_attribs.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

inouts.exe: $(SRC)/inouts.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

uniforms.exe: $(SRC)/uniforms.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

rainbow.exe: $(SRC)/rainbow.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

rainbow2.exe: $(SRC)/rainbow2.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

# The following recipies no longer rely on shaders.h but rather on ext_shaders.h