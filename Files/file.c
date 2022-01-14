#include <stdio.h>
#include <stdlib.h>

typedef struct maillon
{
   int val;
   struct maillon *suivant;
} maillon;

typedef struct file
{
   maillon *tete;
   maillon *queue;
} file;

void afficheFile(file);
void enfile(file *, int);
int defile(file *);

int main()
{
   file f;
   f.queue = NULL;
   f.tete = NULL;
   defile(&f);
   enfile(&f, 2);
   enfile(&f, 23);
   enfile(&f, 22);
   defile(&f);
   afficheFile(f);
   return 0;
}

int defile(file *f)
{
   maillon *ptr = f->tete;
   int val;
   if (!ptr)
   {
      printf("Impossible de defiler une file vide\n");
      return 0;
   }
   val = ptr->val;
   f->tete = ptr->suivant;
   free(ptr);
   return val;
}

void enfile(file *f, int e)
{
   maillon *m = (maillon *)malloc(sizeof(maillon *));
   m->val = e;
   m->suivant = NULL;
   if (f->tete)
   {
      f->queue->suivant = m;
   }
   else
   {

      f->tete = m;
   }
   f->queue = m;
}

void afficheFile(file f)
{
   maillon *ptr = f.tete;
   while (ptr)
   {
      if (ptr->suivant)
      {
         printf("%d, ", ptr->val);
      }
      else
      {
         printf("%d", ptr->val);
      }

      ptr = ptr->suivant;
   }
}