TARGETS = additup

all: $(TARGETS)

additup: additup.o
	gccx -o additup additup.o

additup.o: additup.c
	gccx -c additup.c

clean:
	rm additup.o additup
