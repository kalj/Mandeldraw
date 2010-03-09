### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-03-09 10:19:55 CET>


CC = g++
# DEBUG = -g -DDEBUG
CFLAGS = -Wall -O3 -I./src -fopenmp $(DEBUG)
PROG = mandeldraw


ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

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
	rm -f $(PROG) build/mandeldraw.o build/mtexture.o build/colorspaces.o build/mousebox.o build/mwindow.o



### Makefile ends here
