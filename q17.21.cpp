#include <iostream>
#include <pair>
#include <queue>
#include <utility> // make_pair
#include <vector>

using namespace std;

/* SMALL CHANGE: MUSTE INCLUDE PREPROCESSING STEP TO REDUCE TIME COMPLEXITY */

typedef vector<int>::iterator ITER;

ITER find_iter_next_max(ITER first, ITER last) {

  ITER iter_next_max = first + 1;

  while (true) {
    first++;
    if (*first > *iter_next_max)
      iter_next_max = first;
    if (first == last)
      break;
  }

  return iter_next_max;
}

void update_vol_helper(ITER first, ITER last, int &volume) {

  volume += min(*first, *last) * (last - first - 1);
  // subtracts volume of intermediate lower hist peaks
  first++;
  while (first != last) {
    volume -= *first;
    first++;
  }
  return;
}

void update_volume(ITER iter_first, ITER iter_last, ITER iter_next_max,
                   int &volume) {

  if ((*iter_last >= *iter_first) || (iter_next_max == iter_last)) {
    update_vol_helper(iter_first, iter_last, volume);
  }

  else {

    while (true) {
      update_vol_helper(iter_first, iter_next_max, volume);
      if (iter_next_max == iter_last)
        break;
      iter_first = iter_next_max;
      iter_next_max = find_iter_next_max(iter_next_max, iter_last);
    }
  }
  return;
}

int find_hist_vol(vector<int> &input) {
  ITER iter_first, iter_next_max, iter_last;

  iter_first = input.begin();
  iter_next_max = input.begin() + 1;
  iter_last = input.begin() + 1;

  int volume = 0;

  while (true) {

    if (iter_last == input.end()) {
      update_volume(iter_first, iter_last--, iter_next_max, volume);
      break;
    }

    if (*iter_last == 0) {
      iter_last++;
      continue;
    }

    if (*iter_last >= *iter_first) {
      update_volume(iter_first, iter_last, iter_next_max, volume, input);
      iter_first = iter_last;
      iter_last++;
      iter_next_max = iter_last;
      continue;
    }

    if (*iter_last > *iter_next_max)
      iter_next_max = iter_last;

    iter_last++;
  }

  return volume;
}

int main(void) {

  vector<int> input{0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 5, 0, 1, 0, 0};
  // vector<int> input{1, 0, 1};
  int vol = find_hist_vol(input);
  cout << "volume is: " << vol << endl;

  return 0;
}