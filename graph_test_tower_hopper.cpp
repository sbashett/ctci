#include <iostream>
#include <map>
#include <queue>
#include <vector>

typedef int INDICES typedef map<INDICES, vector<LLNode *>> MYMAP;

enum GraphNodeState { WHITE = 0, GREY = 1, BLACK = 2 };

class GraphNode {
public:
  int data;
  int dist;
  GraphNodeState state;
  vector<GraphNode *> children;
  vector<GraphNode *> parents;
  GraphNode();
  GraphNode(int);
};

GraphNode::GraphNode() : data(-1), dist(0) {}
GraphNode::GraphNode(int data) : data(data), dist(0) {}

class Graph {
public:
  map<int, GraphNode *> map_nodes; // similar to adj list
  void print_graph();
  void resetNodeStates(); // includes resetting the state variable and the dist
                          // variable
  vector<GraphNode *>
  shortestPath(int); // breadth first search to find path to destination
  GraphNode *getNodePointer(int);
};

void Graph::resetNodeStates() {

  for (auto &map_pairs : map_nodes) {
    map_pairs.second()->state = WHITE;
    map_pairs.second()->dist = 0;
  }
}

void Graph::print_graph() {
  for (auto &map_pairs : this->map_nodes) {
    cout << map_pairs.first() << ":\n\t";

    cout << "children: ";
    for (auto &child : map_pairs.second->children) {
      cout << child->data << " ,";
    }

    cout << "\n\t parents: ";
    for (auto &parent : map_pairs.second->parents) {
      cout << parent->data << " ,";
    }
    cout << "\n";
  }
}

GraphNode *Graph::getNodePointer(int val) { return this->map_nodes[val]; }

vector<int> Graph::shortestPath(int src, int dst) {
  vector<int> shortestPath;
  queue<GraphNode *> process_queue;

  GraphNode *node_src = this->map_nodes[src];
  GraphNode *node_dest = this->map_nodes[dst];

  node_src->dist = 0;

  process_queue.push(node_src);
  GraphNode *currentNode;
  while (!process_queue.empty()) {
    currentNode = process_queue.front();

    if (currentNode->state == BLACK) {
      process_queue.pop();
      continue;
    }

    for (auto &child : curretnNode->children) {
      child->dist = currentNode->dist + 1;

      if (child->data == dst) { // destination found
        goto FILLPATH;
      }
    }
  }

FILLPATH:
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) { return 0; }
