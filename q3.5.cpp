#include "common_header.hpp"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  stack<int> st1, temp_stack;
  int temp, counter;
  vector<int> array{5, 1, 3, 8, 9, 10, 6};

  myspace::fill_stack(&st1, &array);

  while (st1.empty() == false) {
    if ((temp_stack.empty() == true) || (st1.top() >= temp_stack.top())) {
      temp_stack.push(st1.top());
      st1.pop();
    }

    else {
      temp = st1.top();
      st1.pop();
      counter = 0;

      while (true) {
        if (temp_stack.empty() == true)
          break;
        if (temp <= temp_stack.top()) {
          st1.push(temp_stack.top());
          temp_stack.pop();
          counter++;
        }

        else
          break;
      }

      temp_stack.push(temp);
      while (counter > 0) {
        temp_stack.push(st1.top());
        st1.pop();
        counter--;
      }
    }

    // cout << "size of original stack :" << st1.size() << '\n';
    // cout << "size of temp stack: " << temp_stack.size() << '\n';
  }

  while (temp_stack.empty() == false) {
    st1.push(temp_stack.top());
    cout << ' ' << temp_stack.top();
    temp_stack.pop();
  }
  cout << '\n';

  return 0;
}
