#include "tree.h"
#include "tree_node.h"
#define MAX_LVL 4

void tree::delete_tree()
{
	current = root;
	delete_left_podder();
	delete_right_podder();
	
	delete_root();	
	
	return;
}

void tree::delete_left()
{
	go_left();
	delete current;
}

void tree::delete_right()
{
	go_right();
	delete current;
}

void tree::delete_root()
{
	delete root;
}

void tree::delete_left_podder()
{	
	go_left();
	
	if(!current) return;
	
	delete_left_podder();
	delete_right_podder();
	
	delete current;
	
	return;
}

void tree::delete_right_podder()
{
	go_right();
	
	if(!current) return;
	
	delete_left_podder();
	delete_right_podder();
	
	delete current;
	
	return;
}

void tree::poisk(tree_node *a, tree_node *b)
{
	if(*b<*a)
	{
		go_left();/////????????????????????????????????????????go_left(a)
		if(current==NULL)///(a->left==NULL)
		{
			current=b;//a->left=b;
		}
		else
		{
			poisk(current,b);//poisk(a->left,b);
		}
		return;
	}
	else
	{
		go_right();//////////////////////////////////////////////////////
		if(current==NULL)//(a->right==NULL)
		{
			current=b;//a->right=b;
		}
		else
		{
			poisk(current,b);//poisk(a->right,b);
		}
		return;
	}
	return;
}

int tree::read (FILE*fp)
{
	delete_tree();
	int ret;
	
	tree_node *b;
	b = new tree_node;
	
	
	if(!b)return -1;
	
	b->right = 0;
	b->left = 0;
	
	ret = b->read(fp);
	if(ret<0)
	{
		
		delete b;
		if(ret==-1)return -2;
		if(ret==-2)return -1;
	}
	if(ret>0)//файл закончился empty
	{
		delete b;
		return 1;
	}
	
	root = current = b;
	
	for(;;)
	{
		b = new tree_node;
		if(!b)return -1;
		
		b->left = 0;
		
		ret = b->read(fp);
		if(ret==-1)//ошибка чтения
		{
			return -2;
		}
		if(ret==-2)//память
		{
			return -1;
		}
		if(ret>0)//файл закончился
		{
			delete b;
			return 0;
		}
		poisk(root,b);
	}
	return 0;//никогда
}

tree_node * tree::get_root()
{
    return (this->root);
}

void tree::print_tree(int level,tree_node*p)
{	
	int i=0;
	if(level>MAX_LVL)return;
	if(!p)return;
	
	for(i=0;i<level;i++)printf(" ");
	p->print(stdout);
	
	level++;
	print_tree(level,p->right);
	print_tree(level,p->left);
	
	return;   
}

int tree:: add_left(tree_node* a)
{
	current->left = new tree_node;
	if(!current->left)return -1;///memory
	
	*(current->left)=*a;
	
	return 1;	
}

int tree:: add_right(tree_node* a)
{
	current->right = new tree_node;
	if(!current->right)return -1;///memory
	
	*(current->right)=*a;
	
	return 1;	
}


int tree::f(tree_node*a)
{
	if(!a)return 0;
	
	if((!a->right)&&(!a->left))
	{
		return 1;
	}
	
	return f(a->right)+f(a->left);
}  