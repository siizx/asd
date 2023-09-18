// g++ dictionary-main.cpp dictionary-bst.cpp string-utility.cpp

#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

Dictionary emptyNode = NULL;
Dictionary emptyDictionary = NULL;

struct dict::bstNode
{
    Elem elem;
    bstNode *leftChild;
    bstNode *rightChild;
};

/****************************************************************/

bool isEmpty(const Dictionary &d)
{
    return d == emptyDictionary;
}

/****************************************************************/

Dictionary dict::createEmptyDict()
{
    return emptyDictionary;
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna OK se la chiave non esisteva già e se l'inserimento  */
/* ha avuto successo.							    */
/* Ritorna FAIL se la chiave esisteva già o se l'inserimento    */
/* non ha avuto successo.
/****************************************************************/
Error dict::insertElem(const Key k, const Value v, Dictionary &d)
{
    if (isEmpty(d))
    {
        bstNode *newNode = new bstNode;
        newNode->elem.key = k;
        newNode->elem.value = v;
        newNode->leftChild = emptyNode;
        newNode->rightChild = emptyNode;
        d = newNode;
        return OK;
    }
    if (d->elem.key == k)
        return FAIL;

    if (d->elem.key > k)
        return insertElem(k, v, d->leftChild);
    else
        return insertElem(k, v, d->rightChild);
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna il Value v associato alla Key k, se questa esiste    */
/* Ritorna emptyValue altrimenti					    */
/****************************************************************/
Value dict::search(const Key k, const Dictionary &d)
{
    if (isEmpty(d))
        return emptyValue;
    if (d->elem.key == k)
        return d->elem.value;

    if (d->elem.key > k)
        return search(k, d->leftChild);
    else
        return search(k, d->rightChild);
}

/****************************************************************/

Elem deleteMin(Dictionary &d)
{
    if (d->leftChild == emptyNode)
    {
        Elem tmpElem = d->elem;
        Dictionary tmpNode = d->rightChild;
        delete d;
        d = tmpNode;
        return tmpElem;
    }
    else
        return deleteMin(d->leftChild);
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna OK se la chiave esiste nel dizionario e se la 	    */
/* cancellazione ha avuto successo					    */
/* Ritorna FAIL se la chiave non esisteva nel dizionaio o se la */
/* cancellazione non ha avuto successo				    */
/****************************************************************/
Error dict::deleteElem(const Key k, Dictionary &d)
{
    if (isEmpty(d))
        return FAIL;
    if (k == d->elem.key)
    {
        // case1
        if (d->rightChild == emptyNode && d->leftChild == emptyNode)
        {
            delete d;
            d = emptyNode;
        } // case 2
        else if (d->leftChild == emptyDictionary)
        {
            Dictionary tmpNode = d->rightChild;

            delete d;
            d = tmpNode;
            return OK;
        } // case 3
        else if (d->rightChild == emptyDictionary)
        {
            Dictionary tmpNode = d->leftChild;

            delete d;
            d = tmpNode;
            return OK;
        }
        // caso 4
        else
            d->elem = deleteMin(d->leftChild);

        return OK;
    }

    if (d->elem.key > k)
        return deleteElem(k, d->leftChild);
    else
        return deleteElem(k, d->rightChild);
}

/****************************************************************/

void print(const Dictionary &d)
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
    if (isEmpty(d))
        return;
    if (d->leftChild != emptyNode)
        print(d->leftChild);
    cout << d->elem.key << ": " << d->elem.value << "\n";
    if (d->rightChild != emptyNode)
        print(d->rightChild);
}

/****************************************************************/
Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs)
    {
        cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n";
        return createEmptyDict();
    }
    return readFromStream(ifs);
}

/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
    // Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}

/****************************************************************/
Dictionary readFromStream(istream &str)
{
    Dictionary d = createEmptyDict();
    string key, kcopy;
    string value;
    getline(str, key, ':');
    getline(str, value);
    while (!str.eof())
    {
        kcopy = key;
        removeBlanksAndLower(kcopy);
        insertElem(kcopy, value, d); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline(str, key, ':');
        getline(str, value);
    }
    str.clear();
    return d;
}
