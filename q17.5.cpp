#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isKeyExists(int key, map<int, int> &hashmap) {

  if (hashmap.find(key) == hashmap.end())
    return false;
  else
    return true;
}

void get_max_subarray_equal(string data) {

  map<int, int> diff_map;
  int letterCount = 0, numberCount = 0, max_len = 0, lindex = 0;
  int diff;
  char character;

  cout << data << endl;

  for (int it = 0; it < (int)data.length(); it++) {
    character = data[it];

    // cout << character << " " << (int)character;

    if ((int)character >= 49 && (int)character <= 57) // it is a number
      numberCount++;
    else
      letterCount++;

    diff = numberCount - letterCount;
    // cout << " " << diff << endl;
    if (isKeyExists(diff, diff_map)) {
      if ((it - diff_map[diff]) > max_len) {
        max_len = it - diff_map[diff];
        lindex = diff_map[diff];
      }
    }

    else {
      diff_map[diff] = it;
    }
  }

  cout << "max subarray with equal number of letters and numbers is: "
       << max_len << endl;
  cout << "the subarray string lindex: " << lindex + 1 << endl;
  cout << "the subarray string is: " << data.substr(lindex + 1, max_len)
       << endl;

  return;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  string in1 = "ab1c4e23d89gf";
  string in2 = "a12c34b789d";
  string in3 = "a123456b";
  string in4 = "a1234c56b";

  get_max_subarray_equal(in1);
  cout << endl;
  get_max_subarray_equal(in2);
  cout << endl;
  get_max_subarray_equal(in3);
  cout << endl;
  get_max_subarray_equal(in4);

  return 0;
}