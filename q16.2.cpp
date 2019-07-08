#include <iostream>
#include <string>
#include <vector>
#include <ctype.h> //tolower
#include <algorithm> //transform

using namespace std;

class TrieNode{
public:
	typedef vector<TrieNode*> TRIECHILDREN;
	char letter;
	int freq; // this is the frequency of word made from root char to the current char
	TRIECHILDREN children;
	TrieNode();
	TrieNode(char);

	//increases the frequency of exisiting string or creates a new branch
	// returns true if new branch created or false if already exists and freq increases
	bool insert(string);
	// searches and returns the frequency of given string. If not found returns -1
	int find_word_frequency(string);
	void trimSpaces(string&);
};

TrieNode::TrieNode() : letter('\0'), freq(0) {}
TrieNode::TrieNode(char letter) : letter(letter), freq(1) {}

void TrieNode::trimSpaces(string& word){
	string whitespaces(" \t\f\v\n\r"); 
	word.erase(word.find_last_not_of(whitespaces)+1); //erase trailing
	word.erase(word.begin(), word.begin()+word.find_first_not_of(whitespaces)); // erase starting

	return;
}

bool TrieNode::insert(string word){
	// assuming the each word is extracted and parsed from the book
	transform(word.begin(), word.end(), word.begin(), ::tolower); //converting word to lowercase
	trimSpaces(word);

	TrieNode *currentNode = this;
	bool ret_flag = false;

	for(auto wordIterator : word){
		// string wordPart(word.begin(), wordIterator);
		TrieNode* child;
		TRIECHILDREN::iterator childIt;
		for(childIt = currentNode->children.begin(); childIt != currentNode->children.end(); childIt++){
			child = *childIt;
			if(wordIterator == child->letter){
				child->freq++;
				break;
			}
		}

		if(childIt == currentNode->children.end()){ // child not found so start bulding new branches
			ret_flag = true;
			TrieNode *newChild = new TrieNode(wordIterator);
			currentNode->children.push_back(newChild);
			currentNode = newChild;
		}

		else currentNode = child;
	}

	return ret_flag;
}

int TrieNode::find_word_frequency(string word){

	TrieNode *currentNode = this;

	for(auto wordIterator : word){
		
		TrieNode* child;
		TRIECHILDREN::iterator childIt;

		for(childIt = currentNode->children.begin(); childIt != currentNode->children.end(); childIt++){
			child = *childIt;
			if(wordIterator == child->letter){
				currentNode = child;
				break;
			}
		}

		if(child != currentNode){ // could not find the child for current letter
			return -1;
		}
	}

	return currentNode->freq;
}

int main([[maybe_unused]] int arg, [[maybe_unused]] char **argv){

	TrieNode *head = new TrieNode('\0');

	// for inserting 
	// bool ret_val;
	cout << head->insert("abcd") << ' ';
	cout << head->insert("abcd") << ' ';

	//for searchinf freq of word
	// int ret_val2;
	cout << '\n';
	cout << head->find_word_frequency("abcd");
	cout << '\n';

	return 0;
}
