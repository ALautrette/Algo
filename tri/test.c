#include <stdio.h>
#include <stdlib.h>

int indexOf(int *, int, int);
void afficheTab(int *, int);
void triInsert(int *, int);
void triSelect(int *, int);
int dicho(int *, int, int);

void triFusion(int *, int);
void fusion(int *, int, int *, int);

void genereTab(int *, int);

void affficheProduitMatrice(int *, int, int, int *, int, int);

struct test
{
    int a;
    float b;
};


int main(int argc, char *argv[])
{
    int find = 11;
    int tab[9] = {5, 8, 3, 6, 7, 2, 1, 6, 12};
    struct test essai, *ptr;
    essai.a = 2;
    essai.b = 3.0; 
    ptr = &essai;
    ptr->a = 3; 
    // genereTab(tab, 10);
    // afficheTab(tab, 10);
    // printf("\n");
    // triFusion(tab, 10);
    // printf("Tri fusion\n");
    // afficheTab(tab, 10);

    return 0;
}

//lx = nombre de lignes
//cx = nombre de colonnes
void affficheProduitMatrice(int *m1, int l1, int c1, int *m2, int l2, int c2)
{

//Ce qui est fait ici est éclaté au sol
    if (l2 != c1)
    {
        printf("Multiplication non compatible");
    }
    else
    {
        int tab[50];
        int somme;
        // int i, j;
        for (int i = 0; i < l1; i++)
        {
            somme = 0;
            for (int j = 0; i < c1; j++)
            {
                somme += m1[i*c1 + j] * m2[j*c2 + i]; 
            }
        }
    }
}

void genereTab(int *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 50;
    }
}

void triFusion(int *tab, int n)
{
    if (n > 1)
    {
        triFusion(tab, n / 2);
        triFusion(&tab[n / 2], n - (n / 2));
        fusion(tab, n / 2, &tab[n / 2], n - (n / 2));
    }
}

void fusion(int *tab1, int n1, int *tab2, int n2)
{
    int tabUn[50], tabDeux[50];

    for (int i = 0; i < n1; i++)
    {
        tabUn[i] = tab1[i];
    }

    for (int j = 0; j < n2; j++)
    {
        tabDeux[j] = tab2[j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = 0;

    while (i < n1 && j < n2)
    {
        if (tabUn[i] <= tabDeux[j])
        {
            tab1[k] = tabUn[i];
            i++;
        }
        else
        {
            tab1[k] = tabDeux[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        tab1[k] = tabUn[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        tab1[k] = tabDeux[j];
        j++;
        k++;
    }
}

int dicho(int *tab, int find, int n)
{
    int d, f, m;
    d = 0;
    f = n;
    m = (d + f) / 2;
    while (tab[m] != find && d < f)
    {
        if (tab[m] < find)
        {
            d = m + 1;
        }
        else
        {
            f = m - 1;
        }
        m = (d + f) / 2;
    }
    if (tab[m] == find)
    {

        return m;
    }
    else
    {

        return -1;
    }
}

void triInsert(int *tab, int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        int y = i + 1;
        while (y > 0 && tab[y] < tab[y - 1])
        {
            temp = tab[y];
            tab[y] = tab[y - 1];
            tab[y - 1] = temp;
            y--;
        }
    }
    printf("Trié par insertion\n");
}

void triSelect(int *tab, int n)
{
    int temp, min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int y = i; y < n; y++)
        {
            if (tab[min] > tab[y])
            {
                min = y;
            }
        }
        temp = tab[min];
        tab[min] = tab[i];
        tab[i] = temp;
    }

    printf("Trié par séléction\n");
}

int indexOf(int *tab, int find, int n)
{
    int i = 0;
    while (i < n && tab[i] != find)
    {
        i++;
    }
    if (tab[i] == find)
    {

        return i;
    }

    return -1;
}

void afficheTab(int *tab, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", tab[i]);
        if (i != n - 1)
        {
            printf(", ");
        }
    }
    printf("]");
}