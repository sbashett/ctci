#include <bitset>
#include <iostream>
#include <map>

using namespace std;
static const int bitset_size = 8;

int get_max_bits(int n) {
  int counter = 0;
  while (n != 0) {
    counter++;
    n = n >> 1;
  }

  return counter;
}

int get_bit_mask(int bit_pos) {
  int bit_mask = 1;

  while (bit_pos > 0)
    bit_mask = bit_mask << 1;

  return bit_mask;
}

int find_missing_number(map<int, bitset<bitset_size>> &numbers_map) {

  int maxBitsCheck = get_max_bits(numbers_map.size());
  bitset<bitset_size> missing_num;
  map<int, bitset<bitset_size>> part1, part2; // part1 for zero, part2 for 1
  int zeros_count = 0;
  int ones_count = 0;
  int bit_pos = 0;
  bool remove_keys = 0;

  while (bit_pos < maxBitsCheck) {
    zeros_count = 0;
    ones_count = 0;

    for (auto &map_pair : numbers_map) {
      if (map_pair.second[bit_pos] == 0) {
        zeros_count++;
        part1[map_pair.first] = map_pair.second;
      } else {
        ones_count++;
        part2[map_pair.first] = map_pair.second;
      }
    }

    cout << "size of map: " << numbers_map.size() << endl;
    cout << "checking bit pos: " << bit_pos << " zeros_count: " << zeros_count
         << " ones_count: " << ones_count << endl;

    if ((numbers_map.size() + 1) % 2 ==
        0) { // total numbers count is even num_zeros = num_ones ideally
      cout << "entered condition 1" << endl;
      if (zeros_count < ones_count)
        remove_keys = 0;
      else if (zeros_count > ones_count)
        remove_keys = 1;
      else {
        cout << "no missing key" << endl;
        exit(0);
      }
    }

    else { // total numbers count is odd num_zeros = num_ones+1 ideally
      cout << "entered condition 2" << endl;
      if (zeros_count == ones_count) // missing zero
        remove_keys = 0;
      else // missing 2
        remove_keys = 1;
    }

    if (remove_keys) { // missing 1
      numbers_map.clear();
      numbers_map = part2;
    }

    else { // missing 0
      numbers_map.clear();
      numbers_map = part1;
    }

    cout << "missing bit: " << remove_keys << endl << endl;
    missing_num[bit_pos] = remove_keys;
    bit_pos++;
    part1.clear();
    part2.clear();
  }

  return (int)(missing_num.to_ulong());
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  // assuming the
  int n = 50;

  map<int, bitset<bitset_size>>
      numbers; // change the constant val of bitset size based on usage

  for (int i = 0; i <= n; i++) {
    numbers[i] = i;
  }

  numbers.erase(
      49); // change this number to erase a number from list and test the code
  int missing_num = find_missing_number(numbers);

  cout << "missing_num is: " << missing_num << endl;

  // printing the elements of map
  // for(auto& map_pair : numbers){
  // 	cout << map_pair.first << " : " << map_pair.second << endl;
  // }

  return 0;
}
