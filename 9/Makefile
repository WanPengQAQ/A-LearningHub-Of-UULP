OBJ1 = smsh1.o splitline.o execute.o
OBJ2 = smsh2.o splitline.o execute.o process.o controlflow.o
smsh1:$(OBJ1)
	gcc $(OBJ1) -o smsh1 -Wall
smsh2:$(OBJ2)
	gcc $(OBJ2) -o smsh2 -Wall

smsh1.o: smsh1.c
splitline.o:splitline.c
execute.o:execute.c

process.o:process.c
controlflow.o:controlflow.c

clean:
	rm smsh1 $(OBJ1) smsh2 $(OBJ2)

