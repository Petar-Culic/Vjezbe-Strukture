#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element;
typedef struct element * position;
typedef struct element
{
	int el;
	position left;
	position right;
}element;

position create_el(int a);
position insert(position root, position p); //pod a)
int replace(position root); //pod b)
int printinorder(position root);

int main()
{
	position korijen = NULL;
	int i = 0;
	int niz[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	for (i = 0; i < 10; i++)
	{
		korijen = insert(korijen, create_el(niz[i]));
	}
	printinorder(korijen);
    puts("");
	replace(korijen);
	printinorder(korijen);
    puts("");
	return 0;
}

int printinorder(position q) {
	if (q == NULL)
	{
		return EXIT_SUCCESS;
	}
	else
	{
		printinorder(q->left);
		printf("%d\t", q->el);
		printinorder(q->right);
	}
	return EXIT_SUCCESS;
}

position create_el(int a)
{
	position q = (position)malloc(sizeof(element));
	
	q->el = a;

	q->left = NULL;
	q->right = NULL;

	return q;
}

position insert(position root, position p)
{
	if (root == NULL)
	{
		root = p;
		return root;
	}
	else if (root->el <= p->el)
	{
		root->left = insert(root->left, p);
	}
	else if (root->el > p->el)
	{
		root->right = insert(root->right, p);
	}
	return root;
}

int replace(position current)
{
	int l_before = 0;
	int d_before = 0;
	int l_now = 0;
	int d_now = 0;

	if (current != NULL)
	{
		if (current->left != NULL)
		{
			l_before = current->left->el;
		}
		if (current->right != NULL)
		{
			d_before = current->right->el;
		}

		replace(current->left);
		replace(current->right);

		if (current->left != NULL)
		{
			l_now = current->left->el;
		}

		if (current->right != NULL)
		{
			d_now = current->right->el;
		}

		return current->el = l_now + d_now + l_before + d_before;
	}
	return 0;
}			
