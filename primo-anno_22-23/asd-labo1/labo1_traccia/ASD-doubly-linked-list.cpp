// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

#include "ASD-doubly-linked-list.h"

using namespace list;

struct list::node
{ // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream &str, List &l)
{
    createEmpty(l);
    Elem e;
    str >> e;
    if (!str)
        throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != FINEINPUT)
    {
        addRear(e, l); // aggiunge l'elemento alla fine della lista
        str >> e;
        if (!str)
            throw runtime_error("Errore inserimento dati\n");
    }
}

/* legge il contenuto di una lista da file */
void readFromFile(string nome_file, List &l)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}

/* legge il contenuto di una lista da standard input */
void readFromStdin(List &l)
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const List &l)
{
    List q = l->next; // q "salta la sentinella" e va alla testa della lista
    while (q != l)
    { // avanza finche' non finisce la lista
        cout << q->info << "; ";
        q = q->next;
    }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

/* crea la lista vuota */
void list::createEmpty(List &l)
{
    l = new node;
    l->info = EMPTYELEM;
    l->next = l;
    l->prev = l;
}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List &l)
{
    return l->next == l;
}

/* restituisce la dimensione della lista */
int list::size(const List &l)
{
    if (list::isEmpty(l))
        return 0; // se la lista e' vuota return 0.

    int counter = 0;
    List auxptr = l->next;
    while (auxptr != l)
    {
        auxptr = auxptr->next;
        counter++;
    }
    return counter;
}

/* "smantella" la lista svuotandola */
void list::clear(const List &l)
{
    if (list::isEmpty(l))
        return; // se la lista e' vuota, return...
    List curr = l->next;
    List prev;
    while (curr != l)
    {
        curr = curr->next;
        prev = curr->prev;
        delete prev;
    }

    l->next = l;
    l->prev = l;
}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento
che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
Elem list::get(int pos, const List &l)
{

    if (pos >= size(l) || pos < 0)
        return EMPTYELEM;

    List auxPtr = l->next;
    for (int i = 0; i < pos; i++)
    {
        auxPtr = auxPtr->next;
    }
    return auxPtr->info;
}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, Elem e, const List &l)
{
    if (list::isEmpty(l))
        return;
    if (pos == 0)
    {
        l->next->info = e;
        return;
    }
    if (pos == size(l) - 1)
    {
        l->prev->info = e;
        return;
    }

    List auxPtr = l->next; // puntatore ausiliario

    for (int i = 0; i < pos; i++)
    {
        auxPtr = auxPtr->next;
        if (auxPtr == l)
            return; // questo if l'ho messo perche itero sulla lista, ma siccome si tratta di una lista circolare, se il ptr ritorna sul punto iniziale (l), allora la posizione eccede il numero di elementi nella lista.
        else if (i == pos - 1)
            auxPtr->info = e;
    }
    return;
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, Elem e, const List &l)
{

    if (pos < 0 || pos > size(l) || list::isEmpty(l))
        return;
    else if (pos == size(l))
        addRear(e, l);
    else if (pos == 0)
        addFront(e, l);
    else
    {

        List auxPtr = l; // puntatore ausiliario

        for (int i = 0; i <= pos; i++)
        {
            auxPtr = auxPtr->next;
        }

        List a = new node;
        a->info = e;

        a->next = auxPtr;
        a->prev = auxPtr->prev;
        auxPtr->prev->next = a;
        auxPtr->next->prev = a;
    }

    return;
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e, const List &l)
{

    List toADD = new node;
    toADD->info = e;
    // aggiusto i puntatori
    l->prev->next = toADD;
    toADD->prev = l->prev;
    toADD->next = l;
    l->prev = toADD;

    return;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List &l)
{

    List toADD = new node;
    toADD->info = e;
    // aggiusto i puntatori

    l->next->prev = toADD;
    toADD->next = l->next;
    toADD->prev = l;
    l->next = toADD;
    return;
}

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const List &l)
{

    if (pos >= size(l))
        return;
    else if (pos == 0)
    {
        List t = l->next;
        l->next->next->prev = l;
        l->next = t->next;

        delete t;
    }
    else
    {

        List auxPtr = l; // puntatore ausiliario

        for (int i = 0; i <= pos; i++)
        {
            auxPtr = auxPtr->next;
        }

        List w = auxPtr->prev;
        w->next = auxPtr->next;

        auxPtr->next->prev = w;

        delete auxPtr;
    }

    return;
}

/* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(Elem e, const List &l)
{
    if (isEmpty(l))
        return;
    else
    {
        List pp = l->next;
        while (pp != l)
        {
            if (pp->info == e)
            {
                List w = pp->prev;
                w->next = pp->next;

                pp->next->prev = w;
                w = pp;
                pp = pp->next;

                delete w;
            }
            else
                pp = pp->next;
        }
    }

    return;
}
