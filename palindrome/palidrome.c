#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int palindrome(char *);
int phrasePalindrome(char *);
void afficheString(char *);
int isPal(char *);

int main()
{
    // char oui[3] = "oui";
    // char kayak[23] = "esoperesteicietserepose";

    // char phrase[] = "oui iUo";
    char esopse[] = "Esope reste ici, et se Repose";
    // afficheString(string, 3);
    // palindrome("oui", 3);
    // palindrome(kayak, 24);
    // phrasePalindrome(kayak, 23);
    afficheString(esopse);
    if (isPal(esopse))
    {
        printf(" est un palindrome");
    }
    else
    {
        printf(" n'est pas un palindrome");
    }

    return 0;
}

int isPal(char *string)
{
    int t1, t2;
    int d = 0;
    int f = strlen(string) - 1;
    int fini = 1;
    while (d <= f && fini)
    {
        if (!isalpha(string[d]))
        {
            d++;
        }
        else if(!isalpha(string[f]))
        {
            f--;
        } else {
            t1 = tolower(string[d]);
            t2 = tolower(string[f]);
            d++;
            f--;
            if(t1 != t2){
                fini = 0;
            }
        }
    }
    return fini;
}

int phrasePalindrome(char *string)
{
    int n = strlen(string) - 1;
    char *str;
    str = (char)malloc(n * sizeof(char));
    //Allocation dynamique de la taille du tableau

    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(string[i]))
        {
            str[k++] = tolower(string[i]);
        }
    }
    afficheString(str);
    return palindrome(str);
}

int palindrome(char *string)
{
    afficheString(string);
    int i = 0;
    int n = strlen(string) - 1;

    while (i < n / 2 && string[i] == string[n - i - 1])
    {
        i++;
    }
    if (string[i] != string[n - i - 1])
    {
        return 0;
        // printf()
        // afficheString(string, n);
        // printf(" n'est pas un palindrome");
    }
    else
    {
        return 1;
        // afficheString(string, n);
        // printf(" est un palindrome");
    }
}

void afficheString(char *string)
{
    int n = strlen(string);
    printf("\"");
    for (int i = 0; i < n; i++)
    {
        printf("%c", string[i]);
    }
    printf("\"");
}