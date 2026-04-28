#pragma once

#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class Branch
{
	string name = "none";
	int branch1 = 0, branch2 = 0, treeCount = 0;
	class Tree* tree = nullptr;

public:

	void setName(string value);

	string getName();

	void setTree(int value);

	int getTree();

	void setBranch1(int value);

	int getBranch1();

	void setBranch2(int value);

	int getBranch2();

	int getNumber();
};


class Tree
{
	int count = 100, trees = 5;
	Branch** nameAt = nullptr;
	Branch** treeAt = nullptr;
	Branch** branch1 = nullptr;
	Branch** branch2 = nullptr;

public:

	Branch* getNameAt(int index);

	Branch* getTreeAt(int index);

	Branch* getBranch1Tree(int index);

	Branch* getBranch2Tree(int index);

	int getTrees();

	int getCount();

	Tree();
};


Tree* search(Tree* tree, int value1, int value2, int count);

int init(Tree* tree, int count);