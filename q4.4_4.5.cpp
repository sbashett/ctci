#include "common_header.hpp"
#include <assert.h>
#include <bits/stdc++.h> // for INT_MIN and INT_MAX
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int>::iterator ITER;

void buildMinBST(myspace::BinTreeNode *&head, vector<int> &sort_elem,
                 ITER first, ITER last) {
  // minimal binary tree; requires sorted array of elements

  if (last < first)
    return;

  ITER middle = first + distance(first, last) / 2;

  head = new myspace::BinTreeNode((*middle));
  // cout << *middle << ", ";

  buildMinBST(head->left, sort_elem, first, middle - 1);
  buildMinBST(head->right, sort_elem, middle + 1, last);
}

int getHeight(myspace::BinTreeNode *node) {
  int left_height = 0, right_height = 0;

  if ((node->left) != NULL)
    left_height = getHeight(node->left);
  if ((node->right) != NULL)
    right_height = getHeight(node->right);

  // cout << "node " << node->data << " heights:" << left_height << right_height
  // << '\n';

  if ((left_height == -1) || (right_height == -1) ||
      (abs(left_height - right_height) > 1))
    return -1;
  else
    return max(left_height, right_height) + 1;
}

bool isTreeBalanced(myspace::BinTreeNode *head) {
  // assuming head is not null
  // if(head==NULL) return 0;

  int height = 0;

  if ((head->left != NULL) || (head->right != NULL))
    height = getHeight(head);
  else
    return true;

  if (height == -1)
    return false;
  else
    return true;
}

bool isTreeBST(myspace::BinTreeNode *node, int min_val, int max_val) {
  bool isBST = true;

  // if((node->left!=NULL) && (node->left->data > node->data)) return false;
  // if((node->right!=NULL) && (node->right->data <= node->data)) return false;

  if ((node->data <= min_val) || (node->data > max_val))
    return false;

  bool lstree = true, rstree = true;
  lstree =
      (node->left == NULL) ? true : isTreeBST(node->left, min_val, node->data);
  rstree = (node->right == NULL) ? true
                                 : isTreeBST(node->right, node->data, max_val);
  isBST = lstree & rstree;

  return isBST;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  // vector<vector<int>> edges{
  // {1,2},{1,6},{2,3},{2,5},{4,2},{4,5},{5,3},{6,4}};
  vector<int> elements{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  myspace::BinTreeNode *head;

  ITER first = elements.begin();
  ITER last = elements.end() - 1;

  buildMinBST(head, elements, first, last);

  // head=new myspace::BinTreeNode(1);
  // head->left = new myspace::BinTreeNode(2);
  // head->right = new myspace::BinTreeNode(5);
  // head->right->right = new myspace::BinTreeNode(4);
  // head->right->right->right = new myspace::BinTreeNode(3);

  assert(head != NULL);

  myspace::print_binary_tree(head, myspace::INORDER);
  cout << "\n";

  bool isBalanced = false;
  isBalanced = isTreeBalanced(head);

  if (isBalanced)
    cout << "the binary tree is BALANCED\n";
  else
    cout << "the binary tree is NOT BALANCED\n";

  bool isBST = isTreeBST(head, INT_MIN, INT_MAX);

  if (isBST)
    cout << "the binary tree is a BINARY SEARCH TREE\n";
  else
    cout << "the binary tree is NOT a BINARY SEARCH TREE\n";

  return 0;
}