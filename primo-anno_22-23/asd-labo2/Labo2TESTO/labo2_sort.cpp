#include "labo2_sort.h"

void scambia(vector<int> &v, int i, int j)
{
    int tmp = v[j];
    v[j] = v[i];
    v[i] = tmp;
}

/**************************************************************************************
                SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int> &v)
{
    int current_min_index;
    unsigned int size = v.size();
    for (unsigned int i = 0; i < size; ++i)
    {
        current_min_index = i;
        for (unsigned int j = i + 1; j < size; ++j)
            if (v[current_min_index] > v[j])
                current_min_index = j;
        scambia(v, i, current_min_index);
    }
}

/**************************************************************************************
                INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int> &v)
{
    int current, prev;
    unsigned int size = v.size();
    for (unsigned int i = 1; i < size; ++i)
    {
        current = i;
        prev = i - 1;
        while (prev >= 0 && v[current] < v[prev])
        {
            scambia(v, current, prev);
            --current;
            --prev;
        }
    }
}

/**************************************************************************************
                BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int> &v)
{
    unsigned int size = v.size();
    bool scambiati;
    for (unsigned int i = 1; i < size; ++i)
    {
        scambiati = false;
        for (unsigned int j = 0; j < size - i; ++j)
            if (v[j] > v[j + 1])
            {
                scambia(v, j, j + 1);
                scambiati = true;
            }
        if (!scambiati)
            return;
    }
}

/**************************************************************************************
                   MERGESORT
***************************************************************************************/
void fondi(vector<int> &v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
    vector<int> vsinistra, vdestra;

    for (unsigned int i = inizio; i <= centro; ++i)
        vsinistra.push_back(v[i]);

    for (unsigned int i = centro + 1; i <= fine; ++i)
        vdestra.push_back(v[i]);

    unsigned int indicesinistra = 0;
    unsigned int maxsin = vsinistra.size();
    unsigned int indicedestra = 0;
    unsigned int maxdes = vdestra.size();

    for (unsigned int i = inizio; i <= fine; ++i)
    {
        if (indicesinistra < maxsin && indicedestra < maxdes)
        {
            if (vsinistra[indicesinistra] < vdestra[indicedestra])
            {
                v[i] = vsinistra[indicesinistra];
                indicesinistra++;
                continue;
            }
            else
            {
                v[i] = vdestra[indicedestra];
                indicedestra++;
                continue;
            }
        }

        if (indicesinistra == maxsin && indicedestra < maxdes)
        {
            v[i] = vdestra[indicedestra];
            indicedestra++;
            continue;
        }

        if (indicedestra == maxdes && indicesinistra < maxsin)
        {
            v[i] = vsinistra[indicesinistra];
            indicesinistra++;
            continue;
        }
    }
}

void ms(vector<int> &v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
    {
        unsigned int centro = (inizio + fine) / 2;
        ms(v, inizio, centro);
        ms(v, centro + 1, fine);
        fondi(v, inizio, centro, fine);
    }
}

void mergeSort(vector<int> &v)
{
    if (v.size() != 0)
        ms(v, 0, v.size() - 1);
}

/**************************************************************************************
                QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/

void swap(vector<int> &V, int a, int b)
{
    int c = V[a];
    V[a] = V[b];
    V[b] = c;
}

int findPos(int n, vector<int> &V)
{
    int idx = -1;
    // non serve un controllo per vedere se l'elemento esiste perche' so che gia che c'e'.
    for (int i = 0; i < V.size(); i++)
    {
        if (V[i] == n)
            idx = i;
    }
    return idx;
};

// ordino i 3 elementi presi per fare la mediana.
int mediana_pvtarr(vector<int> &V, int inizio, int fine)
{
    int middle = (inizio + fine) / 2;

    if (V[inizio] > V[middle])
        swap(V[inizio], V[middle]);
    if (V[middle] > V[fine])
        swap(V[middle], V[fine]);
    if (V[inizio] > V[middle])
        swap(V[inizio], V[middle]);

    return V[middle];
};

int partition_in_place(vector<int> &V, int inizio, int fine)
{
    int med = mediana_pvtarr(V, inizio, fine);
    int pivot_index = findPos(med, V);
    int p = V[pivot_index];
    int i = inizio + 1;

    swap(V[pivot_index], V[inizio]);

    for (int j = inizio + 1; j <= fine; j++)
    {
        if (V[j] < p)
        {
            swap(V[j], V[i]);
            i++;
        }
    }
    swap(V[inizio], V[i - 1]);
    return i - 1;
}

void qs(vector<int> &V, int inizio, int fine)
{
    if (inizio < fine)
    {
        int pivot_index = partition_in_place(V, inizio, fine);

        qs(V, inizio, pivot_index - 1);
        qs(V, pivot_index + 1, fine);
    };
    return;
};

void quickSortTrivial(vector<int> &V)
{
    qs(V, 0, V.size() - 1);
}

/**************************************************************************************
                QUICKSORT RANDOMIZZATO
***************************************************************************************/

int partition_in_place2(vector<int> &V, int inizio, int fine)
{
    int pivot_index = inizio + rand() % (fine - inizio + 1);
    int p = V[pivot_index];
    int i = inizio + 1;

    swap(V[pivot_index], V[inizio]);

    for (int j = inizio + 1; j <= fine; j++)
    {
        if (V[j] < p)
        {
            swap(V[j], V[i]);
            i++;
        }
    }
    swap(V[inizio], V[i - 1]);
    return i - 1;
}

void qs2(vector<int> &V, int inizio, int fine)
{
    if (inizio < fine)
    {
        int pivot_index = partition_in_place2(V, inizio, fine);

        qs2(V, inizio, pivot_index - 1);
        qs2(V, pivot_index + 1, fine);
    };
    return;
};

void quickSortRandom(vector<int> &V)
{
    qs2(V, 0, V.size() - 1);
}
