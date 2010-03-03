### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-03 10:01:40 CET>


CC = g++
CFLAGS = -Wall -O3 -I./src
PROG = mandeldraw


ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

all: $(PROG)

$(PROG): src/main.cpp build/mandeldraw.o build/mandelbuffer.o build/colorspaces.o build/mousebox.o build/mandelwindow.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/mandeldraw.o: src/mandeldraw.h src/mandeldraw.cpp src/mousebox.h src/mandelbuffer.h src/mandelwindow.h
	$(CC) -c $(CFLAGS) -o $@ src/mandeldraw.cpp $(LIBS)

build/mandelbuffer.o: src/mandelbuffer.h src/mandelbuffer.cpp 
	$(CC) -c $(CFLAGS) -o $@ src/mandelbuffer.cpp $(LIBS)

build/colorspaces.o: src/colorspaces.h src/colorspaces.cpp
	$(CC) -c $(CFLAGS) -o $@ src/colorspaces.cpp

build/mousebox.o: src/mousebox.cpp src/mousebox.h
	$(CC) -c $(CFLAGS) -o $@ src/mousebox.cpp

build/mandelwindow.o: src/mandelwindow.h src/mandelwindow.cpp
	$(CC) -c $(CFLAGS) -o $@ src/mandelwindow.cpp

clean:
	rm -f $(PROG) build/mandeldraw.o build/mandelbuffer.o build/colorspaces.o build/mousebox.o



### Makefile ends here
