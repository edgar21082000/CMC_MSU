#include "student.h"
//#include "list_node.h"
#ifndef TREE_H
#define TREE_H
#include "tree_node.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//class tree_node;

class tree
{
	private:
		tree_node *root = 0;
		tree_node *current = 0;
	public:
	
		void go_left(){current = current->left;}
		void go_right(){current = current->right;}
		void go_root(){current = root;}
		
		int add_left(tree_node* a);
		int add_right(tree_node* a);
		
		void delete_left();
		void delete_right();
		void delete_root();
		void delete_left_podder();
		void delete_right_podder();
		void delete_tree();
		void poisk(tree_node *a, tree_node *b);
		
		int read (FILE *fp);
        	tree_node * get_root(); 
        	void print_tree(int);
		
		int f();
		void kol(tree_node*a);
};

#endif
