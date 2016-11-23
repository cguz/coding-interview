#include "PricingBST.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* create price for a given shop */
pricing* createPrice(double price, char* shopname) {
	pricing *temp =  malloc(sizeof(pricing));
	temp->price = price;
   	temp->shopname = shopname;
   	return temp;
}

/* find for the price of a given shop, NULL if it does not exist */
pricing* findPrice(bstnode* node, char* shopname){

	int i;
	pricing* temp = NULL;

	if(node->nr_of_prices != 0){
		for(i=0; i < node->nr_of_prices; i++){
			temp = node->pl[i];
			if(strcmp(temp->shopname, shopname)==0){
				return temp;
			}
			temp = NULL;
		}
	}

	return temp;
}

/* display given price to given output stream (stdout, sterr, file, etc.) */
void displayPrice(FILE* output, pricing* shop){

	if(shop != NULL){
		fprintf(output, "Price: %f \n", shop->price);
		fprintf(output, "Shop: %s \n", shop->shopname);
	}

}

/* free given pricing */
void freePrice(bstnode* node){
	
	if(node->nr_of_prices != 0){
		int i;
		for(i=0; i < node->nr_of_prices; i++){
			free(node->pl[i]);
			node->pl[i] = NULL;
		}
	}
	node->nr_of_prices = 0;
	free(node->pl);

}

/* create node with given ID, return created node or NULL if creation failed */
bstnode* createNode(int id) {
	bstnode *temp =  malloc(sizeof(bstnode));
	temp->id = id;
	temp->nr_of_prices = 0;
	temp->pl = malloc(sizeof(pricing));
   	temp->left = temp->right = temp->parent = NULL;
   	return temp;
}

/* free given node */
void freeNode(bstnode** node) {

	/* free the price */
	freePrice((*node));	

	/* free the node */
	free(*node);
	(*node) = NULL;
}

/* recursively frees all memory taken up by the BST with given root */
void freeBST(bstnode** root) {
	
    if ((*root) != NULL)
	{
		/* we recu free the left subtree if it is not NULL */
    	if ((*root)->left != NULL)
    		freeBST(&((*root)->left));
    
		/* we recu free the right subtree if it is not NULL */
    	if ((*root)->right != NULL)
    		freeBST(&((*root)->right));
    
		/* we free the node */ 
    	freeNode(&(*root));
    }
        
}

/* display given node to given output stream (stdout, sterr, file, etc.) */
void displayNode(FILE* output, bstnode* node, int treedepth){

	fprintf(output, "BSTNode at address: 00%08X at tree depth: %d \n", node, treedepth);
	fprintf(output, "Left child: 00%08X \n", node->left);
	fprintf(output, "Right child: 00%08X \n", node->right);
	fprintf(output, "Parent: 00%08X \n", node->parent);
	fprintf(output, "ID: %d \n", node->id);

	if(node->nr_of_prices != 0){
		fprintf(output, "Pricelistings: \n");

		int i;
		for(i=0; i < node->nr_of_prices; i++){
			displayPrice(output, node->pl[i]);
		}
	}

	fprintf(output, "\n");

}

/* finds node with given id in BST with given root. If node does not exist in tree: returns NULL */
bstnode* findnodeBST(bstnode* root, int id){

	/* default cases: root is null or we found the id */
	if(root == NULL || root->id == id)
		return root;

	// if key is greater that root's id, we go to the rigth
	if(root->id < id)
		return findnodeBST(root->right, id);

	// otherwise, we go to the left (the id is smaller than the root's id)
	return findnodeBST(root->left, id);

}

/* insert recu a node, in the BST from the parent node. */
void insert(bstnode** parent, bstnode* node){

	/* if the id is less or equal than the parent, we go to the left */
	if (node->id <= (* parent)->id){

		if((*parent)->left == NULL){
			(*parent)->left = node;
		}else{
   	   		insert(&((*parent)->left), node);
		}

		/* we save the parent */
		(*parent)->left->parent = (*parent);

	}else{

		/* otherwise, we go to the right */
		if ((*parent)->right == NULL){
			(*parent)->right = node;
		}else{
			insert(&((*parent)->right), node);
		}
		
		/* we save the parent */
		(*parent)->right->parent = (*parent);

	}
}


/* creates / inserts a node with given id, in BST with given root. Assuming no duplicate items / IDs get added to the BST */
void insertnodeBST(bstnode** root, int id){

	bstnode* node;

	/* if root does not point to memory location zero */
	if(root){ 

		/* we create the node to insert */
		node = createNode(id);
		if(node == NULL){
			printf("[ERROR] THE NODE CAN NOT BE CREATED - MEMORY ALLOCATION.\n");
			return;
		}

		/* if the BST is empty, we create the root */
		if ((*root) == NULL){
			(*root) = node;
			return;
 		}
	
		/* if node already exist, we do not do anything */
		bstnode* temp = findnodeBST((*root), id);
		if(temp != NULL){
			printf("[EXCEPTION] THE BARCODE ALREADY EXIST.\n");
			freeBST(&node);
			return;
		}

		/* otherwise, we insert the node in the BST */
	 	insert(&(*root), node);
	
	}else{
		printf("[EXCEPTION] THE ROOT POINTS TO MEMORY LOCATION ZERO.\n");
	}
}

/* updates price for given ID and shop if price already exists in BST with given root, or adds a new pricing (price + shopname) to the pricelist  if this shop has no price listed yet */
void updatePrice(bstnode* root, int id, char* shop, double price){

	bstnode* node = findnodeBST(root, id);
	
	if(node != NULL){
	
		/* we search for the shop */
		pricing* temp = findPrice(node, shop);

		/* if the price shop does not exist, we create it */
		if(temp == NULL){
			temp = createPrice(price, shop);
			if(temp == NULL){
				printf("[ERROR] THE PRICE CAN NOT BE CREATED - MEMORY ALLOCATION.\n");
				return;
			}
			node->pl[node->nr_of_prices] = temp;
			node->nr_of_prices++;
			// free(temp);
		}else{
			/* otherwise, we update the price */
		    temp->price = price;	
		}	
			
	}

}

/* displays BST in order */
void displayBSTInOrder(FILE* output, bstnode* root, int treedepth){
	
	if(root != NULL){

		displayBSTInOrder(output, root->left, treedepth+1);

		/* display the information of the node */
		displayNode(output, root, treedepth);

		displayBSTInOrder(output, root->right, treedepth+1);

	}

}

/* help function which swaps data of two given nodes */
void swapNodeData(bstnode** node1, bstnode** node2){

	int id = (*node1)->id;
	int nr_of_prices = (*node1)->nr_of_prices;
	pricing** pl = (*node1)->pl;
	
	(*node1)->id = (*node2)->id;
	(*node1)->nr_of_prices = (*node2)->nr_of_prices;
	(*node1)->pl = (*node2)->pl;
	
	(*node2)->id = id;
	(*node2)->nr_of_prices = nr_of_prices;
	(*node2)->pl = pl;

}

/* help function which tries to find the successor to a given node or NULL if the node has no successor in the BST */
bstnode* findSuccessorNode(bstnode* node){
	
	bstnode* current = NULL;

	/* If the node has a right child, then the follower of a node is the smallest */
	if(node->right != NULL){

	 	current = node->right;

		while(current->left != NULL)
			current = current->left;
	
		return current;

	}

	/* If the node has no children */
	if(node->left == NULL && node->right == NULL){
		current = node->parent;
	
		while(current->right == node){
			current = current->parent;
		}

		return current;
	}

}

/* change the link of the parent node */
void removeLinkParent(bstnode* node, bstnode* toLink){

	bstnode* parent = node->parent;
	
	if(parent->left == node)
		parent->left = toLink;
	else
		parent->right = toLink;

}

/* removes a node with given ID from BST with given root */
void removenodeBST(bstnode** root, int id){
	
	bstnode* node;
	bstnode* temp; 

	/* if root does not point to memory location zero */
	if(root){
 
		node = findnodeBST((*root), id);

		/* if node is not found, return */
		if(node == NULL){
			printf("[EXCEPTION] THE BARCODE DOES NOT EXIST.\n");
			return;
		}

		/* if the node has no child */	
		if(node->left == NULL && node->right == NULL){

			if(node == *root){
				freeNode(&(*root));
				return;
			}

			/* we remove the link from the parent node */
			removeLinkParent(node, NULL);

			/* we free the node */ 
		    	freeNode(&node);

			return;

		}

		/* if the node is with one child */	
		if(node->left == NULL){
		
			if(node == *root){
				root = &((*root)->right);

				freeNode(&((*root)->right));
				return;
			}
		
			/* make the parent point to the right child */
			removeLinkParent(node, node->right);
			node->right->parent = node->parent;


			/* we free the node */ 
		    freeNode(&node);

			return;
		}

		if(node->right == NULL){
			if(node == *root){
				root = &((*root)->left);

				freeNode(&((*root)->left));
				return;	
			}

			/* make the parent point to the left child */
			removeLinkParent(node, node->left);
			node->left->parent = node->parent;
				
			/* we free the node */ 
    			freeNode(&node);
	
			return;
		}
		
		/* node with two children */
				
		/* findSuccessorNode */
		temp = findSuccessorNode(node);
		
		/* swap the data of the to-be-removed node with the follower*/
		swapNodeData(&node, &temp);

		/* call removenodeBST on the follower node */		
		removenodeBST(&(node->right), temp->id);
	
	}else{
		printf("[EXCEPTION] THE ROOT POINTS TO MEMORY LOCATION ZERO.\n");
	}
}


void exportToFile(bstnode* root, char* outputFileName){
	/* if root does not point to memory location zero */
	if(root){
		/* if the file exists, we do nothing */
		if(access(outputFileName, F_OK) != -1){
			printf("[EXCEPTION] THE FILE EXISTS.\n");
			return;
		}
	
		FILE* file = fopen(outputFileName, "w+");
		displayBSTInOrder(file, root, 0);
		fclose(file);
	}else{
		printf("[EXCEPTION] THE ROOT POINTS TO MEMORY LOCATION ZERO.\n");
	}
}


void printFile(FILE* stream, char* fileName){
		
	FILE *f;
	char c;
	f = fopen(fileName, "rt");
	
	while((c=fgetc(f))!=EOF){
		fprintf(stream, "%c", c);
	}

	fclose(f);
}
