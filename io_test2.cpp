#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
using namespace std;

template <class T1, class T2> bool isExists(T1 &container, T2 check_val) {

  if (container.find(check_val) == container.end())
    return false;
  else
    return true;
}

class Compare {
public:
  bool operator()(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
  }
};

void find_k_freq(vector<int> &array, int k) {

  unordered_map<int, int> freq_vals;
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

  for (auto elem : array) {
    freq_vals[elem]++;
  }

  // can use bucket sort for linear time
  // number of buckets can be atmost size of input array
  // each bucket represents frequency values
  for (auto pairs : freq_vals)
    pq.push(pairs);
  for (int it = 0; it < k; it++) {
    cout << pq.top().first << endl;
    pq.pop();
  }

  return;
}

int main(void) {

  vector<int> array{1, 1, 1, 2, 2, 3, 4, 5, 6, 6, 6, 6};
  find_k_freq(array, 4);
  return 0;
}