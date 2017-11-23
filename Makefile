# Makefile: A standard Makefile for main.c

OBJECTS = example.o quine_mc_cluskey.o

all  : main
main : $(OBJECTS)
	$(CC) -o main $^

clean:
	/bin/rm -rf main  $(OBJECTS)
# END OF FILE
