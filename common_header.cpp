#include "common_header.hpp"
#include <iostream>

using namespace std;

namespace myspace{
	void print_matrix(int *matrix, int M, int N){
		for (int rows=0; rows < M; rows++){
			for (int cols=0; cols < N; cols++){
				cout << *(matrix+ rows*N + cols) << "	";
			}
	
			cout << "\n";
		}
	}

} // myspace 
