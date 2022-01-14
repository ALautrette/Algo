#include <stdio.h>
#include <stdlib.h>

typedef struct noeud
{
    char val;
    struct noeud *fg, *fd;
} noeud;

void afficheArbre(noeud *);
int profDroite(noeud *);

noeud *rotG(noeud *);
noeud *rotD(noeud *);

int main()
{
    noeud *a = (noeud *)malloc(sizeof(noeud));
    noeud *b = (noeud *)malloc(sizeof(noeud));
    noeud *c = (noeud *)malloc(sizeof(noeud));
    noeud *d = (noeud *)malloc(sizeof(noeud));
    noeud *e = (noeud *)malloc(sizeof(noeud));
    a->val = 'a';
    b->val = 'b';
    c->val = 'c';
    d->val = 'd';
    e->val = 'e';
    a->fg = b;
    a->fd = NULL;
    b->fg = c;
    b->fd = d;
    d->fd = NULL;
    d->fg = NULL;
    c->fg = NULL;
    c->fd = NULL;
    // a->val = 'a';
    // a->fd = b;
    // a->fg = NULL;
    // b->val = 'b';
    // b->fg = d;
    // b->fd = c;
    // d->val = 'd';
    // d->fg = NULL;
    // d->fd = NULL;
    // c->val = 'c';
    // c->fg = NULL;
    // c->fd = e;
    // e->val = 'e';
    // e->fg = NULL;
    // e->fd = NULL;

    afficheArbre(a);
    printf("\n");

    noeud *newRacine = rotD(a);
    afficheArbre(newRacine);

    return 0;
}

int profDroite(noeud *r){
    
}

void afficheArbre(noeud *r)
{
    if (r)
    {
        printf("%c ", r->val);
        if (estPasEquilibre())
        {
            afficheArbre(r->fg);

            afficheArbre(r->fd);
            equilibrer();
        }
        else
        {
            afficheArbre(r->fg);

            afficheArbre(r->fd);
        }
    }
}

noeud *rotG(noeud *a)
{
    noeud *newR = a->fd;
    a->fd = newR->fg;
    newR->fg = a;
    return newR;
    // afficheArbre(newR);
}

noeud *rotD(noeud *a)
{
    noeud *newR = a->fg;
    a->fg = newR->fd;
    newR->fd = a;
    return newR;
    // afficheArbre(newR);
}