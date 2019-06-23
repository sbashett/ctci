#include <iostream>
#include <string>
#include <vector>

using namespace std;

void calculate_frequencies(string *in_string, vector<int> *avail_indices, int *hash_table){
	int index;
	char c;
	for(string::iterator it=in_string->begin(); it!=in_string->end(); it++){
		c = *it;
		c = toupper(c);
		index = (int)c;
		if((index >= 65) && (index < 91)){
			if ( (*(hash_table+index)) == 0 ) avail_indices->push_back(index);
			(*(hash_table+index))++;
		}
	}

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	string input_string;
	int hash_table[256] = {0};
	bool odd_frequency_flag=false;
	vector<int> available_indices;
	int index;

	cout << "enter input string: ";
	getline(cin, input_string);
	
	calculate_frequencies(&input_string, &available_indices, hash_table);
	
	for(vector<int>::iterator it=available_indices.begin(); it!=available_indices.end(); it++){
		index= *it;
		//cout << (char)index << " :" << hash_table[index] << "\n";
		if (hash_table[index]%2 != 0) {
			if (odd_frequency_flag == true) {
				cout << "False\n";
				return 0;
			}
			else odd_frequency_flag = true;
		}
	}

	cout << "True\n";

	return 0;
} 
