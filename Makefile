### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-15 19:00:36 CET>


## ----------------------------
## OS-specific things
## ----------------------------

ifeq ($(OS),Windows_NT)

ifeq ($(shell uname),CYGWIN_NT-5.1)
## Cygwin
RMCMD = rm -f
SLASH = /
LIBS = -lGL -lglut -lGLU
else
## MinGW
RMCMD = del
SLASH = \\
LIBS =  -lfreeglut -lglu32 -lopengl32 
endif

else

## Unix-like
RMCMD = rm -f
SLASH = /

ifeq ($(shell uname),Darwin)
## OSX
LIBS = -framework OpenGL -framework GLUT
else
## Linux
LIBS = -lglut -lGLU

endif
endif


## --------------------------------
## Common stuff
## --------------------------------
CC = g++
# DEBUG = -g -DDEBUG
CFLAGS = -Wall -O3 -I./src $(DEBUG) -fopenmp
# BENCHMARK = benchmark
PROG = mandeldraw

## --------------------------------
## Begin dependency definitions
## --------------------------------
all: $(PROG) 


$(PROG): build/main.o build/mandeldraw.o build/mtexture.o build/colorspaces.o build/mousebox.o build/mwindow.o build/bmpio.o build/log.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/main.o: src/main.cpp src/mandeldraw.h
	$(CC) -c $(CFLAGS) -o $@ src/main.cpp

build/mandeldraw.o: src/mandeldraw.h src/mandeldraw.cpp src/mousebox.h src/mtexture.h src/mwindow.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mandeldraw.cpp

build/mtexture.o: src/mtexture.h src/mtexture.cpp src/log.h src/bmpio.h
	$(CC) -c $(CFLAGS) -o $@ src/mtexture.cpp

build/colorspaces.o: src/colorspaces.h src/colorspaces.cpp src/log.h src/winmath.h	
	$(CC) -c $(CFLAGS) -o $@ src/colorspaces.cpp 

build/mousebox.o: src/mousebox.cpp src/mousebox.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mousebox.cpp 

build/mwindow.o: src/mwindow.h src/mwindow.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mwindow.cpp

build/bmpio.o: src/bmpio.h src/bmpio.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/bmpio.cpp

build/log.o: src/log.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/log.cpp
clean:
	$(RMCMD) $(PROG) build$(SLASH)*



### Makefile ends here
