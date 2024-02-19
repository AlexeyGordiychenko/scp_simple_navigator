#ifndef S21_A2_GRAPH_ALGORITHMS_H_
#define S21_A2_GRAPH_ALGORITHMS_H_

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"

namespace s21 {
class Graph;

struct TsmResult {
  int* vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  // Constructors and the Destructor
  GraphAlgorithms() = default;
  GraphAlgorithms(const GraphAlgorithms&) = delete;
  GraphAlgorithms& operator=(const GraphAlgorithms&) = delete;
  GraphAlgorithms(GraphAlgorithms&&) = delete;
  GraphAlgorithms& operator=(GraphAlgorithms&&) = delete;
  ~GraphAlgorithms() = default;

  // Methods
  stack<int> DepthFirstSearch(Graph& graph, int start_vertex);
  queue<int> BreadthFirstSearch(Graph& graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph& graph, int vertex1, int vertex2);
  void GetShortestPathsBetweenAllVertices(Graph& graph);  // TODO: return value
  void GetLeastSpanningTree(Graph& graph);                // TODO: return value
  TsmResult& SolveTravelingSalesmanProblem(Graph& graph);
};
}  // namespace s21
#endif  // S21_A2_GRAPH_ALGORITHMS_H_