#include <iostream>
#include <vector>

using namespace std;

void print_array(vector<int> &arr) {

  for (auto &elem : arr) {
    cout << elem << ", ";
  }
  cout << endl;

  return;
}

void generate_permutations(vector<int> input_array, int size, int &count) {
  // heaps algorithm: generates (n-1)! permutations of first n-1 elements by
  // ending with the current last element if n is odd swap first and last
  // element and if n even swap ith and last element
  if (size == 1) {
    print_array(input_array);
    count++;
    return;
  }

  for (int i = 0; i < size; i++) {

    generate_permutations(input_array, size - 1, count);

    if (size % 2 == 1)
      swap(input_array[0], input_array[size - 1]);
    else
      swap(input_array[i], input_array[size - 1]);
  }
  return;
}

int main(void) {

  // vector<int> input_array{1,2,3,4,5,6,7,8};
  vector<int> input_array{1, 2, 3};
  int count = 0;

  generate_permutations(input_array, static_cast<int>(input_array.size()),
                        count);

  cout << "number of permutations generated: " << count << endl;

  return 0;
}