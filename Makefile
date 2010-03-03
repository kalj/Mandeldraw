### Makefile.tpl - 
## 
## Author: Karl Ljungkvist
## Last changed: <2010-02-28 16:13:08 CET>


CC = g++
CFLAGS = -Wall -O3
PROG = mandeldraw

SRCS = main.cpp mandelbuffer.cpp 

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

all: $(PROG)

$(PROG): main.cpp mandeldraw.o mandelbuffer.o colorspaces.o mousebox.o mandelwindow.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

mandeldraw.o: mandeldraw.h mandeldraw.cpp mousebox.h mandelbuffer.h mandelwindow.h
	$(CC) -c $(CFLAGS) -o $@ mandeldraw.cpp $(LIBS)

mandelbuffer.o: mandelbuffer.h mandelbuffer.cpp 
	$(CC) -c $(CFLAGS) -o $@ mandelbuffer.cpp $(LIBS)

colorspaces.o: colorspaces.h colorspaces.cpp
	$(CC) -c $(CFLAGS) -o $@ colorspaces.cpp

mousebox.o: mousebox.cpp mousebox.h
	$(CC) -c $(CFLAGS) -o $@ mousebox.cpp

mandelwindow.o: mandelwindow.h mandelwindow.cpp
	$(CC) -c $(CFLAGS) -o $@ mandelwindow.cpp

clean:
	rm -f $(PROG) mandeldraw.o mandelbuffer.o colorspaces.o mousebox.o



### Makefile ends here
