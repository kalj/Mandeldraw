### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-09 10:44:47 CET>


CC = g++
# DEBUG = -g -DDEBUG
CFLAGS = -Wall -O3 -I./src -fopenmp $(DEBUG)

# @WINOS = $(shell echo %OS%)
# @UNOS = $(shell uname)

# ifeq ($(WINOS),Windows_NT)

# PROG = mandeldraw.exe
# LIBS = -lfreeglut -lglu32 -lopengl32
# RMCMD = del

# else

PROG = mandeldraw
RMCMD = rm -f

# ifeq ($(UNOS),Darwin)

# LIBS = -framework OpenGL -framework GLUT

# else

LIBS = -lglut -lGLU

# endif
# endif


all: $(PROG)

$(PROG): src/main.cpp build/mandeldraw.o build/mtexture.o build/colorspaces.o build/mousebox.o build/mwindow.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/mandeldraw.o: src/mandeldraw.h src/mandeldraw.cpp src/mousebox.h src/mtexture.h src/mwindow.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mandeldraw.cpp $(LIBS)

build/mtexture.o: src/mtexture.h src/mtexture.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mtexture.cpp $(LIBS)

build/colorspaces.o: src/colorspaces.h src/colorspaces.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/colorspaces.cpp

build/mousebox.o: src/mousebox.cpp src/mousebox.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mousebox.cpp

build/mwindow.o: src/mwindow.h src/mwindow.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mwindow.cpp

clean:

	$(RMCMD) $(PROG) build/mandeldraw.o build/mtexture.o build/colorspaces.o build/mousebox.o build/mwindow.o



### Makefile ends here
