#ifndef	__AVL_H
#define __AVL_H

/* 
	File: avl.h
	Interface definition of the AVL tree data structure
*/

struct AVLTree;
typedef int (*comparator)(void* left, void* right);
typedef void(*printer)(void* node);

/* INITIALIZE BINARY SEARCH TREE STRUCTURE */
void initAVLTree(struct AVLTree* tree);

/* ALLOCATE AND INITIALIZE SEARCH TREE STRUCTURE */
struct AVLTree* newAVLTree();

/* DEALLOCATE NODES IN BST  */
void clearAVLTree(struct AVLTree* tree);

/* BST BAG INTERFACE */

int isEmptyAVLTree(struct AVLTree* tree);
int sizeAVLTree(struct AVLTree* tree);

void addAVLTree(struct AVLTree* tree, void* val, comparator compare);
int contatinsAVLTree(struct AVLTree* tree, void* val, comparator compare);
void removeAVLTree(struct AVLTree* tree, void* val, comparator compare);

/*  UTILITY FUNCTION TO PRINT A TREE  */
void printTree(struct AVLTree* tree, printer printVal);

#endif	//__AVL_H
