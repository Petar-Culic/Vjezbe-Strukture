#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DIR_NAME_LENGTH 1024

struct dir;
typedef struct dir* Position;
typedef struct dir {
	char name[DIR_NAME_LENGTH];
	Position next;
	Position child;
} Dir;

struct stack;
typedef struct stack* Node;
typedef struct stack {
	Position p;
	Node next;
} Stack;

Position createDir(char* name);
Node createNode(Position p);
int insertDir(Position p, char* name);
int md(Position p);
int push(Node q, Position p);
int print(Position p);
Position pop(Node q);
Position cddir(Position p, Node q);
Position cd(Position p, Node q);
Position deleteDir(Position p, Node q);
Position freeDir(Position p);

int main()
{
	Dir head;
	Position temp = NULL;
	Stack s;
	int a;

	head.next = NULL;
	head.child = NULL;

	s.p = NULL;
	s.next = NULL;
	strcpy(head.name, "C:");

	temp = &head;

	do {
		puts("\n1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - izlaz");
		scanf("%d", &a); 
		switch(a) {
		case 1:
			md(temp);
			break;
		case 2:
			temp = cddir(temp, &s);
			break;
		case 3:
			temp = cd(temp, &s);
			break;
		case 4:
			printf("/%s/", temp->name);
			print(temp);
			break;
		default:
			break;
		}
	}while(a != 5);

	temp = deleteDir(temp, &s);

	return 0;
}

Position createDir(char* name) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Dir));

	if (q == NULL) {
		perror("Error allocating memory!\n");
		return NULL;
	}

	strcpy(q->name, name);
	q->next = NULL;
	q->child = NULL;

	return q;
}

int insertDir(Position p, char* name) {
	Position q = NULL;

	q = createDir(name);

	if (q != NULL) {
		q->next = p->child;
		p->child = q;
	}

	return 0;
}

int md(Position p) {
	char name[DIR_NAME_LENGTH] = {0};

	printf("Insert name of directory: ");
	scanf("%s", name);

	insertDir(p, name);

	return 0;
}

Node createNode(Position p) {
	Node q = NULL;

	q = (Node)malloc(sizeof(Stack));

	if (q == NULL) {
		perror("Error allocating memory!\n");
		return NULL;
	}

	q->p = p;
	q->next = NULL;

	return q;
}


int push(Node q, Position p) {
	Node r = NULL;

	r = createNode(p);
	
	if (r != NULL) {
		r->next = q->next;
		q->next = r;
	}

	return 0;
}

Position pop(Node q) {
	Node temp = NULL;
	Position el = NULL;

	if (q->next != NULL) {
		temp = q->next;
		q->next = temp->next;
		el = temp->p;
		free(temp);
	}

	return el;
}

Position cddir(Position p, Node q) {
	char name[DIR_NAME_LENGTH] = {0};
	Position temp = NULL;

	temp = p->child;

	if (temp == NULL) {
		printf("Directory doesn't exist!\n");
		return p;
	}

	printf("Insert name of directory: ");
	scanf("%s", name);

	while(temp != NULL && strcmp(temp->name, name) != 0)
		temp = temp->next;

	if (temp == NULL) {
		printf("Directory doesn't exist!\n");
		return p;
	}

	push(q, p);

	return temp;
}

Position cd(Position p, Node q) {
	Position r = NULL;

	r = pop(q);

	if (r == NULL)
		return p;

	return r;
}

int print(Position p) {
	if (p == NULL)
		puts("\nEmpty list!");
	
	p = p->child;
	
	while(p != NULL) {
		printf("%s/", p->name);
		p = p->next;
	}

	return 0;
}

Position freeDir(Position p) {
	if (p != NULL) {
		p->child = freeDir(p->child);
		p->next = freeDir(p->next);
		free(p);
	}

	return NULL;
}

Position deleteDir(Position p, Node q) {
	Position temp = p;

	while(q->next != NULL)
		temp = pop(q);
	
	temp = freeDir(temp->child);
	
	return temp;
}
