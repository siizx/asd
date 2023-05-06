#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 100; // Maximum number of elements in the arrays

int main()
{
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {3, 4, 5, 6, 7};

    int maxElement = 0;

    // trovo il massimo di arr1
    for (int i = 0; i < arr1.size(); i++)
    {
        maxElement = max(maxElement, arr1[i]);
    }

    // trovo il massimo di arr2
    for (int i = 0; i < arr2.size(); i++)
    {
        maxElement = max(maxElement, arr2[i]);
    }

    cout << "Max element: " << maxElement << endl;

    // creo un array booleano per tracciare i valori di arr1. inizializzo con zero
    bool inArr1[MAX_N] = {false};

    // "i" e' l'indice dell'arr1, ma "arr1[i]" (cioe' il valore di "arr1" preso con indice "i") e' indice di "inArr1".
    // iterando in questo modo, trasformiamo in "true" solo gli indici (valori in arr1), lasciando in "false" gli altri.
    for (int i = 0; i < arr1.size(); i++)
    {
        inArr1[arr1[i]] = true;
    }

    // creo un vector per salvare l'intersezione dei 2 insiemi (vectors)
    vector<int> intersection;

    for (int i = 0; i < arr2.size(); i++)
    {
        if (inArr1[arr2[i]]) // QUA sfruttiamo il fatto che inArr1 sia un vector di booleani in un modo molto efficiente !!
        {
            intersection.push_back(arr2[i]);
        }
    }

    // semplice print di intersection, ma in un  modo che non avevo mai visto.
    cout << "Intersection: ";
    for (int i : intersection)
    {
        cout << i << " ";
    }
    cout << endl;

    // creo un ulteriore array booleano per l'unione dei due set.
    bool inUnion[MAX_N] = {false};

    // itero i due set, trasformando in "true" tutti i valori di arr1 e arr2 (arrN[i] = valore / indice per inUnion)
    for (int i = 0; i < arr1.size(); i++)
    {
        inUnion[arr1[i]] = true;
    }
    for (int i = 0; i < arr2.size(); i++)
    {
        inUnion[arr2[i]] = true;
    }

    vector<int> unionSet;
    for (int i = 0; i <= maxElement; i++)
    {
        if (inUnion[i])
        {
            unionSet.push_back(i);
        }
    }

    cout << "Union: ";
    for (int i : unionSet)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "Union bool vector: " << endl;

    for (int i = 0; i < 11; i++)
    {
        cout << inUnion[i];
    }

    cout << endl;

    return 0;
}
