#include "common_header.hpp"
#include <iostream>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  vector<vector<int>> edges{{1, 2}, {1, 6}, {2, 3}, {2, 5},
                            {4, 2}, {4, 5}, {5, 3}, {6, 4}};
  myspace::Graph graph;
  myspace::createGraph_manual(graph, edges);
  graph.print_graph();

  int source_id = 1, des_id = 5;
  if (argc > 1) {
    source_id = (int)argv[1][0] - 48;
    des_id = (int)argv[2][0] - 48;
  }
  myspace::SingleLL *path_seq;

  myspace::GraphNode *ptr_source_node = graph.map_nodes.find(source_id)->second;

  bool flag = myspace::breadthSearch(ptr_source_node, des_id, path_seq);

  if (flag) {
    cout << "path exists between " << source_id << " and " << des_id << ": \n";
    // path_seq->appendToTail(ptr_source_node->id);
    myspace::printSingleLL(path_seq);
  }

  else
    cout << "path does not exist between " << source_id << " and " << des_id
         << "\n";

  graph.clear_graph();
  return 0;
}
