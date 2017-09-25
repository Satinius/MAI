CC = g++
FLAGS = -std=c++11
SOURCES = lw01.o Rectangle.o Trapeze.o Rhombus.o
EXECUTABLE = start
all: build

build: lw01.o Rectangle.o Trapeze.o Rhombus.o
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

lw01.o: lw01.cpp Rectangle.h Trapeze.h Rhombus.h
	$(CC) $(FLAGS) -c lw01.cpp

Rectangle.o: Rectangle.cpp Rectangle.h Figure.h
	$(CC) $(FLAGS) -c Rectangle.cpp

Trapeze.o: Trapeze.cpp Trapeze.h Figure.h
	$(CC) $(FLAGS) -c Trapeze.cpp

Rhombus.o: Rhombus.cpp Rhombus.h Figure.h
	$(CC) $(FLAGS) -c Rhombus.cpp

clean:
	rm -f $(SOURCES) $(EXECUTABLE)