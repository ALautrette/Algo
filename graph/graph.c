#include <stdio.h>
#include <stdlib.h>

typedef struct file
{
   int *tab;
   int debut;
   int fin;
} file;

typedef struct maillon
{
   int sommet;
   struct maillon *suivant;
} maillon;

void parcoursProfMatrice(int *, int);
void parcoursProfCMatrice(int, int *, int, int *);

void parcoursLargMatrice(int *, int);
void parcoursLargCMatrice(int, int *, int, int *);

int cyclique(int *, int);

void enfile(file *, int);
int defile(file *);

maillon **matriceToList(int *, int);
void ajouteTriV2(maillon **, int);
void afficheListe(maillon *);

void parcoursProfondeurList(maillon **, int);
void parcoursProfondeurCList(int, maillon **, int, int *);

void parcoursLargList(maillon **, int);
void parcoursLargCList(int, maillon **, int, int *);

void longueurChemins(int *, int, int);

void afficheChemins(int, unsigned int *, maillon **, int);
void changementChemin(maillon **, int, int);
void ajoutFinListe(maillon **, int);
void afficheFile(file *);

main()
{
   int matrice[] = {0, 3, 2, 0, 0, 3, 0, 0, 6, 0, 2, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0};
   int matrice2[] = {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
   int matrice3[] = {0, 7, 2, 7, 0, 1, 2, 1, 0};
   // parcoursLargMatrice(matrice, 5);
   // parcoursProfMatrice(matrice, 5);
   // maillon **l = matriceToList(matrice, 5);
   longueurChemins(matrice3, 3, 1);

   // parcoursLargList(matriceToList(matrice, 5), 5);
   return 0;
}

// int cyclique(int *g, int n)
// {
//    int * marques = (int *)calloc(n, sizeof(int));
//    marques[s] = 1;
//    printf("%d ", s);
//    for (int i = 0; i < n; i++)
//    {

//       if (g[s * n + i] && !marques[i])
//       {
//          parcoursProfCMatrice(i, g, n, marques);
//       }
//    }
// }

void longueurChemins(int *g, int n, int sDepart)
{
   //Initialisation de tout ce dont nous avons besoin
   unsigned int *distances = (unsigned int *)malloc(sizeof(unsigned int) * n);
   maillon **chemins = (maillon **)malloc(sizeof(maillon *) * n);
   for (int i = 0; i < n; i++)
   {
      distances[i] = 100; //(unsigned int)(-1);
      // maillon *boite = (maillon *)malloc(sizeof(maillon));
      // boite->sommet = sDepart;
      // boite->suivant = NULL;
      // chemins[i] = boite;
      chemins[i] = NULL;
   }
   maillon *depart = (maillon *)malloc(sizeof(maillon));
   depart->sommet = sDepart;
   depart->suivant = NULL;
   distances[sDepart] = 0;
   chemins[sDepart] = depart;
   file *f = (file *)malloc(sizeof(file));
   f->debut = 0;
   f->fin = 0;
   f->tab = (int *)malloc(n * sizeof(int));
   int s;

   //Fin initialisation
   enfile(f, sDepart);

   while (f->debut != f->fin)
   {
      s = defile(f);
      for (int i = 0; i < n; i++)
      {

         if (g[s * n + i] && distances[i] > distances[s] + g[s * n + i]) //J'en était la
         {

            enfile(f, i);
            distances[i] = distances[s] + g[s * n + i];
            changementChemin(chemins, s, i);
         }
      }
   }

   afficheChemins(sDepart, distances, chemins, n);
}

// void afficheFile(file f)
// {
//    maillon *ptr = f.tete;
//    while (ptr)
//    {
//       if (ptr->suivant)
//       {
//          printf("%d, ", ptr->val);
//       }
//       else
//       {
//          printf("%d", ptr->val);
//       }

//       ptr = ptr->suivant;
//    }
// }

void afficheChemins(int sommet, unsigned int *distances, maillon **chemins, int n)
{
   maillon *m;
   printf("Sommet %d", sommet);
   for (int i = 0; i < n; i++)
   {
      printf("\nDistance vers le sommet %d : ", i);
      printf("%d\n Chemin : ", distances[i]);
      m = chemins[i];
      while (m)
      {
         printf("%d -> ", m->sommet);
         m = m->suivant;
      }
   }
}

void changementChemin(maillon **chemins, int s, int i)
{
   maillon *maille = chemins[s];
   maillon *boite = (maillon *)malloc(sizeof(maillon));
   boite->sommet = maille->sommet;
   boite->suivant = NULL;
   free(chemins[i]);
   chemins[i] = boite;
   maille = maille->suivant;
   while (maille)
   {

      ajoutFinListe(&chemins[i], maille->sommet);

      maille = maille->suivant;
   }

   ajoutFinListe(&chemins[i], i);
}

void ajoutFinListe(maillon **tete, int e)
{
   maillon *boite = (maillon *)malloc(sizeof(maillon));
   maillon *pre = NULL;
   boite->sommet = e;
   boite->suivant = NULL;
   maillon *suivant = *tete;
   while (suivant)
   {
      pre = suivant;
      suivant = suivant->suivant;
   }
   if (pre)
   {
      pre->suivant = boite;
   }
   else
   {
      *tete = boite;
   }

   // if (tete)
   // {
   //    suivant = *tete;
   //    while (suivant->suivant)
   //    {
   //       suivant = suivant->suivant;
   //    }
   //    suivant->suivant = boite;
   // }
   // else
   // {

   //    *tete = boite;
   // }
}

void parcoursLargCList(int s, maillon **g, int n, int *marques)
{
   maillon *ptr;
   int val;
   file *f = (file *)malloc(sizeof(file));
   f->tab = (int *)malloc(n * sizeof(int));
   f->debut = 0;
   f->fin = 0;
   enfile(f, s);
   marques[s] = 1;
   while (f->debut != f->fin)
   {
      val = defile(f);
      printf("%d ", val + 1);
      ptr = g[val];
      while (ptr)
      {
         if (!marques[ptr->sommet])
         {
            enfile(f, ptr->sommet);
            marques[ptr->sommet] = 1;
         }
         ptr = ptr->suivant;
      }
   }
}

void parcoursLargList(maillon **g, int n)
{
   if (g)
   {
      int *marques = (int *)calloc(n, sizeof(int));
      for (int i = 0; i < n; i++)
      {
         if (!marques[i])
         {
            parcoursLargCList(i, g, n, marques);
         }
      }
   }
}

void parcoursProfondeurList(maillon **g, int n)
{
   if (g)
   {
      int *marques = (int *)calloc(n, sizeof(int));
      for (int i = 0; i < n; i++)
      {
         if (!marques[i])
         {
            parcoursProfondeurCList(i, g, n, marques);
         }
      }
   }
}

void parcoursProfondeurCList(int s, maillon **g, int n, int *marques)
{
   marques[s] = 1;
   printf("%d ", s);
   maillon *ptr = g[s];
   while (ptr)
   {
      if (!marques[ptr->sommet])
      {
         parcoursProfondeurCList(ptr->sommet, g, n, marques);
      }
      ptr = ptr->suivant;
   }
}

void afficheListe(maillon *tete)
{
   struct maillon *ptr = tete;
   while (ptr)
   {
      if (ptr->suivant)
      {
         printf("%d, ", ptr->sommet);
      }
      else
      {
         printf("%d\n", ptr->sommet);
      }

      ptr = ptr->suivant;
   }
}

maillon **matriceToList(int *m, int n)
{
   maillon **liste = (maillon **)malloc(n * sizeof(maillon *));
   for (int i = 0; i < n; i++)
   {
      liste[i] = NULL;
   }

   for (int i = 0; i < n; i++)
   {
      for (int y = 0; y < n; y++)
      {
         if (m[i * n + y])
         {
            ajouteTriV2(&liste[i], y);
         }
      }
   }
   return liste;
}

void ajouteTriV2(maillon **tete, int e)
{
   struct maillon *ptr = *tete;
   struct maillon *pre = NULL;
   struct maillon *boite = (struct maillon *)malloc(sizeof(struct maillon));
   boite->sommet = e;
   while (ptr && ptr->sommet < e)
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

void parcoursProfMatrice(int *g, int n)
{
   if (g)
   {
      int *marques = (int *)calloc(n, sizeof(int));
      for (int i = 0; i < n; i++)
      {
         if (!marques[i])
         {
            parcoursProfCMatrice(i, g, n, marques);
         }
      }
   }
}

void parcoursProfCMatrice(int s, int *g, int n, int *marques)
{
   marques[s] = 1;
   printf("%d ", s);
   for (int i = 0; i < n; i++)
   {

      if (g[s * n + i] && !marques[i])
      {
         parcoursProfCMatrice(i, g, n, marques);
      }
   }
}

void parcoursLargMatrice(int *g, int n)
{
   if (g)
   {
      int *marques = (int *)calloc(n, sizeof(int));
      for (int i = 0; i < n; i++)
      {
         if (!marques[i])
         {
            parcoursLargCMatrice(i, g, n, marques);
         }
      }
   }
}

void parcoursLargCMatrice(int s, int *g, int n, int *marques)
{
   int val;
   file *f = (file *)malloc(sizeof(file));
   f->tab = (int *)malloc(n * sizeof(int));
   f->debut = 0;
   f->fin = 0;
   enfile(f, s);
   marques[s] = 1;
   while (f->debut != f->fin)
   {
      val = defile(f);
      printf("%d ", val);
      for (int i = 0; i < n; i++)
      {
         if (g[val * n + i] && !marques[i])
         {
            enfile(f, i);
            marques[i] = 1;
         }
      }
   }
}

void enfile(file *f, int e)
{
   f->tab[f->fin++] = e;
}

int defile(file *f)
{
   return f->tab[f->debut++];
}
