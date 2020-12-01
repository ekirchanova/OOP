#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h >
#include < assert.h >
typedef struct btree_entry
{
	BTreeItem *Item;
	struct btree_entry *left;
	struct btree_entry*right;
	struct btree_entry * parent;

}btree_entry;
typedef struct bintree {
	size_t keySize;
	size_t valueSize;
	size_t count;
	int(*compare)(const void*, const void *);
	btree_entry *root;
}binarytree;
static void replace_children(btree_entry* parent, btree_entry *child, btree_entry*new_child, int(*compare)(const void *, const void *)) {
	if (compare((parent->Item)->key, (child->Item)->key) == 1)
	{
		parent->right = new_child;
	}
	else {
		parent->left = new_child;
	}
}
static void delete_el(binarytree *btree, btree_entry *temp, void(*destroy)(void*)) {

	destroy((temp->Item));
	free(((temp->Item))->key);
	free(((temp->Item))->value);
	free(temp->Item);
	free(temp);
	btree->count--;
	if (btree_count(btree) == 0)
		btree->root = NULL;
}
static void replace_root(binarytree *btree, btree_entry* new_root) {
	btree->root = new_root;
	btree->root->parent = NULL;
}
btree_entry*leftest(btree_entry *current);
static btree_entry* delete_one_element(binarytree *btree, btree_entry *temp, void(*destroy)(void*))
{
	int cmp_root = btree->compare((temp->Item)->key, (btree->root->Item)->key);
	if (temp == NULL) {
		return NULL;
	}
	btree_entry*node = NULL;
	if (temp->left == temp->right) {
		node = NULL;
	}
	else if (temp->right==NULL) {
		node = temp->left;
	}
	else if (temp->left==NULL) {
		node = temp->right;
	}
	else if (temp->left&&temp->right) {

			btree_entry* replacement = leftest(temp);
			int c = btree->compare((replacement->Item)->key, (replacement->parent->Item)->key);
			if (c<0)
				replacement->parent->right = replacement->right;
			else
				replacement->parent->left = replacement->right;
			if (replacement->right)
				replacement->right->parent = replacement->parent;
			replacement->parent = temp->parent;
			replacement->left = temp->left;
			replacement->right = temp->right;
			temp->left->parent = replacement;
			if (temp->right)
				temp->right->parent = replacement;			
			node = replacement;
	}
	delete_el(btree, temp, destroy);
	if (cmp_root == 0)
		btree->root = node;
	return node;
}

static btree_entry* find_element(btree_entry*tree_node, const  void * key, int(*compare)(const void*, const void*)) {
	if (tree_node == NULL) return NULL;
	int c = compare((tree_node->Item)->key, key);
	if (c == 0) return tree_node;
	if (c < 0) return find_element(tree_node->left, key, compare);
	return find_element(tree_node->right, key, compare);
}

void * btree_create (size_t keySize, size_t valueSize,int(*compare)(const void*, const void* ))
{
	if ((keySize == 0) || (compare == NULL) || (valueSize == 0)) {
		return NULL;
	}
	binarytree *tree;
	tree = (binarytree*)malloc(sizeof(binarytree));
	assert(tree);
	tree=(binarytree*)btree_init(tree, keySize, valueSize, compare);
	return tree;
}
void * btree_init(void *tree, size_t keySize, size_t valueSize, int(*compare)(const void*, const void*))
{
	if ((keySize == 0) || (compare == NULL) || (valueSize == 0)) {
		return NULL;
	}
	binarytree *btree = (binarytree*)tree;
	btree->keySize = keySize;
	btree->valueSize = valueSize;
	btree->count = 0;
	btree->compare = compare;
	btree->root = NULL;
	return tree;
}
void * add_new_element(binarytree *btree, const void*key,btree_entry *parent) {

	btree_entry * new_element;
	new_element = (btree_entry*)malloc(sizeof(btree_entry));
	assert(new_element);
	new_element->Item =(BTreeItem*) malloc(sizeof(BTreeItem));
	new_element->Item->key = malloc(btree->keySize);
	memcpy(new_element->Item->key, key, btree->keySize);
	new_element->Item->value = malloc(btree->valueSize);
	new_element->left = NULL;
	new_element->right = NULL;
	new_element->parent = parent;
	btree->count++;
	return new_element;
}
void * btree_insert(void *tree, const void*key, bool * createFlag)
{
    if ((tree == NULL) || (key == NULL) || (createFlag == NULL))
    {
        if (createFlag)
            *createFlag = false;
        return NULL;
    }
	binarytree *btree = (binarytree*)tree;
	btree_entry * temp;
	if (btree->count == 0)
	{
		btree->root = (btree_entry *)add_new_element(btree, key,NULL);
		*createFlag = true;
		return btree->root->Item->value;
	}
	if (temp= (btree_entry * )find_element(btree->root, key,btree->compare)) {
		if (createFlag)
			*createFlag = false;
		return temp->Item->value;
	}
	temp = btree->root;
	while (temp != NULL)
	{
		if (btree->compare(key, temp->Item->key) == 1)
		{
			if (temp->left == NULL)
			{
				temp->left =( btree_entry * )add_new_element(btree,key,temp);
				*createFlag = true;
				return temp->left->Item->value;
			}
			temp = temp->left;
		}
		else if (btree->compare(key, temp->Item->key) == -1)
		{
			if (temp->right == NULL)
			{
				temp->right = (btree_entry *) add_new_element(btree, key, temp);
				*createFlag = true;
				return temp->right->Item->value;
			}
			temp = temp->right;
		}
	}
	return NULL;
}
size_t btree_count(const void*tree) {
	if (tree != NULL) {
		binarytree *btree = (binarytree*)tree;
		return (size_t)btree->count;
	}
	return -1;
}
void destroy_all_list(btree_entry* list, void(*destroy)(void*))
{
	if (list==NULL) return;
	if (list->left != NULL) {
		destroy_all_list(list->left, destroy);
	}
	if (list->right != NULL) {
		destroy_all_list(list->right, destroy);
	}
	destroy(list->Item);
	free((void*)list->Item->key);
	free((void*)list->Item->value);
	free(list->Item);
	free(list);

}
void btree_clear(void* btree, void(*destroy)(void*))
{
	if ((btree != NULL) && (destroy != NULL)) {
		binarytree *tree = (binarytree*)btree;
		destroy_all_list(tree->root, destroy);
		tree->count = 0;
		tree->root = NULL;
	}
}
void btree_destroy(void*tree, void(*destroy)(void*))
{
	if ((tree != NULL) && (destroy != NULL)) {
		binarytree *btree = (binarytree*)tree;
		if (btree->root!=NULL&&btree->count!=0) {
			destroy_all_list(btree->root, destroy);
		}
		free(btree);
	}
}

void * btree_item(const void*tree, const  void * key)
{
	if ((tree != NULL) && (key != NULL)) {
		binarytree *btree = (binarytree*)tree;
		btree_entry *temp =(btree_entry*) find_element(btree->root,key,btree->compare);
		if(temp)
		return temp->Item->value;
	}
		return NULL;
}
void btree_remove(void*tree, const void*key, void(*destroy)(void*))
{
	if ((tree == NULL) || (destroy == NULL) || (key == NULL)) return;
	binarytree *btree = (binarytree*)tree;
	btree_entry *parent=NULL;
	int c;
	btree_entry *temp =( btree_entry * )find_element(btree->root, key,btree->compare);
	if (temp != NULL) {
		parent = temp->parent;
		if (temp->parent)
			c = btree->compare((temp->Item)->key, (temp->parent->Item)->key);
		temp = delete_one_element(btree, temp, destroy);
	}
	if (temp != NULL) {
		temp->parent = parent;
	}
		if (parent) {
			if (c > 0)
				parent->left = temp;
			else
				parent->right = temp;
		}
	
	
}
size_t btree_first(const void *tree) 
{
	if (tree != NULL) {
		binarytree *btree = (binarytree*)tree;
		if (btree->count != 0) {
			btree_entry *temp = btree->root;
			while (temp->right != NULL) {
				temp = temp->right;
			}
			return (size_t)temp;
		}
	}
	return btree_stop(tree);
}
size_t btree_last(const void*tree)
{
	if (tree != NULL) {
		binarytree *btree = (binarytree*)tree;
		if (btree->root != 0) {
			btree_entry *temp = btree->root;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			return (size_t)temp;
		}
	}
    return btree_stop(tree);
}
btree_entry* grandparent(btree_entry* node, int direction) {
	btree_entry* current = node;
	if (direction == 0) {
		while (current->parent != NULL && current->parent->parent != NULL && current->parent->parent->left != current->parent) {
			current = current->parent;
		}
		return current->parent->parent;
	}
	if (direction == 1) {
		while (current->parent != NULL && current->parent->parent != NULL && current->parent->parent->right != current->parent) {
			current = current->parent;
		}
		return current->parent->parent;
	}
	else return NULL;
}
btree_entry*rightest(btree_entry *current) {
	btree_entry *temp = current->left;
	while (temp->right)
		temp = temp->right;
	return temp;
}
btree_entry*leftest(btree_entry *current) {
	btree_entry *temp = current->right;
	while (temp->left)
		temp =temp->left;
	return temp;
}
size_t btree_next(const void*tree,size_t item_id)
{
	if ((tree == NULL) || (item_id == 0)) {
		return btree_stop(tree);
	}
	if (btree_last(tree) == item_id) return btree_stop(tree);
	binarytree *btree = (binarytree*)tree;
	btree_entry *temp = (btree_entry*)item_id;
	if (btree->count <= 1) {
		return btree_stop(btree);
	}
	if (temp->parent) {
		if (btree->compare(temp->parent->Item->key, temp->Item->key) == 1 && temp->left == NULL)
			return (size_t)temp->parent;
		else if (btree->compare(temp->parent->Item->key, temp->Item->key) == 1 && temp->left != NULL)
			return (size_t)rightest(temp);
		else if ((btree->compare(temp->parent->Item->key, temp->Item->key) == -1)) {
			if (temp->left) return (size_t)rightest(temp);
			return (size_t)grandparent(temp, 1);
		}
	}
	 if (temp->left )
		 return (size_t)rightest(temp);
    return btree_stop(tree);
}

size_t btree_prev(const void *tree, size_t item_id)
{
	if ((tree == NULL) || (item_id == 0)) {
		return btree_stop(tree);
	}
	binarytree *btree = (binarytree*)tree;
	btree_entry *temp = (btree_entry*)item_id;
	if (btree->count <= 1) {
		return btree_stop(btree);
	}
	if (temp->right &&temp->right->left != NULL)
		return (size_t)leftest(temp);
	if (temp->parent != NULL && (btree->compare(temp->parent->Item->key, temp->Item->key) == -1))
		return (size_t)temp->parent;
	else if (temp->right != NULL)
		return (size_t)temp->right;
	else if (temp->parent != NULL && (btree->compare(temp->parent->Item->key, temp->Item->key) == 1))
		return (size_t)grandparent(temp, 0);
    return btree_stop(tree);
}
size_t btree_stop(const void *tree) {
	if (tree != NULL) {
		return (size_t)NULL;
	}
	return (size_t)-1;
}
void * btree_current (const void * tree,size_t item_id)
{
	if ((tree != NULL) && (item_id != 0)) {
		btree_entry *temp = (btree_entry*)item_id;
		return temp->Item;
	}
	return NULL;
}
void btree_erase(void * tree, size_t item_id, void(*destroy)(void*)) {
	if ((tree != NULL) && (item_id != 0) && (destroy != NULL)) {
		binarytree *btree = (binarytree*)tree;
		btree_entry *temp = (btree_entry*)item_id;
		temp=delete_one_element(btree, temp, destroy);
	}
}

