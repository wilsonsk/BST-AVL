#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "avl.h"

struct AVLNode{
	void* val;
	struct AVLNode* left;
	struct AVLNode* right;
	int hght;
};

struct AVLTree{
	struct* AVLNode* root;
	int size;
};

void _initAVL(struct AVLTree* tree){
	tree->root = 0;
	tree->size = 0;
}

struct AVLTree* newAVLTree(){
	struct AVLTree* tree;
	tree = (struct AVLTree*)malloc(sizeof(struct AVLTree));
	assert(tree != 0);		
	_initAVLTree(tree);
	return tree;
}

/* Prototypes for private functions */
int _height(struct AVLNode* cur);
void _setHeight(struct AVLNode* cur);
int bf(struct AVLNode* cur);

struct AVLNode* _balance(struct AVLNode* cur);
struct AVLNode* _rotateLeft(struct AVLNode* cur);
struct AVLNode* _rotateRight(struct AVLNode* cur);

/****************************************************************************/

void _freeAVLTree(struct AVLNode* node){
	if(node != 0){
		_freeAVLTree(node->left);
		_freeAVLTree(node->right);
	}
	free(node);
}

void clearAVLTree(struct AVLTree* tree){
	_freeAVLTree(tree->root);
	tree->root = 0;
	tree->size = 0;
}

void freeAVLTree(struct AVLTree* tree){
	clearAVLTree(tree);
	free(tree);
}

int isEmptyAVLTree(struct AVLTree* tree){ return tree->size == 0 ; }

int sizeAVLTree(struct AVLTree* tree){ return tree-> size ; }

