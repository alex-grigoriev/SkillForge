#include "village.h"

int main()
{
	Tree* tree = new Tree();
	int value1 = 0, value2 = 0, count = 0;
	string name = "none";
	
	count = init(tree, count);
	cout << "\nInput name for search: ";
	cin >> name;
	
	for (int i = 0; i < count; ++i)
	{
		Branch* name_At = tree->getNameAt(i);
		Branch* tree_At = tree->getTreeAt(i);
		Branch* branch_1 = tree->getBranch1Tree(i);
		Branch* branch_2 = tree->getBranch2Tree(i);
		
		if (name == name_At->getName())
		{
			value1 = tree_At->getTree();
			value2 = branch_1->getBranch1();
			search(tree, value1, value2, count);			
		}
	}
	delete tree;
}
