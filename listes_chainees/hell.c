#include <stdio.h>
#include <stdlib.h>

struct maillon
{
    int valeur;
    struct maillon *suivant;
};

void afficheListe(struct maillon *);
int listeVide(struct maillon *);
void ajouter(struct maillon **, int);
struct maillon *cherche(struct maillon *, int);
int supprime(struct maillon **, int);
void ajouteTri(struct maillon **, int);
void ajouteTriV2(struct maillon **, int);

int main()
{
    struct maillon *tete = NULL;
    ajouteTriV2(&tete, 7);
    ajouteTriV2(&tete, 6);
    ajouteTriV2(&tete, 5);
    ajouteTriV2(&tete, 6);
    ajouteTriV2(&tete, 10);
    ajouteTriV2(&tete, 5);
    ajouteTriV2(&tete, 3);
    afficheListe(tete);

    return 0;
}

void ajouteTriV2(struct maillon **tete, int e)
{
    struct maillon *ptr = *tete;
    struct maillon *pre = NULL;
    struct maillon *boite = (struct maillon *)malloc(sizeof(struct maillon));
    boite->valeur = e;
    while (ptr && ptr->valeur < e)
    {
        pre = ptr;
        ptr = ptr->suivant;
    }
    if (*tete == ptr) //Cas début de liste ou liste vide
    {
        boite->suivant = ptr;
        *tete = boite;
    }
    else //Cas général
    {
        pre->suivant = boite;
        boite->suivant = ptr;
    }
}

void ajouteTri(struct maillon **tete, int e)
{
    struct maillon *ptr = *tete;
    struct maillon *pre = NULL;
    struct maillon *boite = (struct maillon *)malloc(sizeof(struct maillon));
    boite->valeur = e;
    int fini = 0;
    //Cas liste vide
    if (!ptr)
    {
        *tete = boite;
        boite->suivant = NULL;
    }
    else
    {
        while (ptr && !fini)
        {
            if (ptr->valeur < e) //Passage au prochain maillon
            {
                pre = ptr;
                ptr = ptr->suivant;
            }
            else if (pre != NULL) //Cas ajout en milieu de liste (cas classique)
            {
                boite->suivant = pre->suivant;
                pre->suivant = boite;
                fini = 1;
            }
            else //Cas ajout au début de la liste
            {
                boite->suivant = *tete;
                *tete = boite;
                fini = 1;
            }
        }
        if (!ptr) //Cas ajout en fin de liste
        {
            boite->suivant = NULL;
            pre->suivant = boite;
        }
    }
}

struct maillon *cherche(struct maillon *tete, int e)
{
    struct maillon *ptr = tete;
    while (ptr)
    {
        if (ptr->valeur == e)
        {
            return ptr;
        }
        ptr = ptr->suivant;
    }
    return NULL;
}

int supprime(struct maillon **tete, int e)
{
    struct maillon *ptr = *tete, *pre = NULL;

    while (ptr)
    {
        if (ptr->valeur != e)
        {
            pre = ptr;
            ptr = ptr->suivant;
        }
        else if (pre != NULL)
        {
            pre->suivant = ptr->suivant;
            free(ptr);
        }
        else
        {
            *tete = ptr->suivant;
            free(ptr);
            return 1;
        }
    }
    return 0;
}

// ** car on modifie l'adresse du pointeur (passage par adresse et non par copie) -> ajouter(&tete, val);
void ajouter(struct maillon **tete, int val)
{
    struct maillon *boite = (struct maillon *)malloc(sizeof(struct maillon));
    boite->suivant = *tete;
    *tete = boite;
    boite->valeur = val;
}

void afficheListe(struct maillon *tete)
{
    struct maillon *ptr = tete;
    while (ptr)
    {
        if (ptr->suivant)
        {
            printf("%d, ", ptr->valeur);
        }
        else
        {
            printf("%d", ptr->valeur);
        }

        ptr = ptr->suivant;
    }
}

int listeVide(struct maillon *tete)
{
    return (tete == NULL);
}