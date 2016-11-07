# Graph
UNIMIB - Programmazione e Amministrazione di Sistema A.A. 2015/2016
Implementazione di un grafo non orientato in C++

Il  progetto  richiede  la  progettazione  e  realizzazione  di  una  classe  generica  che implementa un grafo (non orientato).
Un  grafo è costituito da  un  insieme di nodi e archi. 
I  nodi  sono  rappresentati  da  un  generico  identificativo  (es.  un  numero,  una stringa,  una  classe,  ecc...). 
Gli  archi  mettono  in relazione  due  nodi  creando  un collegamento tra loro.
A parte i metodi essenziali per la classe (tra cui conoscere il numero di nodi e archi), devono essere implementate le seguenti funzionalità:

1.La  classe  deve  includere  il  supporto  al  solo const_iterator  di  tipo  forward  sui nodi. 
  L’iteratore  itera  sull’insieme  dei  nodi  contenuti  nel  grafo  e  l’ordine  con  cui vengono ritornati non è rilevante.
  
2.Deve essere possibile aggiungere e rimuovere nodi e archi.
  Gestire  i casi  in cui  i nodi o gli archi già esistano o si tenti di aggiungere un arco su nodi non esistenti

3.Implementare  un  metodo neighbors  che,  dato  un  nodo,  stampa  a  schermo l’insieme  dei  nodi  immediatamente  raggiungibili  da esso attraverso  un  arco. L'ordine  con cui sono ritornati i nodi non è rilevante.

4.Deve essere possibile interrogare il grafo per sapere se esite un nodo tramite un metodo exists e se una coppia di nodi è connessa da un
  arco tramite un metodo hasEdge.  

Possono  essere  trascurate  considerazioni  di  efficienza  di  accesso  ai  dati  e  di occupazione di memoria.
Utilizzare dove opportuno la gestione delle eccezioni e i funtori.
