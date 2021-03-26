# compilazione: programma a file singolo
copiafile: copiafile.c
	gcc -ansi -Wall -O copiafile.c -o copiafile
# rimuove gli eventuali file oggetto
pulisci:
	rm -f copiafile.o
# rimuove gli eventuali file oggetto e l'eseguibile
pulisci_tutto:
	rm -f copiafile *.o
