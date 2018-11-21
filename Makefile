TARGETS = additup multi

all: $(TARGETS)

additup: additup.o
	gccx -o additup additup.o

additup.o: additup.c
	gccx -c additup.c

multi: multi.o
	gccx -o multi multi.o

multi.o: multi.c
	gccx -c multi.c

clean:
	rm additup.o additup multi.o multi
