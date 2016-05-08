# SplitSearch
Operative System Course Project

# Consegna

Realizzare un’applicazione denominata “ splitsearch” che effettua una ricerca in un insieme di dati almeno di tipo numerico. L’input è un file di testo passato come argomento (un dato per linea), mentre l’output (la/e posizione/i del valore o 0 ­ zero ­ se non presente) può avvenire su stdout o su un file di output passato ulteriormente come argomento. La ricerca deve avvenire dividendo in due parti l’insieme dei dati e iterando la chiamata in modo che ognuna sia verificata da un processo figlio (e così a cascata fino al limite di un unico dato da confrontare con il valore cercato).

# Spiegazione soluzione

## Makefile

Abbiamo usato delle variabili per parametrizzare i parametri di compilazione:

* _SRCDIR:_ contiene tutti i sorgenti del programma. Non si ipotizzano subdirectory;
* _BUILDDIR:_ contiene gli object file e il binario compilato e linkato;
* _OUTFILE:_ è il path del file binario compilato;
* _OBJS:_ contiene tutti i file oggetto ricavati dalla directory src;

## Migliorie

* _Marcatori_: l'eseguibile gestisce gli argomenti con alcuni marcatori. Quelli implementati sono: -v (che specifica il valore da trovare), -i (indica il path del file da analizzare), -r (specifica quanti risultati trovare prima di terminare l'esecuzione) e -o (indica un eventuale file di output dove salvare i valori). Inoltre non è necessario utilizzare questi marcatori in qualche ordine preciso, è sufficiente che ci siano quelli obbligatori (-v e -i);
* _Tipi di dato_: il programma è in grado di gestire diversi tipi di dato. Il file passato come input può contenere stringhe, interi o decimali;
* _Progresso delle azioni_: una volta in esecuzione, il programma stamperà a video, attraverso il simbolo "=", tutte le righe che ha finito di analizzare;
* _Gestione processi_: all'interno del nostro programma è anche implementato un meccanismo di limitazione dei processi. Questo per evitare una proliferazione di processi che potrebbe causare un blocco della macchina. Inoltre, è possibile simulare questa situazione tramite l'apposito marcatore --test che permette di specificare quanti il numero massimo di figli generabili tramite fork;
