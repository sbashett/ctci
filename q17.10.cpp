#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int find_majority_elem(vector<int> &inData) {

  int match_mismatch = 0, majority_elem = -1;
  // int majority_elem, majority_elem_freq;

  cout << "input data is: " << endl;
  for (auto &elem : inData)
    cout << elem << ", ";
  cout << endl;

  majority_elem = inData[0];

  for (vector<int>::iterator iter = inData.begin(); iter != inData.end();
       iter++) {

    if (majority_elem == *iter)
      match_mismatch++;
    else
      match_mismatch--;

    if (match_mismatch == 0) {
      if (!((iter + 1) == inData.end()))
        majority_elem = *(iter + 1);
    }
  }

  if (match_mismatch == 0)
    return -1;

  int maj_freq = 0;

  for (auto &elem : inData)
    if (elem == majority_elem)
      maj_freq++;

  if (maj_freq > (int)(inData.size() / 2))
    return majority_elem;
  else
    return -1;
}

int main(void) {

  vector<int> inData{1, 2, 5, 9, 5, 5, 5};

  int majority_elem = find_majority_elem(inData);

  cout << "majority element is: " << majority_elem << endl;
  return 0;
}