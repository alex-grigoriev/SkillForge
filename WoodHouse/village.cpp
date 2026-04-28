#include "village.h"

void Branch::setName(string value)
{
	name = value;
}

string Branch::getName()
{
	return name;
}

void Branch::setTree(int value)
{
	treeCount = value;
}

int Branch::getTree()
{
	return treeCount;
}

void Branch::setBranch1(int value)
{
	branch1 = value;
}

int Branch::getBranch1()
{
	return branch1;
}

void Branch::setBranch2(int value)
{
	branch2 = value;
}

int Branch::getBranch2()
{
	return branch2;
}

int Branch::getNumber()
{
	for (int i = 0; i < tree->getCount(); ++i)
	{
		Branch* nameAt = tree->getNameAt(i);
		Branch* treeAt = tree->getTreeAt(i);
		Branch* branch1 = tree->getBranch1Tree(i);
		Branch* branch2 = tree->getBranch2Tree(i);
		if (nameAt == this) return i;
		if (treeAt == this) return i;
		if (branch1 == this) return i;
		if (branch2 == this) return i;
	}
	assert(false);
}


Branch* Tree::getNameAt(int index)
{
	if (index < 0) return nullptr;
	if (index >= count) return nullptr;
	return nameAt[index];
}

Branch* Tree::getTreeAt(int index)
{
	if (index < 0) return nullptr;
	if (index >= count) return nullptr;
	return treeAt[index];
}

Branch* Tree::getBranch1Tree(int index)
{
	if (index < 0) return nullptr;
	if (index >= count) return nullptr;
	return branch1[index];
}

Branch* Tree::getBranch2Tree(int index)
{
	if (index < 0) return nullptr;
	if (index >= count) return nullptr;
	return branch2[index];
}

int Tree::getTrees()
{
	return trees;
}

int Tree::getCount()
{
	return count;
}

Tree::Tree()
{
	nameAt = new Branch * [count];
	treeAt = new Branch * [count];
	branch1 = new Branch * [count];
	branch2 = new Branch * [count];
	for (int i = 0; i < count; ++i)
	{
		nameAt[i] = new Branch();
		treeAt[i] = new Branch();
		branch1[i] = new Branch();
		branch2[i] = new Branch();
	}
}


Tree* search(Tree* tree, int value1, int value2, int count)
{
	cout << endl;
	for (int i = 0; i < count; ++i)
	{
		Branch* name_At = tree->getNameAt(i);
		Branch* tree_At = tree->getTreeAt(i);
		Branch* branch_1 = tree->getBranch1Tree(i);
		Branch* branch_2 = tree->getBranch2Tree(i);

		if (tree_At->getTree() == value1 && branch_1->getBranch1() == value2)
		{
			if (name_At->getName() != "none")
			{
				cout << "Tree: " << tree_At->getTree() << " "
					<< "Top branch: " << branch_1->getBranch1() << " ";
				if (branch_2->getBranch2() != 0)
				{
					cout << "Middle branch: " << branch_2->getBranch2() << " ";
				}
				else
				{
					cout << "                 ";
				}
				cout << "Elf: " << name_At->getName() << endl;
			}
		}
	}
	return nullptr;
}


int init(Tree* tree, int count)
{
	string name = "none";
	int branch1 = 0, branch2 = 0, rndBranch1 = 0, rndBranch2 = 0;

	for (int y = 0; y < tree->getTrees(); ++y)
	{
		cout << "_____" << y + 1 << " tree" << endl;
		srand(time(nullptr));
		rndBranch1 = rand() % 3 + 3;
		cout << "Top Branch count: " << rndBranch1 << endl;
		for (int i = 0; i < rndBranch1; ++i)
		{
			rndBranch2 = rand() % 2 + 2;
			cout << i + 1 << " top branch: " << rndBranch2 << " middle branch count" << endl;
			for (int j = 0; j <= rndBranch2; ++j)
			{
				branch1 = i + 1;
				branch2 = j;
				if (j == 0)
				{
					cout << "Imput " << i + 1 << " top branch house elf name: ";
				}
				else
				{
					cout << "Input " << j << " middle branch house elf name: ";
				}
				cin >> name;
				tree->getNameAt(count)->setName(name);
				tree->getTreeAt(count)->setTree(y + 1);
				tree->getBranch1Tree(count)->setBranch1(branch1);
				tree->getBranch2Tree(count)->setBranch2(branch2);
				count++;
			}
		}
	}
	return count;
}
