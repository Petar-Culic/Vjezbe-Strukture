#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MLINE 1024

struct stog;
typedef struct stog* Pozicija;

typedef struct stog {

	int number;
	Pozicija next;

}stog;

int citajIzDatoteke(Pozicija head, char* imeDat);
Pozicija stvoriELement(int number);
int operacija(Pozicija head, char operand);
int unosNaStog(Pozicija head, int number);
int skiniSaStoga(Pozicija head, double *spremiRezultat);
int brisiElement(Pozicija head);
int ispisStoga(Pozicija head);


int main()
{
	stog head = { .number = 0, .next = NULL };

	char imeDat[MLINE] = { 0 };

	printf("unesite ime datoteke iz koje cemo citati postfix \n");
	scanf(" %s", imeDat);
	citajIzDatoteke(&head, imeDat);

	return 0;
}

int citajIzDatoteke(Pozicija head, char* imeDat)
{
	FILE* fp = NULL;
	int number = 0;
	int fileLength = 0;
	int n = 0;
	int d = 0;
	int i = 0;

	char* pok = NULL;
	char buffer[MLINE] = { 0 };

	fp = fopen(imeDat, "rb");

	if (!fp)
	{
		perror("greska pri otvaranju datoteke \n");

		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);

	fgets(buffer, MLINE, fp);
	pok = buffer;

	d = strlen(pok);
	printf("%d\n", d);
	for (i = 0; i < d; i++)
	{
		printf("%d element %c\n", i, buffer[i]);
		

		if (buffer[i] == '+' )
		{
			operacija(&head, buffer[i]);
			
		}
		else if (buffer[i] == '-')
		{
			operacija(&head, buffer[i]);
		}
		else if (buffer[i] == '*')
		{
			operacija(&head, buffer[i]);
		}
		else if (buffer[i] == '/')
		{
			operacija(&head, buffer[i]);
		}
		else if(buffer[i]==' ')
		{
			continue;
		}
		else 
		{
			unosNaStog(&head, number);
		}
		
	}


	return 0;
}

int unosNaStog(Pozicija head, int number)
{
	Pozicija noviElement = NULL;
	Pozicija h = head;

	noviElement = stvoriELement(number);

	noviElement->next = h->next;
	h->next = noviElement;

	printf("ispis stoga:\n");
	ispisStoga(&head);

	return 0;
}

Pozicija stvoriELement(int number)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(stog));

	if (!q)
	{
		perror("Nemoze alocirati memoriju");
		return NULL;
	}

	q->number = number;
	q->next = NULL;

	return q;
}

int operacija(Pozicija head, char operand)
{
	double broj1 = 0;
	double broj2 = 0;
	double rezultat = 0;
	int provjera2 = 0;
	int provjera1 = 0;

	//skini sa stoga broj 2
	provjera2 = skiniSaStoga(&head, &broj2);
	
    //provjeri jeli broj2 uspjesno skinut
	if (provjera2 != 0)
	{
		return -5;
	}
	
	//skini sa stoga broj1 
	provjera1 = skiniSaStoga(&head, &broj1);

	//provjeri jeli broj1 uspjesno skinut
	if (provjera1 != 0)
	{
		return -6;
	}


	switch (operand)
	{
	case '+':
		rezultat = broj1 + broj2;
		break;
	case '-':
		rezultat = broj1 - broj2;
		break;
	case '*':
		rezultat = broj1 * broj2;
		break;
	case '/':
		if (broj2 == 0)
		{
			perror("nemoze se dijeliti sa 0\n");
			return -3;
		}
		rezultat = broj1 / broj2;
		break;
	default:
		return -4;
	}
	//stavi na stog rezultat
	unosNaStog(&head, rezultat);

	return 0;
}

int skiniSaStoga(Pozicija head, double* spremiRezultat)
{
	printf("usa u funkciju skini sa stoga\n");

	Pozicija p = head;
	p = p->next;

	if (!p)
	{
		perror("stog prazan!");
		return -2;
	}

	spremiRezultat = p->number;
	//obrisi elemnt koji si upravo skinija
	brisiElement(&head);

	return 0;
}

int brisiElement(Pozicija head)
{
	printf("usa u funkciju brisi\n");
	Pozicija h = head;
	Pozicija temp = NULL;

	temp = h->next;

	//akoj e head->next NULL onda je lista prazna --> nema sta brisat
	if (!temp)
	{
		printf("stog je prazan\n");
		return 0;
	}

	h->next = temp->next;
	free(temp);

	return 0;
}

int ispisStoga(Pozicija head)
{
	Pozicija prvi = head;
	prvi = prvi->next;

	while (prvi != NULL)
	{
		printf("element stoga: %d\n", prvi->number);
		prvi = prvi->next;
	}
	return 0;
}

