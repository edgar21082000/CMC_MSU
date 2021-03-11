#ifndef TREE_H
#define TREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "student.h"

class tree_node;

class tree
{
	private:
		tree_node *root = 0;
		tree_node *current = 0;
	public:
        int read(FILE *fp);
        void delete_tree();
        tree_node *get_root() { return root; }
};

#endif
