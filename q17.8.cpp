#include <algorithm> // sort
#include <iostream>
#include <map>
#include <utility> // pair
#include <vector>

using namespace std;

bool sortFunction(pair<int, int> i, pair<int, int> j) {
  return (i.first < j.first);
}

void longest_subseq_helper(int currentIndex, vector<int> &array,
                           map<int, vector<int>> &longest_subseq_map) {

  if (currentIndex == 0) {
    longest_subseq_map.insert(
        make_pair(currentIndex, vector<int>{array[currentIndex]}));
    return;
  }

  int max_len_index = -1, max_len = 0, temp_len = 0;

  for (auto &pairs : longest_subseq_map) {

    if (pairs.second.back() < array[currentIndex])
      temp_len = pairs.second.size() + 1;
    else
      temp_len = pairs.second.size();

    if (temp_len > max_len) {
      max_len = temp_len;
      max_len_index = pairs.first;
    }
  }

  longest_subseq_map[currentIndex] = longest_subseq_map[max_len_index];

  if (longest_subseq_map[max_len_index].back() < array[currentIndex])
    longest_subseq_map[currentIndex].push_back(array[currentIndex]);

  return;
}

int get_longest_subsequence(vector<int> &array) {

  map<int, vector<int>> longest_subseq_map;

  for (int index = 0; index < (int)array.size(); index++) {
    longest_subseq_helper(index, array, longest_subseq_map);
  }

  // for(auto& pairs : longest_subseq_map){
  // 	cout << pairs.first << " : ";

  // 	for (auto& elem : pairs.second)
  // 		cout << elem << ", ";

  // 	cout << endl;
  // }

  return longest_subseq_map[array.size() - 1].size();
}

void add_input_data(vector<pair<int, int>> &inData) {

  inData.push_back(make_pair(65, 100));
  inData.push_back(make_pair(70, 150));
  inData.push_back(make_pair(56, 90));
  inData.push_back(make_pair(75, 190));
  inData.push_back(make_pair(60, 95));
  inData.push_back(make_pair(68, 110));

  return;
}

int main(void) {

  vector<pair<int, int>> inData;

  add_input_data(inData);
  // sort based on weights
  sort(inData.begin(), inData.end(), sortFunction);

  vector<int> heights;

  // fetching the heights of people sorted based on weights
  for (auto &pairs : inData) {
    heights.push_back(pairs.second);
  }

  // heights.push_back(10);
  // heights.push_back(22);
  // heights.push_back(9);
  // heights.push_back(33);
  // heights.push_back(21);
  // heights.push_back(50);
  // heights.push_back(41);
  // heights.push_back(60);
  // heights.push_back(80);

  int longest_tower = get_longest_subsequence(heights);

  cout << "longest tower length is : " << longest_tower << endl;

  return 0;
}