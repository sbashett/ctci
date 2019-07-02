#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "common_header.hpp"

using namespace std;

namespace myspace{

	GraphNode::GraphNode() : visited(false) , id(-1), parent(NULL){}
	GraphNode::GraphNode(int id) : visited(false) , id(id), parent(NULL){}
	GraphNode::GraphNode(string name) : name(name), visited(false), parent(NULL){}

	void createGraph_manual(Graph& graph, vector<vector<int>>& edges){
		map<int, GraphNode*>::iterator find_iterator_parent, find_iterator_child;

		for(auto& edge: edges){
			find_iterator_parent = graph.map_nodes.find(edge.at(0));
			if(find_iterator_parent == graph.map_nodes.end()){ // new vertex
				graph.map_nodes.insert(make_pair(edge.at(0), new GraphNode(edge[0])));
				find_iterator_parent = graph.map_nodes.find(edge.at(0));
			}

			find_iterator_child = graph.map_nodes.find(edge.at(1));
			if(find_iterator_child == graph.map_nodes.end()){ // new vertex
				graph.map_nodes.insert(make_pair(edge.at(1), new GraphNode(edge[1])));
				find_iterator_child = graph.map_nodes.find(edge.at(1));
			}

			find_iterator_parent->second->adj.push_back(find_iterator_child->second);
			// if(find_iterator_child->parent==NULL)
		}
	}

	void Graph::print_graph(){
		cout << "adjacency list of graph:\n";

		for(auto n : this->map_nodes){ // iterate over each pair object in map

			cout << n.second->id << ": ";
			for(auto ptr_adj_nodes : n.second->adj){
				cout << ptr_adj_nodes->id << ' ';
			}
			cout << '\n';
		}

	}

	void Graph::clear_graph(){
		for(auto n : this->map_nodes){
			n.second->adj.clear(); 
			delete n.second;
		}
		map_nodes.clear();
	}

	void Graph::reset_visited_flags() {
		for(auto n : this->map_nodes) n.second->visited=false;
	}

	bool depthSearch(GraphNode* ptr_source_node, int des_id, SingleLL*& path_seq){

		bool pathExist = false;

		for(auto ptr_adj_nodes : ptr_source_node->adj){
			if(ptr_adj_nodes->visited) continue;
			// cout << ptr_adj_nodes->id << ' ';
			
			ptr_adj_nodes->visited = true;
			ptr_adj_nodes->parent = ptr_source_node;

			if(ptr_adj_nodes->id == des_id){
				pathExist = true;
				path_seq = new SingleLL(ptr_adj_nodes->id);
				return pathExist;
			}

			pathExist=depthSearch(ptr_adj_nodes, des_id, path_seq);

			if(pathExist){
				path_seq->appendToTail(ptr_adj_nodes->id);
				return pathExist;
			} 
		}

		return pathExist;
	}

	bool breadthSearch(GraphNode* ptr_source_node, int des_id, SingleLL*& path_seq){
		queue<GraphNode*> process_queue;
		GraphNode* current_node=NULL;
		process_queue.push(ptr_source_node);
		bool pathExist = false;
		
		while(!process_queue.empty()){
			current_node = process_queue.front();
			// cout << current_node->id << ' ';

			if(current_node->visited){
				process_queue.pop();
				continue;
			}

			if(current_node->id == des_id){
				pathExist = true;
				break;
			}

			for(auto ptr_adj_nodes : current_node->adj){
				if(ptr_adj_nodes->visited == true) continue;
				if(ptr_adj_nodes->parent == NULL) ptr_adj_nodes->parent = current_node;
				process_queue.push(ptr_adj_nodes);
			}

			current_node->visited = true;
			process_queue.pop();
		}

		queue<GraphNode*> empty_queue;
		swap(process_queue, empty_queue); // clearing queue

		if(pathExist){
			path_seq = new SingleLL(current_node->id);

			while(current_node->parent != NULL){
				path_seq->appendToTail(current_node->parent->id);
				current_node = current_node->parent;
			}
		}

		return pathExist;
	}

	/*********************** trees **************************/

	void print_binary_tree(BinTreeNode* head, TreeTraverseMode order){

		if(order==INORDER){
			if(head->left != NULL) print_binary_tree(head->left, order);
			cout << head->data << ", ";
			if(head->right != NULL) print_binary_tree(head->right, order);
		}

		else if(order==PREORDER){
			cout << head->data << ", ";
			if(head->left != NULL) print_binary_tree(head->left, order);
			if(head->right != NULL) print_binary_tree(head->right, order);			
		}

		else if(order==POSTORDER){
			if(head->left != NULL) print_binary_tree(head->left, order);
			if(head->right != NULL) print_binary_tree(head->right, order);			
			cout << head->data << ", ";
		}

		else cout << "given traversal order is not valid";
	}


} //myspace
