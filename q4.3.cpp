#include "common_header.hpp"
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

void generate_ll_depths(myspace::BinTreeNode *head,
                        map<int, myspace::SingleLL *> &linkedLists) {
  queue<myspace::BinTreeNode *> process_queue;
  process_queue.push(head);
  head->level = 0;
  myspace::BinTreeNode *currentNode;

  while (!(process_queue.empty())) {
    currentNode = process_queue.front();

    if (linkedLists.find(currentNode->level) == linkedLists.end()) {
      linkedLists[currentNode->level] =
          new myspace::SingleLL(currentNode->data);
    } else
      linkedLists[currentNode->level]->appendToTail(currentNode->data);

    if (currentNode->left != NULL) {
      currentNode->left->level = currentNode->level + 1;
      process_queue.push(currentNode->left);
    }

    if (currentNode->right != NULL) {
      currentNode->right->level = currentNode->level + 1;
      process_queue.push(currentNode->right);
    }

    process_queue.pop();
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  vector<int> elements{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  myspace::BinTreeNode *head;

  ITER first = elements.begin();
  ITER last = elements.end() - 1;

  buildMinBST(head, elements, first, last);
  // myspace::print_binary_tree(head, myspace::INORDER);
  // cout << "\n";

  map<int, myspace::SingleLL *> linkedLists;
  generate_ll_depths(head, linkedLists);

  for (auto ll : linkedLists) {
    cout << "level " << ll.first << ":\n";
    myspace::printSingleLL(ll.second);
  }

  return 0;
}