#include <algorithm> // transform
#include <cassert>
#include <cctype>
#include <cstdlib> // abs
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

typedef map<string, vector<int>> TABLEMAP;
#define MAXVAL numeric_limits<int>::max();

bool isExists(string key, TABLEMAP &lut) {

  if (lut.find(key) == lut.end())
    return false;
  else
    return true;
}

void fill_table(string word, int pos, TABLEMAP &lut) {
  transform(word.begin(), word.end(), word.begin(),
            ::tolower); // converting everything to lower case

  if (isExists(word, lut))
    lut[word].push_back(pos);
  else
    lut.insert(make_pair(word, vector<int>{pos}));
}

void read_file(string fname, TABLEMAP &lut) {

  fstream myfile;
  string word;
  myfile.open(fname, ios::in);
  int pos = 0;

  if (!myfile.is_open())
    return;

  while (myfile >> word) {
    fill_table(word, pos, lut);
    pos++;
  }

  myfile.close();

  return;
}

void display_file_data(string fname) {

  fstream myfile;
  string line;
  myfile.open(fname, ios::in);

  if (!myfile.is_open())
    return;

  while (getline(myfile, line))
    cout << line << endl;

  myfile.close();

  return;
}

void display_map(TABLEMAP &lut) {

  for (auto &pairs : lut) {
    cout << pairs.first << ": ";

    for (auto &elem : pairs.second) {
      cout << elem << ", ";
    }

    cout << endl;
  }

  return;
}

string trim_and_transform(string word) {

  const char *whitespaces = " \t\v\r\n";

  size_t start = word.find_first_not_of(whitespaces);
  size_t end = word.find_last_not_of(whitespaces);

  word = ((start == end) && ((int)word[start] == 32))
             ? ""
             : word.substr(start, end - start + 1);

  transform(word.begin(), word.end(), word.begin(), ::tolower);
  return word;
}

int smallest_difference(vector<int> &vec1, vector<int> &vec2) {

  vector<int>::iterator iter1, iter2;

  iter1 = vec1.begin();
  iter2 = vec2.begin();

  int shortest_dist = MAXVAL;
  int curr_val;
  while ((iter1 != vec1.end()) || (iter2 != vec2.end())) {

    curr_val = abs(*iter1 - *iter2);
    if (curr_val < shortest_dist)
      shortest_dist = curr_val;

    if (!(iter2 + 1 == vec2.end()) && (abs(*iter1 - *(iter2 + 1)) < curr_val))
      iter2++;

    else {
      if (!(iter1 + 1 == vec1.end()))
        iter1++;
      else
        break;
    }
  }

  return shortest_dist;
}

void find_shortest_distance(string word1, string word2, TABLEMAP &lut) {

  word1 = trim_and_transform(word1);
  word2 = trim_and_transform(word2);

  assert((word1.empty(), word2.empty(), "one of the word is empty!!"));

  if (!isExists(word1, lut)) {
    cout << "word " << word1 << " doesnot exist in the file" << endl;
    return;
  }

  if (!isExists(word2, lut)) {
    cout << "word " << word2 << " doesnot exist in the file" << endl;
    return;
  }

  int shortest_dist = smallest_difference(lut[word1], lut[word2]);

  cout << "shortest distance between " << word1 << " and " << word2 << " is "
       << shortest_dist << endl;

  return;
}

int main(void) {
  TABLEMAP lut;
  string fname = "q17.11.txt";

  read_file(fname, lut); // read and prepare look up table

  display_file_data(fname);
  cout << endl << endl;

  // display_map(lut);
  // cout << endl;

  string word1, word2;

  while (true) {
    cout << "enter word1: ";
    cin >> word1;
    cout << "enter word2: ";
    cin >> word2;

    find_shortest_distance(word1, word2, lut);
    cout << endl;
  }

  return 0;
}
