#include <vector>

using namespace std;

namespace myspace{

	void print_matrix(int *matrix, int M, int N);
	
	// single linked list: class declaration
	class SingleLL {
		public:
			SingleLL *next;
			int data;
			SingleLL();
			SingleLL(int);
			void appendToTail(int);
		};

	// single linked list node delete given data value: function declaration
	SingleLL* deleteSingleLLNode(SingleLL*, int);
	
	// single linked list node delete given pointer to the node
	SingleLL* deleteSingleLLNode(SingleLL*, SingleLL*);

	//generate single linked list given vector of elements
	SingleLL* generateSingleLL(vector<int>*);

	//print elements of linked list
	int printSingleLL(SingleLL*);

}
