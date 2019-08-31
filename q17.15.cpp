#include <algorithm> //sort
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef vector<string>::iterator ITER;

bool sort_func(string w1, string w2) { return w1.size() > w2.size(); }
bool doesCombExist(string, vector<string> &, map<string, bool> &);
bool doesCombExist_helper(string, string, vector<string> &,
                          map<string, bool> &);

bool checkWord(string word, vector<string> &list_words,
               map<string, bool> &mem_map) {
  if (mem_map.find(word) == mem_map.end()) {
    if (find(list_words.begin(), list_words.end(), word) == list_words.end())
      mem_map[word] = false;
    else
      mem_map[word] = true;
  }
  return mem_map[word];
}

bool doesCombExist_helper(string lword, string rword,
                          vector<string> &list_words,
                          map<string, bool> &mem_map) {
  bool lwordExists, rwordExists;
  lwordExists = checkWord(lword, list_words, mem_map);
  rwordExists = checkWord(rword, list_words, mem_map);
  if (!rwordExists) // not needed to lwordExists
    rwordExists = doesCombExist(rword, list_words, mem_map);
  return (lwordExists && rwordExists);
}

bool doesCombExist(string word, vector<string> &list_words,
                   map<string, bool> &mem_map) {
  bool combExist;
  for (int i = 1; i < static_cast<int>(word.size()); i++) {
    combExist = doesCombExist_helper(word.substr(0, i), word.substr(i),
                                     list_words, mem_map);
    // cout << word.substr(0, i+1) << ", " << word.substr(i+1, word.size()-1) <<
    // ": " << combExist << endl;
    if (combExist)
      return true;
  }
  return false;
}

void find_longest(vector<string> &list_words) {
  bool longest_check;
  map<string, bool> mem_map;
  for (auto word : list_words)
    mem_map[word] = true;
  for (ITER it = list_words.begin(); it != list_words.end(); it++) {
    longest_check = doesCombExist(*it, list_words, mem_map);
    if (longest_check) {
      cout << "longest word made of other words is : " << *it << endl;
      return;
    }
  }
  cout << "no word exists which is a combination of others" << endl;
  return;
}

int main(void) {
  vector<string> list_words{"cat",  "banana", "dog",      "nana",
                            "walk", "walker", "dogwalker"};
  sort(list_words.begin(), list_words.end(),
       sort_func); // sort in decreasing order of length of strings
  for (auto &word : list_words)
    cout << word << endl;
  find_longest(list_words);
  return 0;
}