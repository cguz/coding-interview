#ifndef _PRICINGBST
#define _PRICINGBST

#include <stdlib.h>
#include <stdio.h>

typedef struct _price {
	double price;
	char* shopname;
} pricing;

typedef struct _bstnode {
	int id;
	pricing** pl;
	int nr_of_prices;
	struct _bstnode *left;
	struct _bstnode *right;
	struct _bstnode *parent;
} bstnode;

void freeBST(bstnode** root);
void insertnodeBST(bstnode** root, int id);
void removenodeBST(bstnode** root, int id);
bstnode* findnodeBST(bstnode* root, int id);
void displayBSTInOrder(FILE* output, bstnode* root, int treedepth);
void updatePrice(bstnode* node, int id, char* shop, double price);
void exportToFile(bstnode* root, char* outputFileName);
void printFile(FILE* stream, char* fileName);


#endif _PRICINGBST
