#include <iostream>
#include "tree_node.h"

int list_count(tree_node *root) {
	if (!root)
		return 0;
	if (!root->get_left() && !root->get_right())
		return 1;
	return list_count(root->get_left()) + list_count(root->get_right());
}

int maxDepth(tree_node *root) 
{
	if (!root)
		return 0
	
    int lDepth = maxDepth(root->get_left());
    int rDepth = maxDepth(root->get_right());
	if (lDepth > rDepth) 
		return(lDepth + 1);
	else 
		return(rDepth + 1);
	}
}

int level_max_count(tree_node *root)
{
	int d = maxDepth(root);
	if (!d) return 0;
	vector<int> cnt(d + 1);
	
	function<void(tree_node *, int)> dfs = [&] (tree_node *root, int deep) {
		if (!root) return;
		++cnt[deep];
		dfs(root->get_left(), deep + 1);
		dfs(root->get_right(), deep + 1);
	}; 
	dfs(root, 0);
	return *std::max_element(cnt.begin(), cnt.end());
}

int one_son_count(tree_node *root)
{
    if (!root)
        return 0;
    if (!root->get_left() && root->get_right())
		return (one_son_count(root->get_right()) + 1);
    if (root->get_left() && !root->get_right())
        return (one_son_count(root->get_left()) + 1);
	return one_son_count(root->get_left()) + one_son_count(root->get_right());
}
