#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MLINE 1024

struct polinom;

typedef struct polinom* Pozicija;

typedef struct polinom {

    int k;
    int ex;
    Pozicija next;

}polinom;

int citanjeIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat);
Pozicija stvoriPolinom(int k, int exp);
int sortiraniUnos(Pozicija head, int koef, int exp);
int ispisListe(Pozicija head);
int brisi(Pozicija p);
int brisiSve(Pozicija head);
int zbroji(Pozicija head1, Pozicija head2, Pozicija sumHead);
int pomnozi(Pozicija head1, Pozicija head2, Pozicija produktHead);





int main()
{
    polinom Head1 = { .next = NULL, .ex = 0, .k = 0 };
    polinom Head2 = { .next = NULL, .ex = 0, .k = 0 };

    polinom sumHead = { .next = NULL, .ex = 0, .k = 0 };
    polinom produktHead = { .next = NULL, .ex = 0, .k = 0 };

    char imeDat[MLINE] = { 0 };



    printf("unesite ime datoteke iz koje cemo citati polinome \n");
    scanf(" %s", imeDat);

    citanjeIzDatoteke(&Head1, &Head2, imeDat);

    printf("ovo je prvi polinom: \n");
    ispisListe(&Head1);

    printf("ovo je drugi polinom: \n");
    ispisListe(&Head2);

    printf("ovo je zboj ova 2 polinoma: \n");
    ispisListe(&sumHead);

    printf("ovo je produkt ova 2 polinoma: \n");
    ispisListe(&produktHead);

    brisiSve(&Head1);

    return 0;
}

int citanjeIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat)
{
    FILE* fp;
    int koef = 0;
    int pot = 0;
    int n = 0;
    char* pok = NULL;
    char buffer[MLINE] = { 0 };

    fp = fopen("eksponenti.txt", "r");

    if (!fp)
    {
        perror("neuspijesno otvoren file!\n");
        return -1;
    }

    fgets(buffer, MLINE, fp);
    pok = buffer;
    while (strlen(pok) > 0)
    {
        sscanf(pok, " %d %d %n", &koef, &pot, &n);

        sortiraniUnos(head1, koef, pot);
        pok += n;

    }

    fgets(buffer, MLINE, fp);
    pok = buffer;
    while (strlen(pok) > 0)
    {
        sscanf(pok, " %d %d %n", &koef, &pot, &n);

        sortiraniUnos(head2, koef, pot);
        pok += n;

    }
    
    return 0;
}

Pozicija stvoriPolinom(int koef, int exp)
{
    Pozicija noviPoli = NULL;

    noviPoli = (Pozicija)malloc(sizeof(polinom));

    if (!noviPoli)
    {
        perror("Nemoze alocirati memoriju");
        return -2;
    }

    noviPoli->k = koef;
    noviPoli->ex = exp;
    noviPoli->next = NULL;

    return noviPoli;
}

int sortiraniUnos(Pozicija head, int koef, int exp)
{
    Pozicija q = NULL;
    Pozicija h = head;
    Pozicija prev = head;


    q = stvoriPolinom(koef, exp);
  
    if (NULL == h->next)
    {
        q->next = h->next;
        h->next = q;
        
    }

    else {

        h = h->next;

        while (h->next != NULL && h->ex > exp)
        {
           
            prev = h;
            h = h->next;
        }

        if (h->ex < q->ex)
        {
            //ako je exp novog elementa veci od elementa na kojem je sta h
            q->next = h;
            prev->next = q;
        }
        else if (h->ex == q->ex)
        {
            //ako je exp novog eleemnta isti kao element na kojem je sta h
            //zbroji koeficijente
            h->k = h->k + q->k;
            if (h->k == 0)
            {
                //brisi ovaj element
                //posalt cemo pokazivac na prethodni
                brisi(prev);
            }
        }
        else {

            //ako je exp novog elementa manji od elementa na kojem je sta h
            q->next = h->next;
            h->next = q;
        }
    }
    
    return 0;
}

int ispisListe(Pozicija head)
{
    Pozicija p = head;
    p = p->next;

    while (p != NULL)
    {
        printf("%d x^%d \t", p->k, p->ex);
        p = p->next;
    }

    return 0;
}

int brisi(Pozicija p)
{
    Pozicija temp = NULL;

    temp = p->next;

    p->next = temp->next;
    free(temp);

    return 0;
}

int zbroji(Pozicija head1, Pozicija head2, Pozicija sumHead)
{
    Pozicija h1 = head1;
    Pozicija h2 = head2;
    Pozicija suma = sumHead;

    Pozicija temp = NULL;

    while (h1 != NULL && h2 != NULL)
    {
        if (h1->ex == h2->ex)
        {
            //zbroji k i upisi u listu
            sortiraniUnos(suma, h1->k + h2->k, h1->ex);
            h1 = h1->next;
            h2 = h2->next;
        }

        else if (h1->ex > h2->ex)
        {
            // onaj sa vecim exp prekopiraju sumu
            sortiraniUnos(sumHead, h1->k, h1->ex);
            h1 = h1->next;
        }

        else
        {
            //dosa do kraja liste bez da je nasa elemesnt s kojim se moze zbrojit i jos ima najmanji exp pa ga samo prekopiraj
            sortiraniUnos(suma, h2->k, h2->ex);
            h2 = h2->next;
        }
    }
        
    if (h1 != NULL)
    {
            temp = h1;
    }
       
    else{
            temp = h2;
    }
  
    while (temp != NULL)
    {
            sortiraniUnos(suma, temp->k, temp->ex);
            temp = temp->next;
    }

    

    return 0;
}

int brisiSve(Pozicija head)
{
    Pozicija temp = NULL;

    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 0;
}

int pomnozi(Pozicija head1, Pozicija head2, Pozicija produktHead)
{
    Pozicija h1 = head1;
    Pozicija h2 = head2;
    Pozicija produkt = produktHead;

    Pozicija p = h2;

    while (h1 != NULL)
    {
        h2 = p;
        while (h2 != NULL)
        {
            sortiraniUnos(produkt, h1->k * h2->k, h1->ex + h2->ex);
            h2 = h2->next;
        }
        h1 = h1->next;
    }

    return 0;
}
