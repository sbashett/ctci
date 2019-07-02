#include <iostream>
#include <vector>
#include "common_header.hpp"

using namespace std;

typedef vector<int>::iterator ITER;

void buildMinBST(myspace::BinTreeNode*& head, vector<int>& sort_elem, ITER first, ITER last){
	// minimal binary tree; requires sorted array of elements

	if(last < first) return;

	ITER middle = first + distance(first, last)/2;

	head = new myspace::BinTreeNode((*middle));
	// cout << *middle << ", ";

	buildMinBST(head->left, sort_elem, first, middle-1);
	buildMinBST(head->right, sort_elem, middle+1, last);
}
	
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	// vector<vector<int>> edges{ {1,2},{1,6},{2,3},{2,5},{4,2},{4,5},{5,3},{6,4}};
	vector<int> elements{1,2,3,4,5,6,7,8,9,10};
	myspace::BinTreeNode* head;

	ITER first = elements.begin();
	ITER last = elements.end()-1;

	buildMinBST(head, elements, first, last);

	myspace::print_binary_tree(head, myspace::INORDER);
	cout << "\n";

	return 0;
}