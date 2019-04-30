who1:who1.o
	gcc -o who1 who1.c -std=c99
who2:who2.o utmplib.o
	gcc -o who2 who2.c utmplib.c -std=c99
cp1:cp1.o
	gcc -o cp1 cp1.c -std=c99 
clean:
	rm who1.o who1 who2.o who2 utmplib.o cp1.o cp1 
