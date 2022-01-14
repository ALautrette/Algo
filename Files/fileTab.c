#include <stdio.h>
#include <stdlib.h>

typedef struct file
{
    int *tab;
    int debut;
    int fin;
    int taille;
} file;

void enfile(file *, int);
int defile(file *);
void afficheFile(file);

int main()
{
    file f;
    f.taille = 5;
    f.tab = (int *)malloc(sizeof(int) * f.taille);
    f.debut = 0;
    f.fin = 0;
    defile(&f);
    for(int i = 0; i < 7; i++){
        enfile(&f, i);
    }
    // enfile(&f, 1);
    // defile(&f);
    // enfile(&f, 2);
    // enfile(&f, 3);
    // enfile(&f, 4);
    // enfile(&f, 5);
    // defile(&f);
    // enfile(&f, 1);
    // defile(&f);
    afficheFile(f);
    return 0;
}

int defile(file *f)
{
    if (f->debut == f->fin)
    {
        printf("Impossible de defiler une file vide\n");
        return 0;
    }
    return f->tab[f->debut++ % f->taille];
}

void enfile(file *f, int e)
{
    if ((f->fin - f->debut) < f->taille)
    {
        f->tab[f->fin % f->taille] = e;
        f->fin += 1;
    }
    else
    {
        printf("La file est pleine\n");
    }
}

void afficheFile(file f)
{
    for (int i = f.debut; i < f.fin; i++)
    {
        printf("%d ", f.tab[i % f.taille]);
    }
}
