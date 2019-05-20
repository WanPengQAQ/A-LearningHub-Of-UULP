OBJ = smsh1.o splitline.o execute.o
smsh1:$(OBJ)
	gcc $(OBJ) -o smsh1
smsh1.o: smsh1.c
splitline.o:splitline.c
execute.o:execute.c

clean:
	rm smsh1 $(OBJ)

