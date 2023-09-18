#include "tree-chsib.h"

using namespace tree;

/* Nota: nei commenti usiamo "albero" e "puntatore a un nodo" come sinonimi, scegliendo di volta in volta
la formulazione più adatta a dare la specifica di una funzione.
Dal punto di vista tecnico, usiamo sempre il tipo Tree sia quando operiamo su un albero, sia quando operiamo,
a livello concettuale, su un puntatore a un nodo dell'albero.
Questo approccio e' corretto in quanto un albero (o sottoalbero) è un puntatore a una struct di tipo treeNode:
un albero è identificato univocamente dal puntatore alla sua radice */

/*******************************************************************************************************/
// il nodo di un albero è caratterizzato dall'etichetta, il puntatore al primo figlio e il puntatore al prossimo fratello
// NON manteniamo il puntatore al padre, anche se sarebbe comodo per alcune funzioni (ma del tutto inutile per altre)
struct tree::treeNode
{
   Label label;
   treeNode *firstChild;
   treeNode *nextSibling;
};

/*******************************************************************************************************/
// isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
bool tree::isEmpty(const Tree &t)
{
   return t == emptyTree;
}

// struttura dati ausiliaria restituita da search, che ci restituisce
// il nodo cercato, il nodo che punta a esso (padre o fratello) e il padre
struct search_result
{
   Tree node;
   Tree pred;
   Tree parent;
};

// funzione ausiliaria per search
search_result search_aux(Tree t, const Label l, const Tree pred, const Tree parent)
{
   if (isEmpty(t))
      return {emptyTree, emptyTree, emptyTree};
   if (t->label == l)
      return {t, pred, parent};
   search_result res = search_aux(t->firstChild, l, t, t);
   if (res.node != emptyTree)
      return res;
   return search_aux(t->nextSibling, l, t, parent);
}

// cerca un nodo con etichetta l, restituisce predecessore e padre (il predecessore è il nodo che linka
// quello cercato, può essere il padre o il fratello precedente)
search_result search(treeNode *t, const Label l)
{
   return search_aux(t, l, emptyTree, emptyTree);
}

/*******************************************************************************************************/

/* restituisce il puntatore al nodo che si trova in t ed ha come
etichetta l */
Tree getNode(const Label l, const Tree &t)
{
   /* se t è vuoto o l'etichetta è vuota restituisco emptyTree */
   if (isEmpty(t) || l == emptyLabel)
      return emptyTree;
   /* se l'etichetta di t è quella cercata, restituisco t */
   if (t->label == l)
      return t;
   /* ...chiamata ricorsiva di getNode su ciascuno dei figli di t,
   finché una delle chiamate non restituisce un valore diverso da
   emptyTree.... Rispetto alla visita esaustiva vista prima, la getNode non
   deve per forza esplorare tutto l'albero: quando una delle chiamate
   restituisce un albero != emptyTree, si deve fare return di tale albero
   non vuoto interrompendo la scansione dei fratelli */
   if (t->firstChild != emptyTree)
   {
      Tree auxt = t->firstChild;
      while (auxt != emptyTree && auxt->label != l)
      {
         getNode(l, auxt);
         auxt = auxt->nextSibling;
      }
   }
   return emptyTree;
}

/*******************************************************************************************************/
// addElem aggiunge il nodo etichettato con labelOfNodeToAdd come
// figlio del nodo etichettato con labelOfNodeInTree.
// Caso particolare: aggiunta della radice, che si ottiene
// con labelOfNodeInTree uguale a emptyLabel (= nessun padre), e ha successo
// solo se l'albero e' vuoto (in caso contrario restituisce FAIL
// e non aggiunge nulla).
// Restituisce FAIL se non esiste un nodo nell'albero etichettato
// con labelOfNodeInTree oppure se nell'albero esiste gia' un nodo
// etichettato con labelOfNodeToAdd; aggiunge e restituisce OK altrimenti
Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree &t)
{
   if (isEmpty(t))
   {
      t = createEmpty();
      t->label = labelOfNodeToAdd;
      return OK;
   }
   else if (member(labelOfNodeToAdd, t))
      return FAIL;
   Tree auxT = getNode(labelOfNodeInTree, t); /* recupero il puntatore al nodo
dell'albero che ha etichetta labelOfNodeInTree */
   if (auxT == emptyTree)
   // return FAIL;
   /* nell'albero non esiste un nodo con etichetta
      labelOfNodeInTree, restituisco FAIL */
   // else            /* ho trovato il nodo auxT a cui aggiungere il figlio */
   {
      /* creo il figlio con etichetta labelOfNodeToAdd e lo aggiungo a auxT. Può
      essere una buona idea implementare una funzione ausiliaria che crea il nodo e
      ne restituisce il puntatore */
      Tree newtree = createEmpty();
      newtree->label = labelOfNodeToAdd;
      if (auxT->firstChild == emptyTree)
         auxT->firstChild = newtree;
      else
      {
         auxT = auxT->firstChild;
         while (auxT->nextSibling != emptyTree)
         {
            auxT = auxT->nextSibling;
         }
         auxT->nextSibling = newtree;
      }
   }
   return OK;
}

/*******************************************************************************************************/
// deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
// e collega al padre di tale nodo tutti i suoi figli
// Restituisce FAIL se si tenta di cancellare la radice e questa ha
// dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste
// un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti
Error tree::deleteElemI(const Label l, Tree &t)
{
   return FAIL;
}

/*******************************************************************************************************/
// deleteElem (versione ricorsiva): stesso comportamento della versione iterativa, ma implementata ricorsivamente
// (può anche non essere ricorsiva la deleteElemR, ma deve fare uso di funzioni ausiliarie ricorsive)
Error tree::deleteElemR(const Label l, Tree &t)
{
   return FAIL;
}

/*******************************************************************************************************/
// father restituisce l'etichetta del padre del nodo con etichetta l se il nodo esiste nell'albero
// (o sottoalbero) t e se il padre esiste.
// Restituisce la costante emptyLabel altrimenti
Label tree::father(const Label l, const Tree &t)
{

   return emptyLabel;
}

/*******************************************************************************************************/
// children restituisce una lista di Label, contenente le etichette
// di tutti i figli nell'albero t del nodo etichettato con l
// La lista può essere implementata usando una qualunque delle strutture dati viste a lezione
// (non un Vector!!!): si riusi una implementazione del TDD list, adattandola
// a elementi di tipo string (nelle precedenti esercitazioni gli elementi erano int)
list::List tree::children(const Label l, const Tree &t)
{
   list::List lst = list::createEmpty();
   Tree auxt = t;
   if (isEmpty(auxt->firstChild) || isEmpty(auxt))
      return lst;
   auxt = auxt->firstChild;
   while (auxt->label != emptyLabel)
   {
      addBack(auxt->label, lst);
      auxt = auxt->nextSibling;
   }
   return lst;
}

/*******************************************************************************************************/
// degree restituisce il numero di archi uscenti dal nodo etichettato con l; restituisce -1 se non esiste
// nessuna etichetta l nell'albero
int tree::degree(const Label l, const Tree &t)
{
   if (isEmpty(t))
      return -1;
   Tree auxt = getNode(l, t);
   list::List bimbi = children(l, auxt);
   int deg = size(bimbi);

   return deg;
}

/*******************************************************************************************************/
// ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
// (può anche non essere ricorsiva la ancestorsR, ma deve fare uso di funzioni ausiliarie ricorsive)
list::List tree::ancestorsR(const Label l, const Tree &t)
{
   list::List lst = list::createEmpty();
   return lst;
}

/*******************************************************************************************************/
// ancestors (versione iterativa) restituisce una lista di Label, contenente le etichette
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
list::List tree::ancestorsI(const Label l, const Tree &t)
{
   list::List lst = list::createEmpty();
   return lst;
}

/*******************************************************************************************************/
// leastCommonAncestor restituisce l'etichetta del minimo antenato comune
// ai nodi etichettati con label1 e label2
Label tree::leastCommonAncestor(const Label label1, const Label label2, const Tree &t)
{
   return emptyLabel;
}

/*******************************************************************************************************/
// member restituisce true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
bool tree::member(const Label l, const Tree &t)
{
   Tree member = getNode(l, t);

   if (member != emptyTree)
      return true;

   return false;
}

/*******************************************************************************************************/
// numNodes restituisce il numero di nodi nell'albero t mediante una visita ricorsiva in depthfirst
int tree::numNodes(const Tree &t)
{
   return -1;
}

/*******************************************************************************************************/
// createEmptyTree restituisce l'albero vuoto
Tree tree::createEmpty()
{
   Tree p = new treeNode;
   p->firstChild = emptyTree;
   p->label = emptyLabel;
   p->nextSibling = emptyTree;
   return p;
}

/*******************************************************************************************************/
// Visualizzazione possibilmente strutturata come visto a lezione
// unsigned int c = 0;
void printTree(const Tree &t)
{
   /* se l'albero e' vuoto non c'é niente da visitare */
   if (isEmpty(t))
      return;
   /* ...dovrò fare qualche operazione op(t) su t: potrebbe essere la stampa
   dell'etichetta di t, il confronto dell'etichetta di t con un'etichetta che
   stiamo cercando, la verifica di qualche altra proprietà di t o dei suoi
   figli, etc... . E' l'operazione che nel testo viene indicata con “visita
   di t”... */
   cout << t->label << "\n";
   /* Chiamata ricorsiva di visit su ciascuno dei figli di t, partendo dal
   primo figlio e poi scorrendo la lista dei suoi fratelli */
   Tree auxT = t->firstChild;

   while (!isEmpty(auxT))
   {
      printTree(auxT);
      auxT = auxT->nextSibling;
   }
   return;
}

/****************************************************************/
// Questa funzione NON richiede di conoscere come e' fatta la struttura dati che implementa l'albero: usa solo addElem e quindi e' ad
// un alto livello di astrazione
// Vantaggi: codice compatto, leggibile, riutilizzabile per qualunque implementazione del TDD Tree
// Svantaggi: inefficiente: la addElem cerca ogni volta il nodo con etichetta fatherLabel, mentre basterebbe una chiamata sola per
// trovarlo e poi si potrebbero attaccare tutti i figli a esso, senza ripetere la dispendiosa ricerca nell'albero; per renderla
// efficiente dovrei pero' accedere direttamente alla struttura dati chiamando qualche funzione ausiliaria che operi
// sui nodi dell'albero, rinunciando a scrivere codice modulare, chiaro e ad un ragionevole livello di astrazione...
// Non esiste un'opzione migliore tra le due: se il codice deve essere efficiente, è opportuno scrivere una funzione ad hoc per
// una determinata implementazione; se il codice deve essere riutilizzabile, bisogna limitarsi a usare le funzioni offerte dall'
// interfaccia del TDD in modo che la funzione continui ad andare bene anche se cambia l'implementazione
Tree readFromStream(istream &str)
{
   Tree t = createEmpty();
   string line;
   Label rootLabel, fatherLabel, childLabel;
   getline(str, line);
   istringstream instream; // uso una variabile di tipo istringstream per poter scandire i pezzi di ogni riga usando >>
   instream.clear();
   instream.str(line);
   instream >> rootLabel;             // il primo elemento che si incontra nel file e' l'etichetta della radice, per convenzione su come deve essere fatto il file
   addElem(emptyLabel, rootLabel, t); // la si inserisce nell'albero vuoto, indicando che il padre non c'e' (primo argomento emptyLabel)
   getline(str, line);                // poi si iniziano a scansionare le righe seguenti
   instream.clear();
   instream.str(line);
   while (!str.eof())
   {
      instream >> fatherLabel; // in ogni riga del file, il primo elemento e' l'etichetta del nodo padre e gli altri sono le etichette dei figli
      normalize(fatherLabel);  // normalizzo l'etichetta del padre
      while (!instream.eof())  // finche' la riga corrente non e' terminata
      {
         instream >> childLabel;              // leggo la prossima etichetta
         normalize(childLabel);               // la normalizzo
         addElem(fatherLabel, childLabel, t); // e la attacco al padre
      }
      getline(str, line);
      instream.clear();
      instream.str(line);
   }
   str.clear();
   return t;
}

/****************************************************************/
Tree readFromFile(string nome_file)
{
   ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
   if (!ifs)
   {
      cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n";
      return createEmpty();
   }
   return readFromStream(ifs);
}
