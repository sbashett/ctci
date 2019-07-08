#include <iostream>
#include <vector>
#include <iterator> // distance
#include <algorithm> // find
#include <map>

using namespace std;

typedef map<int,int> MAP;
typedef map<int,int>::iterator MapIterator;
typedef vector<int> VECTOR;
typedef vector<int>::iterator VecIterator;

class BinTreeNode{
public:
	int data;
	BinTreeNode *left;
	BinTreeNode *right;
	int level;

	BinTreeNode();
	BinTreeNode(int);
	void printTree();
};

BinTreeNode::BinTreeNode() : data(0), left(NULL), right(NULL), level(0){}
BinTreeNode::BinTreeNode(int data) : data(data), left(NULL), right(NULL), level(0){}

void BinTreeNode::printTree(){
	BinTreeNode* head = this;

	if(head->right != NULL)
		head->right->printTree();
	
	for(int it=0; it<this->level; it++)
		cout << "    ";
	cout << head->data << "\n";

	if(head->left != NULL)
		head->left->printTree();	

	return;
}

int getArrayIndex(VECTOR* vec, int val){
	VecIterator findIterator;
	
	findIterator = find(vec->begin(), vec->end(), val);
	if(findIterator == vec->end())
		return -1;
	else
		return distance(vec->begin(), findIterator);
}

BinTreeNode* buildTree(VECTOR* preorder, VECTOR* inorder, int& preIndex, int lindex, int rindex, int level){

	int inorderSearchIndex;
	if(lindex > rindex)
		return NULL;
	if((uint)preIndex >= preorder->size())
		return NULL;

	// cout << lindex << rindex << preIndex << '\n';
	// if(rindex == 9 || preIndex == 9){
	// 	cout << "error here";
	// 	return NULL;
	// }

	BinTreeNode *node = new BinTreeNode(preorder->at(preIndex));
	node->level = level;
	inorderSearchIndex = getArrayIndex(inorder, node->data);
	preIndex++;


	if(lindex == rindex)
		return node;

	node->left = buildTree(preorder, inorder, preIndex, lindex, inorderSearchIndex-1, level+1);
	node->right = buildTree(preorder, inorder, preIndex, inorderSearchIndex+1, rindex, level+1);

	return node;
}


bool isKeyExists(MAP& hashmap, int key){
	MapIterator findIterator;
	findIterator = hashmap.find(key);

	if(findIterator == hashmap.end())
		return false;
	else 
		return true;
}

void countPathsWithSum(BinTreeNode *head,int targetSum,int& totalCount, int cumsum, MAP& hashmap){
	if(head == NULL) return;
	cumsum += head->data;

	if(isKeyExists(hashmap, cumsum))
		hashmap[cumsum]++;
	else
		hashmap.insert(make_pair(cumsum, 1));

	int diffCumSum = cumsum-targetSum;

	if(isKeyExists(hashmap, diffCumSum)){
		totalCount += hashmap[diffCumSum];
		if(diffCumSum == cumsum) // this might happen when targer sum is 0
			totalCount--;
	}

	if(head->left != NULL)
		countPathsWithSum(head->left, targetSum, totalCount, cumsum, hashmap);
	if(head->right != NULL)
		countPathsWithSum(head->right, targetSum, totalCount, cumsum, hashmap);

	//decrease cumsum count before returning from stack
	hashmap[cumsum]--;
	if(hashmap[cumsum] == 0)
		hashmap.erase(cumsum);

	return;
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){

	/*  SOMETHING IS WORNG WITH CREATING A BINARY TREE*/
	VECTOR preorder{10,5,3,3,-2,2,1,-3,11};
	VECTOR inorder{3,3,-2,5,2,1,10,-3,11};

	int preIndex = 0;
	BinTreeNode* head = buildTree(&preorder, &inorder, preIndex, 0, preorder.size()-1, 0);

	if(head != NULL)
		head->printTree();

	int totalCount = 0;
	int targetSum = 8;
	MAP hashmap;
	countPathsWithSum(head, targetSum, totalCount, 0, hashmap);

	cout << "total number of paths with targetSum 8 are: " << totalCount;

	return 0;
}