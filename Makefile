### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-10 10:11:05 WEST>


## ----------------------------
## OS-specific things
## ----------------------------

ifeq ($(OS),Windows_NT)

ifeq ($(shell uname),CYGWIN_NT-5.1)
## Cygwin

PROG = mandeldraw
RMCMD = rm -f  $(PROG) $(addprefix build/, $(OBJS))
LIBS = -lGL -lglut -lGLU
else
## MinGW
PROG = mandeldraw.exe
RMCMD = del $(PROG) $(addprefix build\, $(OBJS))
LIBS =  -lfreeglut -lglu32 -lopengl32 
endif

else

## Unix-like

PROG = mandeldraw
RMCMD = rm -f  $(PROG) $(addprefix build/, $(OBJS))
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
OBJS = main.o mandeldraw.o mtexture.o colorspaces.o mousebox.o mwindow.o 


## --------------------------------
## Begin dependency definitions
## --------------------------------

all: $(PROG)

$(PROG): $(addprefix build/, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/main.o: src/main.cpp src/mandeldraw.h
	$(CC) -c $(CFLAGS) -o $@ src/main.cpp

build/mandeldraw.o: src/mandeldraw.h src/mandeldraw.cpp src/mousebox.h src/mtexture.h src/mwindow.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mandeldraw.cpp

build/mtexture.o: src/mtexture.h src/mtexture.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mtexture.cpp

build/colorspaces.o: src/colorspaces.h src/colorspaces.cpp src/log.h src/winmath.h	
	$(CC) -c $(CFLAGS) -o $@ src/colorspaces.cpp 

build/mousebox.o: src/mousebox.cpp src/mousebox.h src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mousebox.cpp 

build/mwindow.o: src/mwindow.h src/mwindow.cpp src/log.h
	$(CC) -c $(CFLAGS) -o $@ src/mwindow.cpp

clean:
	$(RMCMD)



### Makefile ends here
