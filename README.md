# SplitSearch
Operative System Course Project

#Instructions

Realizzare un’applicazione denominata “ splitsearch” che effettua una ricerca in un insieme di dati almeno di tipo numerico. L’input è un file di testo passato come argomento (un dato per linea), mentre l’output (la/e posizione/i del valore o 0 ­ zero ­ se non presente) può avvenire su stdout o su un file di output passato ulteriormente come argomento. La ricerca deve avvenire dividendo in due parti l’insieme dei dati e iterando la chiamata in modo che ognuna sia verificata da un processo figlio (e così a cascata fino al limite di un unico dato da confrontare con il valore cercato).
Esempio di chiamata, ipotizzando che nell’ordine si passino valore, file di input e di output:
```
splitsearch 3 input.txt output.txt
```
se l’input contiene (uno per riga) i dati 7,3,5,4, in output si dovrà ottenere 2 (la posizione del valore cercato, cioè il “3” tra i dati di input): se il valore fosse presente più volte si avrà una lista di risultati.

Migliorie suggerite:
  - gestire gli argomenti con dei marcatori (ad esempio “­v” per il valore da cercare, “­i” per il
    file di input e “­o” per quello di output) evitando di usare la posizione come filtro
  - gestire dati numerici non interi
  - gestire dati di tipo stringa
  - mostrare il progresso delle azioni (ad esempio la gerarchia dei processi, la quantità di
    dati elaborati, etc.)
  - gestire un’opzione aggiuntiva per decidere il numero massimo di risultati da restituire e
    far terminare immediatamente l’applicazione. In questo caso se si decidesse di impostare come argomento “1” (massimo 1 risultato) e il valore fosse presente anche più volte tra i dati, l’applicazione dovrebbe terminare senza attendere ulteriormente
  - gestire l’impossibilità di generare nuovi processi (ad esempio perchè troppi) attraverso un’esecuzione diretta

#

Si deve scegliere UN SOLO progetto tra quelli (due quest'anno) proposti: si raccomanda di verificare che sia tutto a posto e funzionante prima dell'invio (salvo eccezioni particolari non sono ammessi nuovi invii: l'invio equivale alla consegna di uno scritto)
per semplificare lo svolgimento si è deciso di usare come riferimento una versione di Linux facilmente testabile (Ubuntu 14.x) anzichè la v.m. ipotizzata inizialmente: questo anche a causa di alcuni disguidi interni e alle giornate di interruzione nel calendario: in pratica il progetto deve funzionare se "aperto" sul s.o. indicato e compilato con qualcosa come "gcc nomefile1.c nomefile2.c ..." senza ulteriori opzioni (che sono ammesse solo per ragioni secondarie, come "-o" per scegliere il nome del file di output o altri argomenti per avere informazioni sull'andamento della compliazione)
il "range" di valutazione è indicativo: una risoluzione completa delle richieste minime corrisponde grosso modo al valore minimo, mentre soddisfare tutti i requisiti e le migliorie al valore massimo: a questo si aggiungono valutazioni collaterali (come l'originalità della soluzione, l'ordine di stesura dei codici e dei commenti, etc.)
le informazioni sono tutte caricate su Esse3: ho notato però che non di rado questa piattaforma ha dei problemi di accesso (come utenti o ai dati: di recente o ri-caricato ad esempio le ultime slides per sicurezza)... si deve comunque utilizzare il menu laterale per poter arrivare al dettaglio dei contenuti e poter scaricare gli allegati (altrimenti ne compare solo il nome e non sono "cliccabili")
i progetti si possono completare con le sole informazioni discusse in aula: nel prossimo incontro (l'ultimo del percorso prettamente "didattico") sarà fatto un riepilogo della parte più legata a "processi e comunicazioni" con qualche funzione aggiuntiva che può semplificare lo svolgimento o comunque fornire nuovi spunti
cercherò di mandare via mail direttamente alcune informazioni generali (come questo messaggio), ma ricordo ancora una volta di consultare costantemente "Esse3"

# part 2

formazione gruppi: consiglio di sfruttare Esse3 e l'aula (per esempio appuntando un foglio) per chi non avesse "compagni di gruppo" e trovare colleghi "liberi"... ricordo anche che quest'anno sono consentiti sia gruppi di 2 che di 3 unità, quindi chi magari ha "un posto libero" potrebbe offrirsi per accogliere un terzo componente
generazione processi: quando si parla di "iterazione" nel progetto del "mergesort" si intende concettualmente di ripetere il procedimento a cascata... in pratica si deve creare in qualche modo un "albero di processi" da cui poi recuperare le informazioni per ricostruire il risultato finale... qualunque soluzioni che non violi i requisiti va bene, essendocene alcune ovviamente migliori (funzionalmente, ma anche come "pulizia")... l'uso di fork e pipe/fifo è la strada da seguire se non ci sono motivi particolari per non farlo (ad esempio perché si ritiene che non possano risolvere il problema)
per gli argomenti NON si può usare getopt e altre funzioni "avanzate", ma solo argc ed argv: non è richiesto (ma si può farlo) di riprodurre tali funzioni avanzate... occorre solo che siano gestiti gli argomenti dell'eseguibile correttamente (quindi i parametri necessari)... per intendersi non è necessario realizzare funzioni di parsing degli argomenti "generiche", volendo, purché siano ben gestiti quelli richiesti dal programma (ne riparlerò in aula)
quando si parla di gestire tra i dati di input - come migliorie - dati non numerici si intende semplicemente quanto detto: il requisito minimo è che siano ordinati/ricercati (a seconda del progetto) dati interi, ma come miglioria si può lavorare su dati non interi e infine su stringhe (in cui la difficoltà un po' superiore è data dall'attenzione per la gestione del confronto tra due valori)

# part 3

Per quanto riguarda la comunicazione tra i processi si dovrebbero sfruttare pipe/fifo (o eventualmente altre syscall con valori di ritorno) dove possibile

Altre informazioni (relative a richieste fatte da alcuni studenti):
è possibile usare file temporanei (ragionevolmente da eliminare appena possibile)
gestendo dati numerici si includono anche valori negativi (prestare eventualmente attenzione all'uso del segno "meno" nel caso dell'argomento da ricercare...)
NON si possono usare funzioni di gestione della memoria salvo le più semplici  tipo malloc/free (quindi nessuna funzione per memoria condivisa, ad esempio)
SI possono usare tutte le funzioni della libreria standard "string.h", oltre che quelle di "stdio.h" e "stdlib.h"
