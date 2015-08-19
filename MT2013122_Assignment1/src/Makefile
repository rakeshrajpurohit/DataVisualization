CC = g++

CFLAGS = -Wall

PROG = main

SRCS = main.cpp EasyBMP.cpp vec3f.cpp elevation.cpp

LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
