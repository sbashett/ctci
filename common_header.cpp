#include "common_header.hpp"
#include <iostream>
#include <vector>

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
/*
	template <typename T>
	class SingleLL{
		SingleLL next = null;
		T data;
		
		public SingleLL(T d){
			data = d;
		}

		void appendToTail(T d){
			SingleLL<T> *end = new SingleLL<T>(d);
			SingleLL<T> *current = this;
			
			while(current->next != null){
				current=current->next;
			}
			current->next = end;
		}

	}
*/
	
	// Single linked list class definition
	SingleLL::SingleLL() : next(NULL), data(0) {}
	SingleLL::SingleLL(int d) : next(NULL), data(d) {}
	void SingleLL::appendToTail(int d){
		SingleLL *end = new SingleLL(d);
		SingleLL *current = this;
		while (current->next != NULL){
			current = current->next;
			}
		current->next = end;
		}
	
	// delete node from single linked list function
	SingleLL* deleteSingleLLNode(SingleLL *head, int d){
		SingleLL *current = head;
		
		if(current->data==d){
			if(current->next == NULL) return NULL;
			else return current->next;
		}

		while(current->next != NULL){
			if(current->next->data == d){
				current->next=current->next->next;
				return head;
			}
			current=current->next;
		}

		return head;
	}

	// single linked list node delte given pointer to the node
	SingleLL* deleteSingleLLNode(SingleLL *head, SingleLL *node){
		SingleLL *current = head;

		if(current == node){
			if(current->next == NULL) return NULL;
			else return current->next;
		}
		while(current->next != NULL){
			if(current->next == node){
				current->next = current->next->next;
				return head;
			}
			current=current->next;
		}

		return head;

	}
	
	//generate single linked list with given data
	SingleLL* generateSingleLL(vector<int>* array){
		if(array->size() == 0) return NULL;
		SingleLL* head = new SingleLL();
		head->data = array->at(0);
		SingleLL* current = head;

		for(vector<int>::iterator it=(array->begin()+1); it!=array->end(); ++it){
			current->next = new SingleLL(*it);
			current=current->next;
		}

		return head;

	}

	//print elements of single linked list
	int printSingleLL(SingleLL* head){
		if(head==NULL) {
			cout << "NULL\n";
			
			}
		SingleLL* current=head;
		cout << current->data;
		current = current->next;

		while(current != NULL){
			cout << " -> " << current->data;
			current = current->next;
			}

		cout << '\n';
		return 0;
	}


} // myspace 
