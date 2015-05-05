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

struct AVLNode* _addNode(struct AVLNode* cur, void* val, comparator compare){
	struct AVLNode* newNode = 0;
	if(cur == 0) /* BASE CASE */
	{
		*/ Create a new one and return it */
		newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
		assert(newNode != 0);
		newNode->left = newNode->right = 0;
		newNode->val = val;
		newNode->hght = 0;	/* or SetHeight on newNode */
		return newNode;
	}else{	/* RECURSIVE CASE */
		if((*compare)(val, cur->val) < 0){
			cur->left = _addNode(cur->left, val, compare);	/* Functional approach, rebuild subtree */
		}else{
			cur->right = _addNode(cur->right, val, compare);
		}
	}
	return _balance(cur);
}

void addAVLTree(struct AVLTree* tree, void* val, comparator compare){
	tree->root = _addNode(tree->root, val, compare);
	tree->size++;
}

int containsAVLTree(struct AVLTree* tree, void* val, comparator compare){
	/* cur == iter */
	struct AVLNode* cur;
	cur = tree->root;
	
	while(cur != 0){
		if((*compare)(cur->val, val) == 0){
			return 1;
		}else if ((*compare)(cur->val, val) < 0){
			cur = cur->left;
		}else{	
			cur = cur->right;
		}
	}
	return 0;
}

void* _leftMost(struct AVLNode* cur){
	while(cur->left != 0){
		cur = cur->left;
	}
	return cur->val;
}

