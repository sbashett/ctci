#include <iostream>
#include "common_header.hpp"
#include <vector>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	myspace::SingleLL *head;
	vector<int> array{1,2,3,4,3,2,1};
	head = myspace::generateSingleLL(&array);
	cout << "input linked list: \n";
	myspace::printSingleLL(head);
	
	
	return 0;
}

