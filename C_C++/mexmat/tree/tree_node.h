#ifndef TREE_NODE_H
#define TREE_NODE_H
#include "student.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class tree;

class tree_node
{
	private:
		student data;
		tree_node *left = 0;
		tree_node *right = 0;
	public:
		tree_node *get_left() { return left; }
		tree_node *get_right() { return right; }
};

int list_count(tree_node *root);
int maxDepth(tree_node *root);
int level_max_count(tree_node *root);

int one_son_count(tree_node *root); 

#endif
