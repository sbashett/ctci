#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

typedef map<int, vector<int> *> MAPTYPE;

class HeapNodeData {
public:
  int elem_value;
  int index;
  HeapNodeData(int, int);
};

HeapNodeData::HeapNodeData(int elem_value, int index)
    : elem_value(elem_value), index(index) {}

template <class T1, class T2> bool isKeyExists(T1 key, T2 &preprocess_map) {

  if (preprocess_map.find(key) == preprocess_map.end())
    return false;
  else
    return true;
}

void fill_elem_occurences(vector<int> &biggerArr, vector<int> &smallArr,
                          MAPTYPE &preprocess_map) {

  for (auto &elem : smallArr) {
    preprocess_map.insert(make_pair(elem, new vector<int>()));
  }

  for (int index = 0; index < static_cast<int>(biggerArr.size()); index++) {
    if (isKeyExists(biggerArr[index], preprocess_map))
      preprocess_map[biggerArr[index]]->push_back(index);
  }

  return;
}

class Comparator {

public:
  bool operator()(const HeapNodeData *n1, const HeapNodeData *n2) {
    return n1->index > n2->index;
  }
};

void find_shortest_subseq(MAPTYPE &preprocess_map, int min_diff) {

  priority_queue<HeapNodeData *, vector<HeapNodeData *>, Comparator> heap;
  int max_index = -1, min_index = 0;

  for (auto &pairs : preprocess_map) {
    heap.push(new HeapNodeData(pairs.first, pairs.second->at(0)));
    if (pairs.second->at(0) > max_index)
      max_index = pairs.second->at(0);
  }

  int ret_val[] = {0, 0};
  HeapNodeData *temp;
  int temp_store_index;

  while (true) {
    min_index = heap.top()->index;
    if ((max_index - min_index) < min_diff) {
      ret_val[0] = min_index;
      ret_val[1] = max_index;
      min_diff = max_index - min_index;
    }

    temp = heap.top();
    heap.pop();
    preprocess_map[temp->elem_value]->erase(
        preprocess_map[temp->elem_value]->begin());

    if (preprocess_map[temp->elem_value]->empty()) {
      delete temp;
      while (!heap.empty()) {
        temp = heap.top();
        heap.pop();
        delete temp;
      }
      break;
    }

    temp_store_index = preprocess_map[temp->elem_value]->at(0);
    heap.push(new HeapNodeData(temp->elem_value, temp_store_index));
    max_index = max(max_index, temp_store_index);
    delete temp;
  }

  cout << "index_posns: " << ret_val[0] << ", " << ret_val[1] << endl;
  return;
}

int main(void) {

  vector<int> biggerArr{7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7};
  vector<int> smallArr{7, 5, 1};

  MAPTYPE preprocess_map;
  fill_elem_occurences(biggerArr, smallArr, preprocess_map);
  find_shortest_subseq(preprocess_map, biggerArr.size());
  return 0;
}