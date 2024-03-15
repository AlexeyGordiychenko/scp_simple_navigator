#ifndef S21_A2_GRAPH_ALGORITHMS_H_
#define S21_A2_GRAPH_ALGORITHMS_H_

#include <random>
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
  static std::vector<uint32_t> GetShortestPathsBetweenAllVertices(Graph& graph);
  static std::vector<uint32_t> GetLeastSpanningTree(Graph& graph);
  static TsmResult& SolveTravelingSalesmanProblem(Graph& graph);
  static TsmResult SolveTravelingSalesmanProblemAnnealing(
      const Graph& graph, const double initial_temperature,
      const double cooling_rate, const unsigned seed = std::random_device{}());
  static TsmResult SolveTravelingSalesmanProblemNearestNeighbor(
      const Graph& graph, const unsigned seed = std::random_device{}());
};
}  // namespace s21
#endif  // S21_A2_GRAPH_ALGORITHMS_H_