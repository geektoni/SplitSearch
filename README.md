# SplitSearch
Operative System Course Project

# Consegna

Realizzare un’applicazione denominata “ splitsearch” che effettua una ricerca in un insieme di dati almeno di tipo numerico. L’input è un file di testo passato come argomento (un dato per linea), mentre l’output (la/e posizione/i del valore o 0 ­ zero ­ se non presente) può avvenire su stdout o su un file di output passato ulteriormente come argomento. La ricerca deve avvenire dividendo in due parti l’insieme dei dati e iterando la chiamata in modo che ognuna sia verificata da un processo figlio (e così a cascata fino al limite di un unico dato da confrontare con il valore cercato).

# Spiegazione soluzione

## Makefile

Abbiamo usato delle variabili per parametrizzare i parametri di compilazione:

* _SRCDIR:_ contiene tutti i sorgenti del programma. Non si ipotizzano subdirectory.
* _BUILDDIR:_ contiene gli object file e il binario compilato e linkato.
* _OUTFILE:_ è il path del file binario compilato
* _OBJS:_ contiene tutti i file oggetto ricavati dalla directory src.

## Algorithm


