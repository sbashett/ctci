#include <iostream>
#include <vector>

using namespace std;

class LLNode{
public:
	int data;
	LLNode* next;
	LLNode();
	LLNode(int);
	void printll();
	void appendtoTail(int);
	LLNode* reverseList();
};

LLNode::LLNode() : data(0), next(NULL){}
LLNode::LLNode(int data) : data(data), next(NULL){}

void LLNode::printll(){
	LLNode *currentNode = this;

	while(currentNode->next != NULL){
		cout << currentNode->data << "->";
		currentNode = currentNode->next;
	}
	cout << currentNode->data << '\n';
	return;
}

void LLNode::appendtoTail(int data){
	LLNode *currentNode = this;
	while(currentNode->next != NULL) currentNode = currentNode->next;
	currentNode->next = new LLNode(data);
	return;
}

LLNode* LLNode::reverseList(){

	LLNode *head = this;
	LLNode *current = this;
	LLNode *prev = NULL;
	LLNode *next = current->next;

	while(next != NULL){
		current->next = prev;
		prev = current;
		current = next;
		next = current->next;
	}

	current->next = prev;
	head = current;

	return head;
}

LLNode* createLL(vector<int>& vals){
	LLNode *head = new LLNode(vals[0]);
	vector<int>::iterator it;

	LLNode *currentNode = head;
	for(it=vals.begin()+1; it!=vals.end(); it++){
		currentNode->next = new LLNode(*it);
		currentNode = currentNode->next;
	}

	return head;
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	vector<int> vals{1,2,3,4,5,6,7,8};

	LLNode *head = createLL(vals);

	head->printll();

	head = head->reverseList();
	head->printll();
}