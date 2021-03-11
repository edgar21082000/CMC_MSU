#include "student.h"
#ifndef TREE_NODE_H
#define TREE_NODE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//class tree;

class tree_node: public student
{
	private:
		tree_node*left = 0;
		tree_node*right = 0;
	public:
		
		friend class tree;// открываем доступ к приватным функциям
		tree_node *get_right() const {return right;}
		void set_right(tree_node*right){this->right = right;}
		tree_node *get_left() const {return left;}
		void set_left(tree_node*left){this->left = left;}
};

#endif
