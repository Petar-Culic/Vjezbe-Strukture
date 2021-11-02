#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAXLINE 1024

struct _person;
typedef struct _person* Position;
typedef struct _person
{
	char name[MAX];
	char surname[MAX];
	int year;
	Position next;
}person;

int printlist(Position head);
int addAfter(Position head, char* name, char* surname, int year);
Position findLast(Position head);
Position createPerson(char* name, char* surname, int year);
int sort(Position head);
Position find(Position head, char* surname);
int addAfterFound(Position head, char* name, char* surname, int year, char* findSurname);
int addBeforeFound(Position head, char* name, char* surname, int year, char* findSurname);
int readFromFile(Position head, char* namefile);
int writeToFile(Position head, char* namefile);

int main()
{
	int n = 0;
	char findSurname[MAX] = { 0 };
	person head = { .name = {0}, .surname = {0}, .year = 0, .next = NULL };
	person newPerson = { .name = {0}, .surname = {0}, .year = 0, .next = NULL };

	printf("Koliko osoba zelite unjeti: ");
	scanf(" %d", &n);

	for (int i = 0; i < n; i++)
	{
		printf("Unesite ime nove osobe: \n");
		scanf(" %s", newPerson.name);
		printf("Unesite prezime nove osobe: \n");
		scanf(" %s", newPerson.surname);
		printf("Unesite godinu nove osobe: \n");
		scanf(" %d", newPerson.year);

		addAfter(&head, newPerson.name, newPerson.surname, newPerson.year);
	}


	printf("Unesite ime koje dodajete osobe: \n");
	scanf(" %s", newPerson.name);
	printf("Unesite prezime koje dodajete osobe: \n");
	scanf(" %s", newPerson.surname);
	printf("Unesite godinu koje dodajete osobe: \n");
	scanf(" %d", newPerson.year);

	printf("unesite prezime osobe iza koje zelte unijeti novu osobu\n\n");
	scanf(" %s", findSurname);

	addAfterFound(&head, newPerson.name, newPerson.surname, newPerson.year, findSurname);

	printf("unesite prezime osobe ispred koje zelite unijeti novu osobu \n\n");
	scanf(" %s", findSurname);

	addBeforeFound(&head, newPerson.name, newPerson.surname, newPerson.year, findSurname);
	
	sort(&head);
	printlist(&head);
	

	return 0;
}

Position createPerson(char* name, char* surname, int year)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Position));

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->year = year;
	newPerson->next = NULL;

	return newPerson;
}

Position findLast(Position head)
{
	Position p = head;

	while (NULL != p->next)
	{
		p = p->next;
	}
	return p;
}

int addAfter(Position head, char* name, char* surname, int year)
{
	Position newPerson = createPerson(name, surname, year);
	Position p = findLast(head);

	newPerson->next = p->next;
	p->next = newPerson;

	return 0;
}

Position find(Position head, char* surname)
{
	Position p = head;
	p = p->next;

	while (NULL != p && strcmp(p->surname, surname) != 0)
	{
		p = p->next;
	}
	return p;
}

int printlist(Position head)
{
	Position p = head;
	p = p->next;

	while (NULL!=p)
	{
		printf("%s\t%s\t%d\n", p->name, p->surname, p->year);
		p = p->next;
	}
	return 0;
}

int sort(Position head)
{
	Position temp = NULL, q = NULL, preq = NULL, end = NULL;
	Position p = head;

	while (p->next != end)
	{
		preq = p;
		q = p ->next;
		while (q->next != end)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				temp=q->next;
				preq->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			preq = q;
			q = q->next;
		}
		end = q;
	}
	return 0;
}

int addAfterFound(Position head, char* name, char* surname, int year, char* findSurname)
{
	Position p = head;
	Position newPerson = NULL;

	p = find(head, findSurname);

	if (NULL != p)
	{
		newPerson = (Position)malloc(sizeof(Position));
		strcpy(newPerson->name, name);
		strcpy(newPerson->surname, surname);
		newPerson->year = year;

		newPerson->next = p->next;
		p->next = newPerson;
	}
	else {
		printf("greska!!!\n");
	}

	return 0;
}

int addBeforeFound(Position head, char* name, char* surname, int year, char* findSurname)
{
	Position p = head;
	Position newPerson = NULL;

	while (NULL != p->next && strcmp(p->next->surname, findSurname) != 0)
	{
		p = p->next;
	}
	if (NULL != p)
	{
		newPerson = (Position)malloc(sizeof(Position));
		strcpy(newPerson->name, name);
		strcpy(newPerson->surname, surname);
		newPerson->year = year;

		newPerson->next = p->next;
		p->next = newPerson;
	}
	else {
		printf("greska!!!\n");
	}

	return 0;
}

int readFromFile(Position head, char* namefile)
{
	FILE* file = NULL;
	Position p = head;
	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int year=0;

	

	file = fopen(namefile, "r");
	if (!file)
	{
		printf("greska \n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(namefile, "%s\t%s\t%d", name, surname, &year);
		addAfter(p, name, surname, year);
	}

	fclose(namefile);
	return 0;
}

int writeToFile(Position head, char* namefile)
{
	FILE* file = NULL;
	Position p = head;
	p = p->next;
	
	file = fopen(namefile,"w");
	if (!file)
	{
		printf("greska \n");
		return -1;
	}
	while (NULL != p)
	{
		fprintf("%s\t%s\t%d", p->name, p->surname, p->year);
		p = p->next;
	}
	fclose(namefile);

	return 0;
}
