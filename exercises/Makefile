LIBRARY=C:/msys64/mingw64/lib
INCLUDE=C:/msys64/mingw64/include
SRC=../src
BIN=./bin

CC=gcc 
CFLAGS=-I $(INCLUDE) -I ../include 
LIBS=  -L $(LIBRARY) -lglfw3 -lopengl32 -lm -lgdi32

ex1.exe: ./ex1.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 

ex2.exe: ./ex2.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 

	
ex3.exe: ./ex3.c $(SRC)/glad.c $(SRC)/shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 

ex4.exe: ./ex4.c $(SRC)/glad.c $(SRC)/ext_shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 

ex5.exe: ./ex5.c $(SRC)/glad.c $(SRC)/ext_shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 

ex6.exe: ./ex6.c $(SRC)/glad.c $(SRC)/ext_shaders.c $(SRC)/window.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(LIBS)
	./bin/./$@ 


