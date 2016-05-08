# SplitSearch

## Descrizione

L'eseguibile permette di effettuare una ricerca all'intero di un file per trovare la posizione di un determinato valore, passato come argomento. L'algortimo agisce dividendo a metà l'insieme dei dati e iterando sulle due metà generate fino ad arrivare ad analizzare una singola linea (tramite la generazione di processi figli). Poiché ogni processo padre aspetta la terminazione dei suoi processi figli prima di continuare, il numero massimo di processi che possono venir generati è uguale a circa log(n) in base 2, dove n è il numero di righe del file di input.

## Uso

splitsearch -i <file_da_analizzare> -v <valore da cercare>

E' possibile anche passare delle informazioni aggiuntive che possono essere:
* -r <numero_di_risultati>: limita il numero di risultati;
* -o <file_di_output>: specifica dove salvare i risultati;
* --verbose: mostra a schermo informazioni sull'esecuzione;

## Makefile

Abbiamo usato delle variabili per parametrizzare i parametri di compilazione:

* _SRCDIR:_ contiene tutti i sorgenti del programma. Non si ipotizzano subdirectory;
* _BUILDDIR:_ contiene gli object file e il binario compilato e linkato;
* _OUTFILE:_ è il path del file binario compilato;
* _OBJS:_ contiene tutti i file oggetto ricavati dalla directory src;

## Migliorie

* _Marcatori_: l'eseguibile gestisce gli argomenti con alcuni marcatori. Quelli implementati sono: -v (che specifica il valore da trovare), -i (indica il path del file da analizzare), -r (specifica quanti risultati trovare prima di terminare l'esecuzione) e -o (indica un eventuale file di output dove salvare i valori). Inoltre non è necessario utilizzare questi marcatori in qualche ordine preciso, è sufficiente che ci siano quelli obbligatori (-v e -i);
* _Tipi di dato_: il programma è in grado di gestire diversi tipi di dato. Il file passato come input può contenere stringhe, interi o decimali;
* _Progresso delle azioni_: è possibile anche avere un controllo maggiore di quello che sta avvenendo durante l'esecuzione se, alla chiamata dell'eseguibile, viene passato il marcatore --verbose, in questo modo verranno stampate a schermo delle informazioni sull'esecuzione;
* _Gestione processi_: all'interno del nostro programma è anche implementato un meccanismo di controllo dell'esecuzione. Questo per evitare una proliferazione di processi che potrebbe causare un blocco della macchina. Inoltre, è possibile simulare questa situazione tramite l'apposito marcatore --test che permette di specificare quanti il numero massimo di figli generabili tramite fork;
