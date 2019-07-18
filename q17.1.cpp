#include <iostream>

using namespace std;

int shiftbits(int num, int count, bool dir){
	if(dir){
		for(int it = 0; it < count; it++){
			num = num >> 1;
		}
	}

	else{
		for(int it = 0; it < count; it++){
			num = num << 1; 
		}
	}

	return num;
}

int sum_helper(int a, int b, bool carry){
	int sum=0;
	int count = 0;
	int f=0;
	bool b1, b2;
	while((a!=0) && (b!=0)){
		b1 = (a & 0x01);
		b2 = (b & 0x01);
		f = b1 ^ b2 ^ carry;
		sum |= shiftbits(f, count, 0);
		carry = (b1 & b2) | ((b1 | b2) & carry);
		a = shiftbits(a, 1, 1);
		b = shiftbits(b, 1, 1);
		count++;
	}

	return sum;
}

int sum(int a, int b){
	// int sum = 0;
	// int sign_a = a < 0 ? -1 : 1; 
	// int sign_b = b < 0 ? -1 : 1;

	return sum_helper(a, b, 0);
}

// int add ( int a, int b) {
//  while (b != 0) {
//  int sum = a ^ b;
//  int carry = (a & b) << 1;
//  a = sum;
//  b = carry;
//  cout << a << ", " << b << endl;
//  }
//  return a;
// }

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){

	int a = 29, b = 14;

	int ans = sum(a,b);
	cout << " sum of " << a << " and " << b << " : " << ans;
	return 0;
}