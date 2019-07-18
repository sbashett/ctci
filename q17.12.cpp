#include<iostream>
#include <queue>
#include <vector>
#include<array>

using namespace std;

class BiNode{
public:
	BiNode *node1;
	BiNode *node2;
	int data;
	BiNode(int);
};

BiNode::BiNode(int data) : node1(NULL), node2(NULL), data(data) { }


BiNode* fill_BST_helper(int arr[], int start, int end){

	if(start > end)
		return NULL;

	int mid = (start + end)/2;
	BiNode *head = new BiNode(arr[mid]);

	head->node1 = fill_BST_helper(arr, start, mid-1);
	head->node2 = fill_BST_helper(arr, mid+1, end);

	return head;
}

BiNode* fill_BST( ){

	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

	return fill_BST_helper(arr, 0, sizeof(arr)/sizeof(arr[0]) -1 );
}


bool checkCondition(BiNode* node){

	// cout << endl << "in check condition: " << node->data << endl;

	bool check_left_link, check_right_link;

	check_left_link = (node->node1->node2 == node);
	check_right_link = (node->node2->node1 == node);

	// cout << " test1, test2: " << check_left_link << check_right_link << endl;

	if( node == NULL )
		return true;

	if( check_left_link || check_right_link ){

		if(!check_left_link)
			node->node1->node2 = node;

		if(!check_right_link)
			node->node2->node1 = node;

		return true;
	}

	return false;
}

BiNode* traverseExtremeLeft(BiNode* node){

	while( node->node1 != NULL )
		node = node->node1;

	return node;
}


BiNode* traverseExtremeRight(BiNode* node){

	while( node->node2 != NULL )
		node = node->node2;

	return node;
}

void reconnect_right_link(BiNode *node){

	BiNode *connectNode = traverseExtremeLeft(node->node2);

	node->node2 = connectNode;
	connectNode->node1 = node;

	cout << "reconnecting right link to: " << connectNode->data << endl;
	return;
}

void reconnect_left_link(BiNode *node){

	BiNode *connectNode = traverseExtremeRight(node->node1);

	node->node1 = connectNode;
	connectNode->node2 = node;

	cout << "reconnecting left link to: " << connectNode->data << endl;

	return;
}

BiNode* generate_inplace_doubleLL(BiNode *treeHead){

	if(treeHead == NULL)
		return NULL;

	queue<BiNode*> process_queue;
	process_queue.push(treeHead);

	BiNode* currentNode = NULL;
	BiNode* doubleLLHead = NULL;

	doubleLLHead = traverseExtremeLeft(treeHead);

	while(!process_queue.empty()){
		
		currentNode = process_queue.front();
		if( (currentNode == doubleLLHead) || checkCondition(currentNode) ){
			process_queue.pop();
			continue;
		}

		cout << endl << "processing node: " << currentNode->data << endl;

		if(currentNode->node1 != NULL)
			process_queue.push(currentNode->node1);
		if(currentNode->node2 != NULL)
			process_queue.push(currentNode->node2);

		reconnect_left_link(currentNode);
		// cout << "reconnected left link" << endl;
		reconnect_right_link(currentNode);
		// cout << "reconnected right link" << endl;

		process_queue.pop();
	}

	return doubleLLHead;
}

void print_reverse_doubleLL(BiNode* last){
	while(true){
		cout << last->data << ", ";
		
		if(last->node1 == NULL)
			break;
		last = last->node1;
	}

	cout << endl;

	return;
}

void print_doubleLL(BiNode* head){

	while(true){
		cout << head->data << ", ";
		
		if(head->node2 == NULL)
			break;
		head = head->node2;
	}

	cout << endl;

	print_reverse_doubleLL(head);

	return;
}

void printBST(BiNode* head){
	if(head == NULL)
		return;

	cout << head->data << ", ";
	printBST(head->node1);
	printBST(head->node2);
}

int main(void){

	BiNode *treeHead;

	treeHead = fill_BST();

	cout << "preorder traversal of input BST: " << endl;
	printBST(treeHead);
	cout << endl;

	BiNode *doubleLLHead = generate_inplace_doubleLL(treeHead);

	cout << endl;
	cout << "printing elements of double linked list in forward and backward order: " << endl;
	print_doubleLL(doubleLLHead);

	return 0;
}
