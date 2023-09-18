#include "stack-ptr.h"

using namespace stack;

struct stack::cell
{
    Elem elem;
    cell *next;
};

/****************************************************************/
bool stack::isEmpty(const Stack &s)
{

    return s == EMPTYSTACK;
}

/****************************************************************/
void stack::push(const Elem x, Stack &s)
{
    Stack N = new cell;
    N->elem = x;
    N->next = s;
    s = N;
    return;
}

/****************************************************************/
Elem stack::pop(Stack &s)
{
    if (isEmpty(s))
        return EMPTYELEM;

    int e = s->elem;
    Stack C = s;
    s = C->next;
    delete C;
    return e;
}

/****************************************************************/
Elem stack::top(Stack &s)
{
    if (isEmpty(s))
        return EMPTYELEM;
    return s->elem;
}

Stack readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}

Stack readFromStdin()
{
    cout << endl
         << "inserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT
         << " per terminare" << endl;
    return readFromStream((std::cin));
}

Stack readFromStream(istream &is)
{
    Stack s = EMPTYSTACK;
    Elem e;
    while (is >> e)
    {
        if (e == FINEINPUT) // il segnale di fine input nel file è il numero FINEINPUT
            return s;
        push(e, s);
    }
    throw runtime_error("errore inserimento dati");
}

void print(const Stack &s)
{
    cell *c = s;
    while (c != EMPTYSTACK)
    {
        cout << c->elem << "; ";
        c = c->next;
    }
    cout << endl;
}
