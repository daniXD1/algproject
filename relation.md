# Relazione di Laboratorio
## Algoritmi di ordinamento

### Corso: Algoritmi e strutture dati
### Anno accademico: 2024/2025

### Gruppo di lavoro:
- Fragrante Daniel - 167543 - fragrante.daniel@spes.uniud.it
- Mauro Andrea - 167544 - mauro.andrea002@spes.uniud.it
- Driussi Emanuele - 167925 - driussi.emanuele@spes.uniud.it

\newpage

# Introduzione

L’obiettivo di questa relazione è di analizzare le caratteristiche, la complessità e il tempo di esecuzione degli algoritmi di ordinamento visti a lezione, quali quickSort, quickSort3Way, countingSort e mergeSort.

Facciamo ciò generando casualmente degli array con vari metodi e misurando il tempo richiesto per l'ordinamento.

Nei vari capitoli confronteremo l’esecuzione dei vari algoritmi di sorting mediante grafici comparativi su diversi tipi di input per evidenziare i punti di forza o debolezza di questi rispetto agli altri o alle loro varianti.
Paragonando anche le performance teoriche dell’algoritmo con quelle misurate empiricamente.

## Dettagli Implementativi

Il sistema di generazione degli array, algoritmi di sorting e misurazione del tempo è stato completamente implementato in C.

Utilizziamo la funzione `clock_gettime(CLOCK_MONOTONIC, &time)` per la misurazione dei tempi, che sono sempre salvati in millisecondi.

Definiamo delle costanti utilizzate per l’implementazione delle funzioni, in particolare:

- $n_{min}=100$: Numero minimo di elementi nell’array
- $n_{max}=1000000$: Numero massimo di elementi nell’array
- $range=1000000$: Range dei valori interi all’interno degli array
- $n_{static}=100000$: Lunghezza fissa dell’array nel caso della generazione per valori diversi
- $d_{min}=100$: n. minimo di elementi diversi nell’array nel caso della generazione per valori diversi
- $d_{max}=100000$: n. massimo di elementi diversi nel caso della generazione per valori diversi

Per generare gli array da ordinare sono stati utilizzati 3 metodi:

- Generazione Semplice: Genera un array di lunghezza $n\in[n_{min}, n_{max}]$, i valori sono casuali, all’interno dell’intervallo $[0, range]$
- Generazione per valori diversi: Genera un array di lunghezza fissa $n_{static}$ contenente $d$ valori diversi, estratti dal range $[0, range]$ (non e garantito che ci siano esattamente $d$ valori diversi data la natura casuale della generazione)
- Generazione di array ordinati al contrario: Genera un array ordinato in ordine decrescente di lunghezza $n\in[n_{min}, n_{max}]$, i valori all'interno dell'array sono esattamente $n,n-1,\dots 2,1$

In base al tipo di generazione dell’array scelto il sistema parte dal parametro minimo e genera 100 punti fino al parametro massimo seguendo una progressione geometrica.

Per ogni punto della progressione si generano e ordinano 10 array.
Questo permette di lisciare eventuali inconsistenze nella durata dell’esecuzione e fornire un valore medio all’esecuzione dell’array su quel parametro.

Le misurazioni sono separate per ognuna delle 10 iterazioni.

> Nota: Non vengono effettuati controlli relativi alla precisione della misurazione utilizzando la risoluzione del clock. Grazie a questo le misurazioni utilizzate in questa ricerca non comprendono il tempo di inizializzazione dell’array. Se si volesse implementare questi controlli nelle misurazioni sarà sufficiente cambiare la funzione `measure_batch` con `measure_batch_gen_included` e aggiungere la risoluzione del clock come ultimo parametro.

\newpage

# Comparazione fra varianti di quicksort

## Generazione Semplice

Valutiamo la complessità e l’efficienza delle varie implementazioni dell’algoritmo di quickSort, quali quickSort, quicksort3way e quickSortSelect su una generazione semplice degli array come sopra descritto.

Ci aspettiamo che l’esecuzione di quickSort risulti la più efficiente rispetto a quickSort3Way in quanto l’utilizzo di un puntatore in più in fase di partition da parte di quest'ultimo porta a controlli aggiuntivi che però in questo caso non lo rendono davvero vantaggioso.

Vogliamo osservare inoltre se le costanti moltiplicative introdotte dalla procedura Select di quickSortSelect siano compensate dalla scelta del pivot ottimale, oppure se il pivot preso da quickSort, anche se non il migliore, porti comunque a prestazioni superiori.

\newpage

![Quick Sort Variants Simple Gen (Lin Scale)](src/AllQuick-simple-lin.png){ height=225px }

![Quick Sort Variants Simple Gen (Log Scale)](src/AllQuick-simple-log.png){ height=225px }

Dai grafici possiamo concludere che le nostre ipotesi erano corrette.
Inoltre viene evidenziato come l'applicazione di Select porti a un grande degrado di prestazioni.
Questo non conferma le nostre aspettative, dato che le costanti moltiplicative introdotte non vengono compensate dalla scelta del pivot ideale.

\newpage

## Generazione per valori diversi
Valutiamo la complessità e l’efficienza di quickSort e quickSort3way già menzionate utilizzando la generazione per valori diversi come descritto in “Dettagli implementativi”.

Ci aspettiamo che l’algoritmo di quicksort3way risulti il più efficiente per valori bassi di $d$, quindi quando l'array contiene molti valori ripetuti.
Questo è dato dall'implementazione della partition che esclude dalle chiamate ricorsive gli elementi uguali al pivot, ed è ottimizzato proprio per questi tipi di input.
Comunque non si dovrebbe osservare un degrado delle prestazioni di quickSort poiché le condizioni di corretto funzionamento non sono state modificate rispetto all'esperimento precedente.

\newpage

![Quick Sort Variants Different Gen (Lin Scale)](src/AllQuick-different-lin.png){ height=225px }

![Quick Sort Variants Different Gen (Log Scale)](src/AllQuick-different-log.png){ height=225px }

Come ci aspettavamo quickSort3Way risulta il migliore per valori piccoli di $d$, in particolare per $d\lesssim 10000$, cioe circa fino a quando ci sono soltanto $\frac{len}{10}$ valori unici nell'array.
Oltre tale valore le costanti moltiplicative introdotte dal partition modificato non sono più compensate.

Osserviamo però che quickSort classico peggiora notevolmente per valori bassi di $d$, questo potrebbe essere causato dal fatto che venga preso diverse volte il medesimo valore come pivot creando delle chiamate ricorsive sbilanciate, è quindi molto probabile che si verifichi un importante degrado delle prestazioni di quickSort.
All'aumentare di $d$ la probabilità che questo fenomeno si verifichi diminuisce e si torna a una normale esecuzione di quickSort.

\newpage

## Generazione ordinata al contrario
Valutiamo la complessità e l’efficienza delle varie implementazioni dell’algoritmo di quickSort già menzionate su array ordinati in ordine decrescente generati come sopra descritto.

Ci aspettiamo che gli algoritmi di quickSort e quicksort3way subiscano un forte degrado delle performance, questo perché prendere come pivot l’elemento in ultima posizione implica che la chiamata ricorsiva non partizioni l’array a metà, portando a chiamate ricorsive sbilanciate.
Questo portare a una complessità quadratica invece della $O(n logn)$ del caso medio.

Invece quickSortSelect non dovrebbe essere affetto da questo problema vista la scelta ottimale del pivot.

\newpage

![Quick Sort Variants Reverse Gen (Lin Scale)](src/AllQuick-reverse-lin.png){ height=225px }

![Quick Sort Variants Reverse Gen (Log Scale)](src/AllQuick-reverse-log.png){ height=225px }

> Nota: quickSort e quickSort3Way sono stati eseguiti solo fino a array di lunghezza inferiore per via del lungo tempo di esecuzione.

Vediamo che otteniamo i risultati aspettati.

\newpage

# Comparazione con altri algoritmi

## Generazione Semplice

Valutiamo la complessità e l’efficienza di quickSort e delle sue varianti quickSort3Way e quickSortSelect insieme a mergeSort e countingSort.

Ci interesseremo in particolare a vedere quanto efficiente sarà l’algoritmo mergeSort rispetto agli altri di medesima complessità $O(n log(n))$.
Comunque ipotizziamo che il migliore tra gli algoritmi con tempo $O(n log(n))$ sia quickSort, questo perché mergeSort inizializza diversi array di supporto che rischiano di rallentare la sua esecuzione.

Inoltre osserviamo l'andamento di countingSort per valutare in quali condizioni l'inizializzazione dell’array di supporto intaccherà la sua efficienza effettiva e se questo lo porterà a essere più lento di un algoritmo $O(n log(n))$ nonostante abbia complessita $O(n)$.

> Nota: I valori all’interno dell’array sono compresi in $[0, range]$, questo aiuta countingSort fornendo un massimo relativamente basso per l'allocazione di un array, che è di cardinalità max.

\newpage

![All Sorting Simple Gen (Lin Scale)](src/All-simple-lin.png){ height=225px }

![All Sorting Simple Gen (Log Scale)](src/All-simple-log.png){ height=225px }


Si può vedere che mergeSort viene superato in velocità da quickSort ma ha un andamento molto simile a quello di quickSort3Way.

E interessante osservare invece che countingSort, nonostante la complessità inferiore, fino ad array di circa 10.000 elementi risulti il più lento.
Inoltre la curva sembra quasi costante fino ad array di 100.000 elementi circa, questo ci fa pensare che il tempo impiegato per l’ordinamento sia quasi nullo rispetto al tempo di allocazione dell’array di supporto per tali valori.
In seguito studieremo perché questo fenomeno si verifica.

## Generazione per valori diversi

Valutiamo la complessità degli algoritmi quickSort e quickSort3Way insieme a mergeSort e countingSort sulla generazione di array per valori diversi.

Ci aspettiamo che gli andamenti di countingSort e mergeSort risultino costanti visto che la presenza di valori ripetuti non impatta il loro funzionamento.
Comunque countingSort dovrebbe risultare il migliore visto le performance osservate finora.

\newpage

![All Sorting Different Gen (Lin Scale)](src/All-different-lin.png){ height=225px }

![All Sorting Different Gen (Log Scale)](src/All-different-log.png){ height=225px }

Le nostre ipotesi sono confermate, inoltre notiamo che mergeSort per bassi valori di $d$ ha un comportamento medio tra quickSort e quickSort3Way.

Come ci si aspettava anche le performance di countingSort rimangono costanti.

\newpage

## Generazione array ordinati al contrario

Valutiamo la complessità di quickSort e sue varianti quickSort3Way e quickSortSelect insieme a mergeSort e countingSort su array ordinati in ordine decrescente.

Ci aspettiamo che mergeSort e countingSort e quickSortSelect mantengano lo stesso andamento che avevano avuto per l'esperimento con generazione semplice degli array, e che quindi risultino notevolmente migliori di quickSort e quickSort3Way

\newpage

![All Sorting Reverse Gen (Lin Scale)](src/All-reverse-lin.png){ height=225px }

![All Sorting Reverse Gen (Log Scale)](src/All-reverse-log.png){ height=225px }

> Nota: quickSort e quickSort3Way sono stati eseguiti solo fino a array di lunghezza inferiore per via del lungo tempo di esecuzione.

Notiamo un andamento particolare per countingSort.
Invece di comportarsi come per la generazione semplice, quindi rimanendo quasi costante con un piccolo picco alla fine, cresce linearmente come ci si aspetterebbe data la sua complessità $O(n)$.

\newpage

### Studio metodi di allocazione countingSort

Viste le inconsistenze riscontrate tra le performance di countingSort su generazione semplice e su generazione di array ordinati al contrario valutiamo due implementazioni leggermente differenti di countingSort.

Una che chiameremo con allocazione dinamica, che estrae il valore piu grande all'interno dell'array e alloca l'array di supporto in base al valore trovato:
```c
int getMax(int *arr, int n){
	int i = 0;
	int max = arr[0];
    
	for (i = 1; i < n; i++) {
    	if(arr[i] > max) {
        	max = arr[i];
    	}
	}

	return max;
}

void countingSort(int *arr, unsigned int n) {
	int i;

	int r = getMax(arr, n);

	int *occurr = (int *)malloc((r + 1) * sizeof(int));
	int *sorted = (int *)malloc(n * sizeof(int));
	...
```

Una che chiameremo allocazione statica, che alloca sempre un array di supporto di dimensione $range$:
```c
void countingSort(int *arr, unsigned int n) {
	int i;

	int range = range;

	int *occurr = (int *)malloc((range + 1) * sizeof(int));
	int *sorted = (int *)malloc(n * sizeof(int));
	...
```

In tutti gli esperimenti precedenti e stata usata l'allocazione dinamica.
Utilizziamo il sistema di allocazione statica come benchmark di peggiore performance possibile.

\newpage

#### Generazione Semplice

>

![Counting Comparison Simple (Lin Scale)](src/CountingComparison-simple-lin.png){ height=225px }


![Counting Comparison Simple (Log Scale)](src/CountingComparison-simple-log.png){ height=225px }

\newpage

#### Generazione array ordinati al contrario

>

![Counting Comparison Reverse (Lin Scale)](src/CountingComparison-reverse-lin.png){ height=225px }

![Counting Comparison Reverse (Log Scale)](src/CountingComparison-reverse-log.png){ height=225px }

Possiamo notare che su array ordinati al contrario l'allocazione dinamica fornisce performance di gran lunga migliori rispetto all'allocazione statica.
Questo per via del modo in cui vengono generati gli array.
Un array di lunghezza $n$ avra $n$ come valore massimo, quindi si dovra allocare spazio soltanto per $n$ interi, e non $range$ come per l'allocazione statica.

Per array ottenuti con generazione semplice invece il sistema di allocazione dinamica degenera in quello con allocazione statica, probabilmente causato da alcuni elementi scelti casualmente molto vicini a $range$ che costringono ad allocare molta piu memoria rispetto al caso medio.

Questo conferma che anomalie e inconsistenze nei tempi di esecuzione di countingSort sono causate dall'allocazione della memoria.
