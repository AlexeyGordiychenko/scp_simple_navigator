#ifndef S21_A2_GRAPH_ALGORITHMS_H_
#define S21_A2_GRAPH_ALGORITHMS_H_

#include <vector>

#include "../containers/s21_queue.h"
#include "../containers/s21_stack.h"
#include "s21_tsm_result.h"

namespace s21 {
class Graph;

class GraphAlgorithms {
 public:
  // Methods
  static std::vector<uint32_t> DepthFirstSearch(Graph& graph,
                                                uint32_t start_vertex);
  static std::vector<uint32_t> BreadthFirstSearch(Graph& graph,
                                                  uint32_t start_vertex);
  static int GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                            int vertex2);
  static void GetShortestPathsBetweenAllVertices(
      Graph& graph);  // TODO: return value
  static std::vector<uint32_t> GetLeastSpanningTree(Graph& graph);
  static TsmResult& SolveTravelingSalesmanProblem(Graph& graph);
};
}  // namespace s21
#endif  // S21_A2_GRAPH_ALGORITHMS_H_