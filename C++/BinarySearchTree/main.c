#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#include <stdio.h>
#include "PricingBST.h"

int main(){
	bstnode* root = NULL;
	int barcodeA=239876;
	int barcodeB=789654;
	int barcodeC=456783;
	int barcodeD=335497;
	int barcodeE=145682;
	int barcodeDuplicate=239876; /* duplicate of barcodeA */
	printf("1. Testing insertion of tree nodes:\n");
	printf("===================================\n");
	insertnodeBST(&root,barcodeA);
	displayBSTInOrder(stdout, root, 0);
	insertnodeBST(&root,barcodeB);
	displayBSTInOrder(stdout, root, 0);
	insertnodeBST(&root,barcodeC);
	displayBSTInOrder(stdout, root, 0);
	insertnodeBST(&root,barcodeD);
	displayBSTInOrder(stdout, root, 0);
	insertnodeBST(&root,barcodeE);
	displayBSTInOrder(stdout, root, 0);
	printf("2. Testing insertion exceptions:\n");
	printf("================================\n");
	insertnodeBST(&root,barcodeDuplicate);
	insertnodeBST(NULL,barcodeDuplicate);
	printf("3. Testing removal of tree nodes:\n");
	printf("=================================\n");
	removenodeBST(&root,barcodeA);
	displayBSTInOrder(stdout, root, 0);
	removenodeBST(&root,barcodeB);
	displayBSTInOrder(stdout, root, 0);
	removenodeBST(&root,barcodeC);
	displayBSTInOrder(stdout, root, 0);
	printf("4. Testing removal exceptions:\n");
	printf("==============================\n");
	removenodeBST(NULL,barcodeC); 
	removenodeBST(&root,barcodeC); /*duplicate removal*/
	removenodeBST(&root,123); /* removal of inexisting item */
	printf("\n");
	/* re-inserting node with barcode A and node with barcode B */
	insertnodeBST(&root,barcodeA);
	insertnodeBST(&root,barcodeB);
	displayBSTInOrder(stdout, root, 0);
	printf("5. Testing price updating:\n");
	printf("==========================\n");
	updatePrice(root,barcodeA,"Colruyt",20.3);
	updatePrice(root,barcodeA,"Delhaize",22.8);
	updatePrice(root,barcodeA,"Carrefour",21.7);
	displayBSTInOrder(stdout, root, 0);
	updatePrice(root,barcodeB,"Carrefour",13.7);
	updatePrice(root,barcodeB,"Carrefour",12.7);
	displayBSTInOrder(stdout, root, 0);
	printf("Testing pricing EXCEPTIONS:\n");
	printf("===============================\n");
	updatePrice(NULL,barcodeA,"Colruyt",20.3);
	updatePrice(root,123,"Colruyt",20.3);
	printf("\n");
	printf("Testing file output:\n");
	printf("====================\n");
	exportToFile(root, "bstFileOutput.txt");
	printFile(stdout, "bstFileOutput.txt");
	printf("Testing file output EXCEPTIONS:\n");
	printf("===============================\n");
	exportToFile(NULL, "bstFileOutput.txt");
	exportToFile(root, "bstFileOutput.txt"); /* output to existing file */
	printf("\n");
	printf("Testing BST memory release:\n");
	printf("===========================\n");
	freeBST(&root);
	displayBSTInOrder(stdout, root, 0);
	printf("\n");
	#ifdef _MSC_VER
	if(_CrtDumpMemoryLeaks())
		printf("MEMORY LEAKS FOUND\n") ;
	else
		printf("BST memory properly released\n\n");
	#endif
	printf("Press ENTER to continue\n");
	getchar();
	return 0;
}
