#include <iostream>
#include <map>
#include <string>

using namespace std;
typedef unsigned long MYINT;

map<int, string> singleDigits{
    {0, "zero"}, {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"},
    {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};

map<int, string> twoDigitsSpecial{
    {11, "eleven"},    {12, "twelve"},   {13, "thirteen"},
    {14, "fourteen"},  {15, "fifteen"},  {16, "sixteen"},
    {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}};

map<int, string> multiplesTen{{1, "ten"},     {2, "twenty"}, {3, "thirty"},
                              {4, "forty"},   {5, "fifty"},  {6, "sixty"},
                              {7, "seventy"}, {8, "eighty"}, {9, "ninety"}};

map<int, string> prependMap{
    {1, ""}, {2, "thousand"}, {3, "million"}, {4, "billion"}, {5, "trillion"}};

string genStr2Dig(int number) {
  if (number == 0)
    return ""; // 00

  if (number / 10 == 0) { // 0x
    return singleDigits[number];
  }
  // xy
  // y=0
  if (number % 10 == 0)
    return multiplesTen[number / 10];

  else if (number / 10 == 1) { // 1y
    return twoDigitsSpecial[number];
  }

  else { // xy
    return multiplesTen[number / 10] + ' ' + singleDigits[number % 10];
  }

  return "";
}

string genStr3Dig(int number, string appendString) {
  if (number == 0) // 000
    return "";

  if (number / 100 == 0) { // 0xy
    return genStr2Dig(number) + ' ' + appendString;
  }

  else { // xyz
    return singleDigits[number / 100] + " hundred " + genStr2Dig(number % 100) +
           ' ' + appendString;
  }
}

string genString(MYINT number) {
  string print_str = "";

  if (number / 10 == 0) {
    return singleDigits[number];
  }

  int prependCounter = 1;
  // int rem;
  int divider = 1000;

  while (number != 0) {
    print_str = genStr3Dig(number % divider, prependMap[prependCounter]) +
                ", " + print_str;
    prependCounter++;
    number = number / divider;
  }

  return print_str;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  MYINT number;
  string print_str;
  while (true) {
    cout << "enter positive number or a zero to quit: ";
    cin >> number;
    if (number == 0)
      break;
    print_str = genString(number);
    cout << print_str << '\n';
  }

  return 0;
}
