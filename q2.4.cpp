#include "common_header.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  vector<int> data{3, 5, 8, 5, 10, 2, 1};
  int partition = 8, swap = 0;

  myspace::SingleLL *head = myspace::generateSingleLL(&data);
  cout << "original linked list: \n";
  myspace::printSingleLL(head);

  myspace::SingleLL *ptr1, *ptr2;

  ptr1 = head;
  ptr2 = head->next;

  while (ptr1->data < partition) {
    ptr1 = ptr2;
    ptr2 = ptr2->next;
  }

  while (ptr2 != NULL) {
    if (ptr2->data < partition) {
      swap = ptr1->data;
      ptr1->data = ptr2->data;
      ptr2->data = swap;
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    } else
      ptr2 = ptr2->next;
  }

  cout << "modified linked list: \n";
  myspace::printSingleLL(head);

  return 0;
}
