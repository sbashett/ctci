#include <iostream>

using namespace std;


void print_number_twos(int n){
	int current_multiple = 10, totalCount = 0;
	int q, rem;

	while(current_multiple < n*10){
		q = n / current_multiple;
		rem = n % current_multiple;

		totalCount += q * (current_multiple/10);

		if(rem >= 3*(current_multiple/10))
			totalCount += (current_multiple/10);
		else if( (2*current_multiple/10) <= rem)
			totalCount += (rem - (2*current_multiple/10) + 1);

		current_multiple *= 10;
	}

	cout << "total number of 2's in numbers from 0 to " << n << " : " << totalCount << endl;

	return;
}

int main(void){
	int n;

	while(true){
		cout << "enter value of n to count number of 2's from 0 to n or enter 0 to exit: ";
		cin >> n;
		if(n == 0)
			break;
		print_number_twos(n);
	}

	return 0;
}