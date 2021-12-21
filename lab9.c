#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct tree;
typedef struct tree* Node;
typedef struct tree* Position;
typedef struct tree {
	int el;
	Node right;
	Node left;
} Tree;

Node createEmptyTree(Node p);
Node insertNode(Node p, int el);
int printTree(Node p);
Position findMin(Node p);
Position findMax(Node p);
Position find(Node p, int el);
Node deleteNode(Node p, int el);

int main()
{
	Tree tree;
	Node root = &tree;

	root = createEmptyTree(root);
	root = insertNode(root, 5);
	root = insertNode(root, 7);
	root = insertNode(root, 4);
	root = insertNode(root, 2);
	root = insertNode(root, 9);
	root = insertNode(root, 11);
	root = insertNode(root, 1);
	root = insertNode(root, 18);

	printTree(root);

	printf("\n");

	root = deleteNode(root, 9);

	printTree(root);

	return 0;
}


Node createEmptyTree(Node p) {
	if (p != NULL)
		return NULL;
	else{
		createEmptyTree(p->right);
		createEmptyTree(p->left);
		free(p);
	}
	return NULL;
}

Node insertNode(Node p, int el) {
	if (p == NULL) {
		p = (Node)malloc(sizeof(Tree));
		if (p == NULL) {
			perror("Error allocating memory!\n");
			return NULL;
		}
		p->el = el;
		p->right = NULL;
		p->left = NULL;
	}

	else if (p->el > el)
		p->left = insertNode(p->left, el);
	else
		p->right = insertNode(p->right, el);
	return p;
}

int printTree(Node p) {
	if (p != NULL) {
		printTree(p->left);
		printf("%d ", p->el);
		printTree(p->right);
	}

	return 0;
}

Position findMin(Node p) {
	if (p == NULL) {
		printf("Element doesn't exist!\n");
		return NULL;
	}
	
	else if (p->left == NULL)
		return p;
	else
		return findMin(p->left);
}

Position findMax(Node p) {
	if (p != NULL) {
		while(p->right != NULL)
			p = p->right;
		return p;
	}
	else
		return p;
}

Position find(Node p, int el) {
	if (p == NULL) {
		printf("Element doesn't exist!\n");
		return NULL;
	}

	else if (p->el > el)
		return find(p->left, el);
	else if (p->el < el)
		return find(p->right, el);
	else
		return p;
}

Node deleteNode(Node p, int el) {
	Position temp = NULL;

	if (p == NULL)
		return NULL;
	else if (p->el > el)
		p->left = deleteNode(p->left, el);
	else if (p->el < el)
		p->right = deleteNode(p->right, el);
	else if (p->right && p->left != NULL) {
		temp = findMin(p->right);
		p->el = temp->el;
		p->right = deleteNode(p->right, p->el);
	}
	else {
		temp = p;
		if (p->left == NULL)
			p = p->right;
		else
			p = p->left;
		free(temp);
	}

	return p;
}
