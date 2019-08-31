#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_num_spaces(string *in_string, int *string_len) {
  int spaces = 0;
  for (int it = 0; it < (*string_len); it++) {
    if (in_string->at(it) == ' ')
      spaces++;
  }

  return spaces;
}

void replace_spaces(string *in_string, int index, int *string_len) {

  for (int it = (*string_len) - 1; it >= 0; it--) {
    if (in_string->at(it) == ' ') {
      in_string->operator[](index) = '0';
      in_string->operator[](index - 1) = '2';
      in_string->operator[](index - 2) = '%';
      index -= 3;
    } else {
      in_string->operator[](index) = in_string->at(it);
      index--;
    }
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  string input_string;
  int string_len, num_spaces;
  cout << "Enter the input string: ";
  getline(cin, input_string);
  // cout << "entered string: " << input_string <<'\n';
  cout << "enter the actual length of string: ";
  cin >> string_len;

  num_spaces = get_num_spaces(&input_string, &string_len);

  int index;
  index = string_len + num_spaces * 2 - 1;

  replace_spaces(&input_string, index, &string_len);

  cout << "replaced string: " << input_string << '\n';
  return 0;
}
