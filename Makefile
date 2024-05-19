LIBRARY=C:/msys64/mingw64/lib
INCLUDE=C:/msys64/mingw64/include
SRC=./src
BIN=./bin

CC=gcc 
CFLAGS=-I $(INCLUDE) -I ./include 
LIBS=  -L $(LIBRARY) -lglfw3 -lopengl32 -lm -lgdi32


default: hello_triangle.exe hello_rectangle.exe

hello_triangle.exe: $(SRC)/hello_triangle.c $(SRC)/glad.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)

hello_rectangle.exe: $(SRC)/hello_rectangle.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
