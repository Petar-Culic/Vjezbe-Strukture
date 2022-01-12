#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_SIZE 128

struct drzava;
typedef struct drzava * Pozicija;

struct grad;
typedef struct grad * PozicijaG;

typedef struct grad
{
    char* ime;
    int stanovnistvo;
    PozicijaG left;
    PozicijaG right;
}_grad; 

typedef struct drzava
{
    char* ime;
    PozicijaG root;
    Pozicija next;
}_drzava;


Pozicija StvoriDrzavu(char*);
int DrzavaInsert(Pozicija, Pozicija);

int InsertAfter(Pozicija , Pozicija);
Pozicija DrzavaFind(Pozicija, char*);

PozicijaG stvoriGrad(char*, int);
int CmpGrad(PozicijaG, PozicijaG);

int ReadFromFile(Pozicija,char*);
int PrintList(Pozicija);

PozicijaG CreateTreeFromFile(char*);
int InsertNode(PozicijaG, PozicijaG);

int PrintSilazno(PozicijaG);
int PrintVeci(PozicijaG, int);

void PrintLine();
int PretraziGrad(Pozicija);

int main()
{
    Pozicija head=NULL;
    
    head = (Pozicija)malloc(sizeof(_drzava));
    head->ime=NULL;
    head->root=NULL;
    head->next=NULL;
    
    ReadFromFile(head, "drzave.txt");

    PrintList(head);

    PretraziGrad(head);
    
    return 0;
}

int InsertAfter(Pozicija pos, Pozicija novaDrzava)
{
    novaDrzava->next = pos->next;
    pos->next = novaDrzava;

    return 0;
}

int DrzavaInsert(Pozicija head, Pozicija novaDrzava)
{
    Pozicija temp = head;

    while(temp->next)
    {
        if (strcmp(novaDrzava->ime, temp->next->ime) < 0)
        {
            InsertAfter(temp, novaDrzava);
            return EXIT_SUCCESS;
        }

        temp = temp->next;
    }

        InsertAfter(temp, novaDrzava);
        return EXIT_SUCCESS;
}

Pozicija StvoriDrzavu(char* ime)
{
    Pozicija novaDrzava = NULL;
    
    novaDrzava = (Pozicija)malloc(sizeof(_drzava));

    if (!novaDrzava)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    novaDrzava->ime=(char*)malloc(strlen(ime)+1);

    strcpy(novaDrzava->ime, ime);
    novaDrzava->root = NULL;
    novaDrzava->next = NULL;

    return novaDrzava;
}


PozicijaG stvoriGrad(char* ime, int stanovnistvo)
{
    PozicijaG noviGrad = NULL;
    noviGrad = (PozicijaG)malloc(sizeof(_grad));
    if(!noviGrad)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    noviGrad->ime=(char*)malloc(strlen(ime)+1);
    strcpy(noviGrad->ime, ime);
    noviGrad->stanovnistvo = stanovnistvo;
    noviGrad->left = NULL;
    noviGrad->right = NULL;

    return noviGrad;
}

int CmpGrad(PozicijaG prvi, PozicijaG drugi)
{
    int razlika = 0;
    
    razlika = prvi->stanovnistvo - drugi->stanovnistvo;

    if (!razlika)
    {
        razlika = strcmp(prvi->ime, drugi->ime);
    }

    return razlika;
}

int ReadFromFile(Pozicija head, char* filename)
{
    FILE* drzave = NULL;
    Pozicija tempDrzava = NULL;

    char* buffer=NULL;
    char* temp=NULL;
    char* imeDrzave=NULL;
    char* imeDatotekezaGrad = NULL;

    int fileSize = 0;
    int read = 0;
    int state = 0;

    imeDrzave = (char*)malloc(MAX_SIZE);
    imeDatotekezaGrad = (char*)malloc(MAX_SIZE);

    if(!imeDrzave || !imeDatotekezaGrad)
    {
        printf("Not enough memory!\n");
        return -1;
    }

    drzave = fopen(filename,"r");

    if(!drzave)
    {
        printf("File not found!\n");
        return 1;
    }

    fseek(drzave,0, SEEK_END);
    fileSize=ftell(drzave);
    rewind(drzave);

    buffer=(char*)malloc(fileSize+1);

    if(!buffer)
    {
        printf("Not enough memory!\n");
        return -1;
    }

    fread(buffer,fileSize,1,drzave);
    fclose(drzave);

    temp=buffer;

    while(strlen(temp)>0)
    {
        state = sscanf(temp,"%s %s %n",imeDrzave,imeDatotekezaGrad,&read);
        temp+=read;

        if(state==2)
        {
            tempDrzava=StvoriDrzavu(imeDrzave);

            if(tempDrzava)
            {
                tempDrzava->root=CreateTreeFromFile(imeDatotekezaGrad);
                DrzavaInsert(head,tempDrzava);
            }
        }
        
    }
    
    return 0;
}

int PrintList(Pozicija head)
{
    Pozicija temp=head->next;

    if(!temp)
    {
        printf("List is empty!\n");
        return 1;
    }

    while(temp)
    {
        printf("%s:\n",temp->ime);
        PrintLine();
        PrintSilazno(temp->root);
        PrintLine();
        printf("\n");
        temp=temp->next;
    }

    return 0;
}

int InsertNode(PozicijaG curr, PozicijaG newNode)
{
    int state=0;
    int relation=0;
    if(!curr)
    {
        printf("Tree doesn't exist!\n");
        return 1;
    }

    relation=CmpGrad(newNode,curr);

    if(!relation)
    {
        free (newNode);
        return EXIT_SUCCESS;
    }

    if(relation<0)
    {
        if(!(curr->left))
        {
            curr->left=newNode;
            return EXIT_SUCCESS;
        }
        state=InsertNode(curr->left,newNode);
        return EXIT_SUCCESS;
    }

    else
    {
         if(!(curr->right))
        {
            curr->right=newNode;
            return EXIT_SUCCESS;
        }
        state=InsertNode(curr->right,newNode);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

PozicijaG CreateTreeFromFile(char* filename)
{
    FILE* cities=NULL;
    PozicijaG tempCity=NULL;
    PozicijaG root=NULL;

    char* buffer=NULL;
    char* temp=NULL;
    char* cityName=NULL;

    int fileSize=0;
    int read=0;
    int pop=0;
    int state=0;

    cityName=(char*)malloc(MAX_SIZE);


    cities=fopen(filename,"r");

    if(!cities)
    {
        printf("File not found!\n");
        return NULL;
    }

    fseek(cities,0, SEEK_END);
    fileSize=ftell(cities);
    rewind(cities);

    buffer=(char*)malloc(fileSize+1);

    if(!buffer)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    fread(buffer,fileSize,1,cities);
    fclose(cities);

    temp=buffer;

    while(strlen(temp)>0)
    {
        state = sscanf(temp,"%s %d %n",cityName,&pop,&read);
        temp+=read;

        if(state==2)
        {
            tempCity=stvoriGrad(cityName,pop);

            if(tempCity)
            {
                if(!root)
                    root=tempCity;
                else
                {
                    InsertNode(root,tempCity);
                }
            }
        }
    }
    
    return root;
}

void PrintLine()
{
    printf("******************************\n");
    return;
}

int PrintSilazno(PozicijaG pos)
{
    if(pos==NULL)
        return EXIT_SUCCESS;
    PrintSilazno(pos->right);
    printf("%s - Population %d\n",pos->ime,pos->stanovnistvo);
    PrintSilazno(pos->left);

    return EXIT_SUCCESS;
}

int PrintVeci(PozicijaG pos, int limit)
{
    if(pos==NULL)
        return EXIT_SUCCESS;
    
    PrintVeci(pos->left,limit);
    if(pos->stanovnistvo > limit)printf("%s - Population %d\n",pos->ime,pos->stanovnistvo);
    PrintVeci(pos->right,limit);

    return EXIT_SUCCESS;
}

Pozicija DrzavaFind(Pozicija head, char* ime)
{
    Pozicija temp=head;
    while(temp)
    {
        if(temp->ime && !strcmp(temp->ime,ime))
        {
            return temp;
        }

        temp=temp->next;
    }

    return NULL;
}

int PretraziGrad(Pozicija head)
{
    char* imeDrzave = NULL;
    Pozicija found = NULL;
    int limit = 0;

    printf("Please choose a country: ");
    imeDrzave=(char*)malloc(MAX_SIZE);

    fgets(imeDrzave,MAX_SIZE,stdin);
    imeDrzave[strcspn(imeDrzave, "\n")] = 0;

    found = DrzavaFind(head,imeDrzave);

    if(!found)
    {
        printf("Couldn't find country!\n");
        return 1;
    }

    printf("Please enter population threshold for city search: ");
    scanf("%d", &limit);
    
    printf("\nCities in %s with population over %d:\n",found->ime,limit);
    PrintLine();
    PrintVeci(found->root,limit);

    return 0;
}
