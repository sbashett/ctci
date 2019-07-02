#include <vector>
#include <stack>
#include <map>

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

	//filling elements of stack
	void fill_stack(stack<int>*, vector<int>*);


	/********************** graph related **************************/
	// defined in coomon_graphs_trees.cpp 
	class GraphNode{
	public:
		vector<GraphNode*> adj;
		string name;
		int data;
		bool visited; // used by dfs and bfs
		int id; // used by dfs and bfs
		GraphNode* parent; // used by dfs and bfs

		GraphNode();
		GraphNode(int id);
		GraphNode(string name);
	};

	class Graph{
	public:
		map<int, GraphNode*> map_nodes;
		void print_graph();
		void clear_graph();
		void reset_visited_flags();
	};

	void createGraph_manual(Graph&, vector<vector<int>>&); // need to change the data manually every time

	bool depthSearch(GraphNode*, int, SingleLL*&);
	bool breadthSearch(GraphNode*, int, SingleLL*&);

	/************************************************************************/

	class BinTreeNode{
	public:
		BinTreeNode* left;
		BinTreeNode* right;
		int data;
		int level;
		BinTreeNode* parent;

		BinTreeNode() : left(NULL), right(NULL), data(0), level(-1), parent(NULL) {}
		BinTreeNode(int d) : left(NULL), right(NULL), data(d), level(-1), parent(NULL) {}
	};

	enum TreeTraverseMode {INORDER, PREORDER, POSTORDER};
	void print_binary_tree(BinTreeNode*, TreeTraverseMode);

	// void buildBST();

}
