#include "common_header.hpp"
#include <iostream>
#include <vector>

using namespace std;

bool check_palindrome(myspace::SingleLL *&ptr_start, myspace::SingleLL *ptr_end,
                      int &counter) {
  bool palindrome_flag = true;

  counter++;
  if (ptr_end->next != NULL)
    palindrome_flag = check_palindrome(ptr_start, ptr_end->next, counter);
  // when last node in on the top of stack
  else {
    cout << "length of list: " << counter << '\n';
    counter /= 2;
  }

  // common for all nodes
  if ((palindrome_flag == false) || (counter == 0))
    return palindrome_flag;

  else {
    counter--;
    if (ptr_end->data == ptr_start->data) {
      ptr_start = ptr_start->next;
      return true;
    } else
      return false;
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  myspace::SingleLL *head;
  vector<int> array{1, 2, 3, 4, 3, 2, 1};
  head = myspace::generateSingleLL(&array);
  cout << "input linked list: \n";
  myspace::printSingleLL(head);

  myspace::SingleLL *ptr_start, *ptr_end;

  ptr_start = head;
  ptr_end = head;

  bool flag;
  int counter = 0;
  flag = check_palindrome(ptr_start, ptr_end, counter);

  if (flag == true)
    cout << "list is PALINDROME\n";
  else
    cout << "list is NOT PALINDROME\n";

  return 0;
}
