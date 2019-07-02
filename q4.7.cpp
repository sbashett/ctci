#include <iostream>
#include <map>
#include <vector>
#include <algorithm> // for find, remove
// #include "common_header.hpp"

using namespace std;

namespace Graphspace{
	enum NodeStatus {BLANK, PROCESSING, COMPLETED};

	class GraphNode{
	public:
		int data;
		vector<GraphNode*> children;
		vector<GraphNode*> parents;
		NodeStatus status;

		GraphNode();
		GraphNode(int);
	};

	typedef map<int, GraphNode*> GraphMap;

	class Graph{
	public:
		GraphMap map_nodes;
		vector<GraphNode*> vertices;
		void print_graph();
		void print_graph_nodes();
		void clear_graph();
		void create_graph(vector<vector<int>>&, vector<int>&);
	};

	// GraphNode class members
	GraphNode::GraphNode() : data(-1), status(BLANK) {}
	GraphNode::GraphNode(int d) : data(d), status(BLANK) {}


	// Graph class members
	void Graph::create_graph(vector<vector<int>>& edges, vector<int>& all_nodes){
		GraphMap& graph_map = this->map_nodes;
		GraphMap::iterator find_iterator_parent, find_iterator_child;
		pair<GraphMap::iterator, bool> ret_value;

		for(auto& edge : edges){
			ret_value = graph_map.insert(make_pair(edge[0], new GraphNode(edge[0])));
			find_iterator_parent = ret_value.first;

			ret_value = graph_map.insert(make_pair(edge[1], new GraphNode(edge[1])));
			find_iterator_child = ret_value.first;

			find_iterator_parent->second->children.push_back(find_iterator_child->second);
			find_iterator_child->second->parents.push_back(find_iterator_parent->second);
		}

		for(auto& node:all_nodes){
			find_iterator_parent = map_nodes.find(node);
			if(find_iterator_parent == map_nodes.end())
				map_nodes.insert(make_pair(node, new GraphNode(node)));
		}

		// // filling in all the available vertices
		// vector<GraphNode*>& vertices = this->vertices;
		// for(auto const& map_pairs:map_nodes)
		// 	vertices.push_back(map_pairs.second);

	}

	void Graph::print_graph(){
		cout << "adjacency list:\n";
		for(auto map_pairs : this->map_nodes){
			cout << map_pairs.first << ": ";
			for(auto adj : map_pairs.second->children) 
				cout << adj->data << ", ";
			cout << '\n';
		}
	}

	void Graph::print_graph_nodes(){
		cout << "graph nodes with parents and children:\n";
		for(auto map_pairs:this->map_nodes){
			cout << "node " << map_pairs.first << ":\n\tparents: ";

			for(auto& p : map_pairs.second->parents)
				cout << p->data << ", ";
			cout << "\n\tchildren: ";
			for(auto& c : map_pairs.second->children)
				cout << c->data << ", ";
			cout << '\n';
		}
	}

	void Graph::clear_graph(){
		for(auto map_pairs : this->map_nodes){
			map_pairs.second->children.clear();
			map_pairs.second->parents.clear();
			delete map_pairs.second;		
		}
		map<int, GraphNode*> empty_map;
		swap(this->map_nodes, empty_map);
	}
} // myspace

// check if element exists in the vector
bool isExist(vector<int> vec, const int val){
	vector<int>::iterator find_iter;
	find_iter = find(vec.begin(), vec.end(), val);
	if(find_iter == vec.end()) return false;
	else return true;
}

// check if an element exists in the hash map
bool isExist(Graphspace::GraphMap map_nodes, int node_val){
	Graphspace::GraphMap::iterator find_iter;
	find_iter = map_nodes.find(node_val);
	if(find_iter == map_nodes.end()) return false;
	else return true;
}

void remove_nodes_vector(vector<Graphspace::GraphNode*>& vec, vector<Graphspace::GraphNode*>& nodes){
	for(auto& n : nodes){
		remove(vec.begin(), vec.end(), n);
	}
}

// check if all of the incoming nodes exist in the final_sequence
// i.e, checking if all dependencies are satisfied
bool checkAllDependencies(vector<Graphspace::GraphNode*> &parents, const vector<int> &final_sequence){
	// cout << "parents: \n";
	// for(auto& p:parents) cout << p->data << ", ";
	// cout << "\n";

	if(parents.size() == 0) return true;
	vector<Graphspace::GraphNode*> remove_nodes;
	for(auto& node:parents){
		if(!isExist(final_sequence, node->data)){
			remove_nodes_vector(parents, remove_nodes);
			return false;
		}
		else
			remove_nodes.push_back(node);
	}
	remove_nodes_vector(parents, remove_nodes);
	return true;
}

bool get_final_sequence(vector<int>& final_sequence, const vector<int>& all_nodes, Graphspace::Graph& graph){
	
	Graphspace::GraphMap& graph_map = graph.map_nodes;
	Graphspace::GraphMap::iterator map_iter;
	unsigned int prev_final_seq_size=0;
	bool frstFlag=true;

	while(final_sequence.size() != all_nodes.size()){

		if(final_sequence.size()==all_nodes.size()) return true;
		if(!(frstFlag) && !(final_sequence.size() > prev_final_seq_size)){
			// cout << prev_final_seq_size << ',' << final_sequence.size() << '\n';
			return false;
		}
		else prev_final_seq_size = final_sequence.size();

		frstFlag = false;		

		for(auto& node:all_nodes){			
			if(isExist(final_sequence, node)) continue;
			if(!isExist(graph_map, node)) {
				cout << "node " << node << " doesnot exist in graph";
				return false;
			}

			// cout << "checking dependencies for node: " << node;
			map_iter = graph_map.find(node);

			if(checkAllDependencies(map_iter->second->parents, final_sequence))
				final_sequence.push_back(node);
		}
	}

	return true;

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	// vector<vector<int>> edges{{1,2},{1,6},{2,3},{2,5},{4,2},{4,5},{5,3},{6,4}};
	vector<vector<int>> edges{{1,4},{6,2},{2,4},{6,1},{4,3}};
	vector<int> all_nodes{1,2,3,4,5,6};

	Graphspace::Graph graph;
	graph.create_graph(edges, all_nodes);
	graph.print_graph();
	graph.print_graph_nodes();

	vector<int> final_sequence;

	bool isSeqValid = get_final_sequence(final_sequence, all_nodes, graph);

	if(!isSeqValid) cout << "could not find a sequence probably there is a cycle in dependency graph\n";
	else{
		cout << "sequence is:\n";
		for(auto& node:final_sequence) cout << node << ", ";
	}
	cout << '\n';

	graph.clear_graph();
	return 0;
}

