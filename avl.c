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
	struct AVLNode* root;
	int size;
};

void _initAVLTree(struct AVLTree* tree){
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
int _balanceFactor(struct AVLNode* cur);

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
		/* Create a new one and return it */
		newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
		assert(newNode != 0);
		newNode->left = newNode->right = 0;
		newNode->val = val;
		newNode->hght = 0;	/* or SetHeight on newNode */
		return newNode;
	}else{	/* RECURSIVE CASE */
		/* IF QUERY VAL < CUR NODE VAL THEN TRAVERSE LEFT */
		/* ELSE IF QUERY VAL > CUR NODE VAL THEN TRAVERSE RIGHT */ 
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

struct AVLNode* _removeLeftMost(struct AVLNode* cur){
	struct AVLNode* newLeftMost = 0;
	if(cur->left != 0){
		cur->left = _removeLeftMost(cur->left);
		return _balance(cur);		/* HEIGHT BALANCE UPDATED TREE POST NODE REMOVAL */
	}

	newLeftMost = cur->right;
	free(cur);
	return newLeftMost;
} 

struct AVLNode* _removeNode(struct AVLNode* cur, void* val, comparator compare){
	struct AVLNode* newNode = 0;
	
	if((*compare)(val, cur->val) == 0){
		if(cur->right != 0){
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftMost(cur->right);
			return _balance(cur); /* could remove this since there's a return at the end */
		}else{
			newNode = cur->left;
			free(cur);
			return newNode;
		}
	}else if((*compare)(val, cur->val) < 0){	
		cur->left = _removeNode(cur->left, val, compare);
	}else{
		cur->right = _removeNode(cur->right, val, compare);
	}
	return _balance(cur);
}

void removeAVLTree(struct AVLTree* tree, void* val, comparator compare){
	if(containsAVLTree(tree, val, compare)){
		tree->root = _removeNode(tree->root, val, compare);
		tree->size--;
	}
}

/* UTILITY FUNCTION TO DETERMINE THE HEIGHT OF A NODE */
int _height(struct AVLNode* cur){
	if(cur == 0){ return -1; }
	return cur->hght;
}

/* UTILITY FUNCTION TO SET THE HEIGHT OF A NODE */
/* IF LH PATH < RH PATH HEIGHT = RH + 1;   */
void _setHeight(struct AVLNode* cur){
	int lh = _height(cur->left);
	int rh = _height(cur->right);
	if(lh < rh){
		cur->hght = (rh + 1);
	}else{
		cur->hght = (lh - 1);
	}
}	

/* UTILITY FUNCTION TO COMPUTE THE BALANCE FACTOR OF A NODE */
int _balanceFactor(struct AVLNode* cur){
	return (_height(cur->right) - _height(cur->left));
}

struct AVLNode* _balance(struct AVLNode* cur){
	int cbf = _balanceFactor(cur);
	if(cbf < -1){ /* CUR IS HEAVY ON THE LEFT */
		if(_balanceFactor(cur->left) > 0){	/* CHECK FOR DOUBLE ROTATION ie IS THE LEFTCHILD HEAVY ON THE RIGHT? */
			cur->left = _rotateLeft(cur->left);	/* yes th left child was heavy on the right side , so rotate child to the left first */
		}
		return _rotateRight(cur);
	}else if(cbf > 1){
		if(_balanceFactor(cur->right) < 0){
			cur->right = _rotateRight(cur->right);
		}
		return _rotateLeft(cur);
	}

	/* ONCE ROTATION IS DONT, WE MUST SE THE HEIGHTS APPROPRIATELY */

	_setHeight(cur);
	return cur;
}

struct AVLNode* _rotateLeft(struct AVLNode* cur){
	struct AVLNode* newTop = 0;
	newTop = cur->right;
	cur->right = newTop->left;
	newTop->left = cur;

	/* RESET THE HEIGHTS FOR ALL NODES THAT HAVE CHANGES HEIGHTS */
	_setHeight(cur);
	_setHeight(newTop);
	
	return cur;
}

struct AVLNode* _rotateRight(struct AVLNode* cur){
	struct AVLNode* newTop = 0;
	newTop = cur->left;
	cur->left = newTop->right;
	newTop->right = cur;

	/* RESET THE HEIGHTS FOR ALL NODES THAT HAVE CHANGES HEIGHTS */
	_setHeight(cur);
	_setHeight(newTop);
	
	return cur;
}

int main(){


return 0;
}
