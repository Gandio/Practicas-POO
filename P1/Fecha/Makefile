CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -std=c++11
OBJETOS = fecha.o prueba-auto.o prueba-consola.o

all: prueba-auto prueba-consola

prueba-auto: prueba-auto.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) prueba-auto.o fecha.o

fecha.o: fecha.h
prueba-auto.o: fecha.h fct.h


prueba-consola: prueba-consola.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) prueba-consola.o fecha.o

prueba-consola.o: fecha.h

clean:
	$(RM) all $(OBJETOS) core *~
