#include <assert.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char **argv) {
  assert(argc > 1);
  char *input_string = argv[1];
  //	int string_length = sizeof(input_string);
  int string_length = strlen(input_string);
  bool check[127] = {0};
  char c;
  bool repeating_flag = 0;
  int index;
  printf("string_length: %d\n", string_length);

  for (int i = 0; i < string_length; i++) {
    c = input_string[i];
    index = (int)c;
    cout << c << ' ' << index << '\n';
    if (index == 32)
      continue;
    if (check[index] == 0)
      check[index] = 1;
    else {
      repeating_flag = 1;
      break;
    }
  }

  if (repeating_flag)
    cout << "\nrepeating character is" << char(index) << '\n';
  else
    cout << "\nno repeating character\n";
}
