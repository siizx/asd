#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int> &V, int a, int b)
{
    int c = V[a];
    V[a] = V[b];
    V[b] = c;
} // inserito V negli argomenti, e smesso di passarli come puntatori

int findPos(int n, vector<int> &V)
{
    int idx;
    // non serve un controllo per vedere se l'elemento esiste perche' so che gia che c'e'.
    for (int i = 0; i < V.size(); i++)
    {
        if (V[i] == n)
            idx = i;
    }
    return idx;
};

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
        // int pvt = mediana_pvtarr(V);
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

void printVect(const vector<int> &a)
{

    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    };
    cout << "\n"
         << endl;
}

int main()
{
    vector<int> V = {56, 260, 83, 41, 94, 50, 2, 77, 22, 1, 97, 113, 132};
    cout << "Ecco l'array: ";
    printVect(V);

    quickSortRandom(V);

    cout << "\nEcco il vector ordinato: ";
    printVect(V);
    cout << endl;

    return 0;
}