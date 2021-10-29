#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define Msize (50)

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
    char ime[Msize];
    char prezime[Msize];
    int godina_rodenja;
    Pozicija next;
}osoba;


int unosPocetak(Pozicija p, char* ime, char* prezime, int godina_rodenja);
int ispisListe(Pozicija prvi);
int unosKraj(Pozicija p, char* ime, char* prezime, int godina_rodenja);
Pozicija trazi(Pozicija prvi, char* prezime);
int brisi(Pozicija prvi, char* preime);

int main()
{
    int n = 0;
    char pronadi[Msize] = { 0 };
    osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .godina_rodenja = 0 };
    osoba ja = { .next = NULL, .ime = {0}, .prezime = {0}, .godina_rodenja = 0 };
    Pozicija pronaden = NULL;

    printf("unesite broj osoba koje zelite unjeti na pocetak\n");
    scanf(" %d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("unesite ime osobe \n");
        scanf(" %s", ja.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s", ja.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d", &ja.godina_rodenja);

        unosPocetak(&head, ja.ime, ja.prezime, ja.godina_rodenja);
    }

    ispisListe(head.next);

    printf("unesite broj osoba koje zelite unjeti na kraj\n");
    scanf(" %d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("unesite ime osobe \n");
        scanf(" %s", ja.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s", ja.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d", &ja.godina_rodenja);

        unosKraj(&head, ja.ime, ja.prezime, ja.godina_rodenja);
    }

    ispisListe(head.next);


    printf("unesite prezime osobe koje trazite\n");
    scanf(" %s", pronadi);
    pronaden = trazi(head.next, pronadi);

    printf("trazeni element: %s %s %d \n", pronaden->ime, pronaden->prezime, pronaden->godina_rodenja);

    brisi(head.next, pronadi);
    ispisListe(head.next);

    return 0;
}



int unosPocetak(Pozicija p, char* ime, char* prezime, int godina_rodenja)
{

    Pozicija novaOsoba = NULL;

    novaOsoba = (Pozicija)malloc(sizeof(Pozicija));

    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodenja = godina_rodenja;

    novaOsoba->next = NULL;


    novaOsoba->next = p->next;
    p->next = novaOsoba;

    return 0;
}

int ispisListe(Pozicija prvi)
{
    Pozicija p = prvi;

    while (NULL != p)
    {
        printf("element: %s %s %d \n", p->ime, p->prezime, p->godina_rodenja);
        p = p->next;
    }
    return 0;
}

int unosKraj(Pozicija p, char* ime, char* prezime, int godina_rodenja)
{
    Pozicija novaOsoba = NULL;

    novaOsoba = (Pozicija)malloc(sizeof(Pozicija));

    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodenja = godina_rodenja;

    novaOsoba->next = NULL;

    while (NULL != p->next)
    {
        p = p->next;
    }
    novaOsoba->next = p->next;
    p->next = novaOsoba;

    return 0;
}

Pozicija trazi(Pozicija prvi, char* prezime)
{

    Pozicija p = prvi;

    while (NULL != p && strcmp(p->prezime, prezime) != 0)
    {
        p = p->next;
    }

    return p;
}

int brisi(Pozicija prvi, char* prezime)
{
    Pozicija temp = NULL;
    Pozicija p = prvi;

    while (NULL != p->next && strcmp(p->next->prezime, prezime) != 0)
    {
        p = p->next;
    }
    temp = p->next;
    p->next = p->next->next;
    free(temp);

    return 0;
}
