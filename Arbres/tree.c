#include <stdio.h>

typedef struct noeud
{
    int val;
    struct noeud *fg, *fd;
} noeud;

typedef struct file
{
    noeud **tab;
    int debut;
    int fin;
    int taille;
} file;

void enfile(file *, noeud *);
noeud *defile(file *);

void parcourPGInf(noeud *);
void parcourPGPre(noeud *);
void parcourPGPost(noeud *);

void parcoursLG(noeud *);

noeud *rechercheArbre(noeud *, int);
void ajout(noeud **, int);

int suppression(noeud **, int);

int main()
{

    // noeud *r = (noeud *)malloc(sizeof(noeud));
    // noeud *n1 = (noeud *)malloc(sizeof(noeud));
    // noeud *n2 = (noeud *)malloc(sizeof(noeud));
    // noeud *n3 = (noeud *)malloc(sizeof(noeud));
    // noeud *n4 = (noeud *)malloc(sizeof(noeud));
    // noeud *n5 = (noeud *)malloc(sizeof(noeud));

    // r->val = 17;
    // r->fg = n1;
    // r->fd = n2;
    // n1->val = 3;
    // n1->fg = n3;
    // n1->fd = NULL;
    // n3->val = 2;
    // n3->fd = NULL;
    // n3->fg = NULL;
    // n2->val = 19;
    // n2->fg = n4;
    // n2->fd = n5;
    // n4->val = 18;
    // n4->fg = NULL;
    // n4->fd = NULL;
    // n5->val = 20;
    // n5->fd = NULL;
    // n5->fg = NULL;

    // noeud *ptr = rechercheArbre(r, 3);
    // printf("Recherche avec la valeur 3\n");
    // if (!ptr)
    // {
    //     printf("Valeur non trouvee");
    // }
    // else
    // {
    //     printf("%d", ptr->val);
    // }

    // parcoursLG(r);

    // printf("Parcour en profondeur gauche prefixe\n");
    // parcourPGPre(r);
    // printf("\n");
    // printf("Parcour en profondeur gauche infixe\n");
    // parcourPGInf(r);
    // printf("\n");
    // printf("Parcour en profondeur gauche postfixe\n");
    // parcourPGPost(r);



    noeud *r = NULL;
    ajout(&r, 10);
    ajout(&r, 3);
    ajout(&r, 5);
    ajout(&r, 2);
    ajout(&r, 1);
    // suppression(&r, 3);

    

    parcourPGInf(r);

    return 0;
}

int suppression(noeud **r, int e)
{
    noeud *ptr = *r;
    noeud *pre;
    while (ptr && ptr->val != e)
    {
        pre = ptr;
        if (ptr->val < e)
        {
            ptr = ptr->fd;
        }
        else
        {
            ptr = ptr->fg;
        }
    }
    if (ptr)
    {
        noeud *new, *suivant;
        //Cas ou c'est une feuille
        if (!ptr->fd && !ptr->fg)
        {
            if (pre->val > ptr->val)
            {
                pre->fg = NULL;
            }
            else
            {
                pre->fd = NULL;
            }
            free(ptr);

        } //Cas ou l'élement a un seul fils
        else if ((!ptr->fd && ptr->fg) || (ptr->fd && !ptr->fg))
        {
            //Cas ou le seul fils est à gauche
            if (ptr->fg)
            {
                new = ptr->fg;
            }
            //Cas ou le seul fils est à droite
            else
            {
                new = ptr->fd;
            }
            if (pre->val > ptr->val)
            {
                pre->fg = new;
            }
            else
            {
                pre->fd = new;
            }
            free(ptr);
        }
        //Cas ou le noeud a deux fils
        else
        {
            suivant = ptr->fg;
            new = ptr;
            while (suivant)
            {
                pre = new;
                new = suivant;
                suivant = suivant->fd;
            }
            //A fix par ici
            ptr->val = new->val;
            if(pre->fd->val == new->val){
                pre->fd = NULL;
            } else {
                pre->fg = NULL;
            }
            // free(new);
        }
    }
    else
    {
        printf("L'element a supprimer n'existe pas\n");
        return 0;
    }
}

void ajout(noeud **r, int e)
{
    noeud *n = (noeud *)malloc(sizeof(noeud));
    n->val = e;
    n->fd = NULL;
    n->fg = NULL;
    if (*r)
    {
        noeud *sui = *r;
        noeud *pre;
        while (sui)
        {
            pre = sui;
            if (e < sui->val)
            {

                sui = sui->fg;
            }
            else
            {
                sui = sui->fd;
            }
        }
        if (pre->val > e)
        {
            pre->fg = n;
        }
        else
        {
            pre->fd = n;
        }
    }
    else
    {
        *r = n;
    }
}

noeud *rechercheArbre(noeud *r, int e)
{
    noeud *suivant = r;
    while (suivant && suivant->val != e)
    {
        if (suivant->val < e)
        {
            suivant = suivant->fd;
        }
        else
        {
            suivant = suivant->fg;
        }
    }
    return suivant;
}

void parcourPGInf(noeud *r)
{
    if (r)
    {
        parcourPGInf(r->fg);
        printf("%d ", r->val);
        parcourPGInf(r->fd);
    }
}

void parcourPGPre(noeud *r)
{
    if (r)
    {
        printf("%d ", r->val);
        parcourPGInf(r->fg);
        parcourPGInf(r->fd);
    }
}

void parcourPGPost(noeud *r)
{
    if (r)
    {
        parcourPGInf(r->fg);
        parcourPGInf(r->fd);
        printf("%d ", r->val);
    }
}

noeud *defile(file *f)
{
    if (f->debut == f->fin)
    {
        printf("Impossible de defiler une file vide\n");
        // return NULL;
    }
    return f->tab[f->debut++ % f->taille];
}

void enfile(file *f, noeud *e)
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

void parcoursLG(noeud *r)
{

    if (r)
    {
        file f;
        f.debut = 0;
        f.fin = 0;
        f.taille = 10;
        f.tab = f.tab = (noeud *)malloc(sizeof(noeud) * f.taille);
        noeud *n;
        enfile(&f, r);
        while (f.debut != f.fin)
        {
            n = defile(&f);
            if (n->fg)
            {
                enfile(&f, n->fg);
            }
            if (n->fd)
            {
                enfile(&f, n->fd);
            }
            printf("%d ", n->val);
        }
    }
}