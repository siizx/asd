#include "queue-array.h"

using namespace queue;

/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
Queue queue::createEmpty()
{
   Queue q;
   q.maxsize = BLOCKDIM;
   q.queue = new Elem[q.maxsize];
   q.size = 0;
   return q;
}

/****************************************************************/
void queue::enqueue(Elem e, Queue &l) // aggiunge e in coda
{
   l.size++;
   l.queue[l.size - 1] = e;
   return;
}

/****************************************************************/
Elem queue::dequeue(Queue &l) // rimuove il primo elemento e lo restituisce
{
   if (isEmpty(l))
      return EMPTYELEM;

   unsigned int C = 0;
   while (l.queue[C] == EMPTYELEM)
      C++;
   Elem d = l.queue[C];
   l.queue[C] = EMPTYELEM;
   l.size--;

   return d;
}

/****************************************************************/
Elem queue::first(Queue &l) // restituisce il primo elemento
{
   if (isEmpty(l))
      return EMPTYELEM;

   unsigned int C = 0;
   while (l.queue[C] == EMPTYELEM)
      C++;

   return l.queue[C];
}

/****************************************************************/
bool queue::isEmpty(const Queue &l)
{
   return l.size == 0;
}

/****************************************************************/
Queue readFromFile(string nome_file)
{
   ifstream ifs(nome_file.c_str()); // stream associato a un file, in lettura
   return readFromStream(ifs);
}

Queue readFromStdin()
{
   cout << endl
        << "inserire una sequenza di numeri separati da spazi seguiti da "
        << FINEINPUT << " per terminare" << endl;
   return readFromStream((std::cin));
}

Queue readFromStream(istream &is)
{
   Queue l = createEmpty();
   Elem e;
   while (is >> e)
   {
      if (e == FINEINPUT) // il segnale di fine input è FINEINPUT
         return l;
      enqueue(e, l);
   }
   throw runtime_error("errore inserimento dati");
}

void print(const Queue &l)
{
   for (int i = 0; i < l.size; ++i)
      cout << l.queue[i] << "; ";
   cout << endl;
}
