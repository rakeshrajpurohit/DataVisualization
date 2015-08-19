CC = g++

CFLAGS = -Wall

PROG = vectorField

SRCS = vectorField.cpp floatData.cpp Glyphus.cpp ColorMap.cpp LIC.cpp

LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
