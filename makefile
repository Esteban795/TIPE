SRCDIR = src
HEADDIR = include
LIBDIR = ./src

CFLAGS = -W -Wall -Wextra -Wvla -fsanitize=address $(shell sdl2-config --cflags) -lSDL2 -lm

LDFLAGS = -export-dynamic $(shell sdl2-config --libs)
DEPENDENCIES = $(SRCDIR)/vect2.c $(SRCDIR)/point.c $(SRCDIR)/spring.c $(SRCDIR)/data.c

build:
	gcc $(SRCDIR)/engine.c -o ./bin/TMD $(DEPENDENCIES) $(CFLAGS) 

run:
	./bin/TMD $(NB_SAMPLES)

clean:
	rm ./bin/TMD

all:
	make build
	make run NB_SAMPLES="4000";clear
	/bin/python3 ./src/plot.py
		
plot:
	/bin/python3 ./src/plot.py