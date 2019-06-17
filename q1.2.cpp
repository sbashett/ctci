#include <iostream>
#include <string.h>
#include <vector>

void character_frequency(char *instring, unsigned int *counter, vector<int> *non_zero_indices){
	string_length = strlen(instring);
	for (int i=0; i< string_length; i++){
		index = int(instring[i]);
		if (*(counter+index) == 0) non_zero_indices->push_back(index);
		*(counter+index)++;

	}

}

int main(int argc, char **argv){
	vector<int> non_zero_indices;
	unsigned int counter[256] = {0};

	instring = argv[1];
	character_frequency(instring, counter, non_zero_indices);

	cout << non_zero_indices << '\n';

	return 0;
	
}
