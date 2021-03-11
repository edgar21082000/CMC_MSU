#include <iostream>
#include <stdlib.h>
#include "list.h"
#include "list_node.h"

void tree::delete_tree()
{
    tree_node *p = root
    std::function<void(tree_node *)> del = [&] (tree_node *cur) {
		if (!cur->get_left() && !cur->get_right()) 
        {
            delete root;
            return;
        }
        if (cur->get_left()) 
            del(cur->get_left());
        if (cur->get_right()) 
            del(cur->get_right()); 
	}; 
    del(p);
}

int read(FILE *fp)
{
    
    
}


