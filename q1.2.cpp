#include <iostream>
#include <string.h>
#include <vector>
#include <assert.h>

using namespace std;
void character_frequency(char *input_string, unsigned int *counter, vector<int> *non_zero_indices){
	int string_length = strlen(input_string);
	char c;
	int index;
	for (int i=0; i< string_length; i++){
		c = input_string[i];
		index = (int)c;
		if (*(counter+index) == 0) non_zero_indices->push_back(index);
		(*(counter+index))++;

	}

}

int main(int argc, char **argv){
	assert(argc > 1);
	vector<int> non_zero_indices1, non_zero_indices2;
	unsigned int counter1[127] = {0}, counter2[127] = {0};
	char *input_string1 = argv[1];
	char *input_string2 = argv[2];
	character_frequency(input_string1, counter1, &non_zero_indices1);
	character_frequency(input_string2, counter2, &non_zero_indices2);

	cout << "printing characters and their frequencies\n";
	if (non_zero_indices1.size() != non_zero_indices2.size()) goto NEGATIVE

	else{
		for (auto it=non_zero_indices1.begin(); it!=non_zero_indices1.end();it++){
			if (counter1[*it] != counter2[*it]) goto NEGATIVE
		}
		goto POSITIVE

	}

	NEGATIVE: cout << "both the strings are not permutations of each other\n"
	
	for (auto it = non_zero_indices1.begin(); it != non_zero_indices1.end(); it++)
		cout << char(*it) << ": " << counter1[*it] << '\n';

	return 0;
	
}
