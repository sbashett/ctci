#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int main(void) {

  int k;
  cout << "enter the value of k: ";
  cin >> k;

  queue<int> queue3;
  queue<int> queue5;
  queue<int> queue7;

  vector<int> multiples{1};

  queue3.push(3);
  queue5.push(5);
  queue7.push(7);

  queue<int> *min_queue;

  while ((int)multiples.size() <= k) {

    if (queue3.front() < queue5.front())
      min_queue = &queue3;
    else
      min_queue = &queue5;

    if (min_queue->front() > queue7.front())
      min_queue = &queue7;

    multiples.push_back(min_queue->front());

    if (min_queue->front() == queue3.front())
      queue3.push(3 * min_queue->front());

    if (min_queue->front() != queue7.front())
      queue5.push(5 * min_queue->front());

    queue7.push(7 * min_queue->front());
    min_queue->pop();
  }

  for (auto &elem : multiples) {
    cout << elem << ", ";
  }
  cout << endl;

  cout << "kth number with only 3, 5 and/or 7 as prime factors is: "
       << multiples.back() << endl;

  return 0;
}