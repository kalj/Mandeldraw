### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-13 09:39:51 CET>


## ----------------------------
## OS-specific things
## ----------------------------

ifeq ($(OS),Windows_NT)

ifeq ($(shell uname),CYGWIN_NT-5.1)
## Cygwin

PROG = mandeldraw
RMCMD = rm -f  $(PROG) testbmpio $(addprefix build/, $(OBJS) testbmpio.o)
LIBS = -lGL -lglut -lGLU
else
## MinGW
PROG = mandeldraw.exe
RMCMD = del $(PROG) testbmpio $(addprefix build\, $(OBJS) testbmpio.o)
LIBS =  -lfreeglut -lglu32 -lopengl32 
endif

else

## Unix-like

PROG = mandeldraw
RMCMD = rm -f  $(PROG) testbmpio $(addprefix build/, $(OBJS) testbmpio.o)
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
OBJS = main.o mandeldraw.o mtexture.o colorspaces.o mousebox.o mwindow.o bmpio.o


## --------------------------------
## Begin dependency definitions
## --------------------------------

all: $(PROG) testbmpio

$(PROG): $(addprefix build/, $(OBJS))
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

testbmpio: build/bmpio.o build/testbmpio.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/testbmpio.o: src/testbmpio.cpp src/bmpio.h
	$(CC) -c $(CFLAGS) -o $@ src/testbmpio.cpp

build/bmpio.o: src/bmpio.h src/bmpio.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/bmpio.cpp

clean:
	$(RMCMD)



### Makefile ends here
