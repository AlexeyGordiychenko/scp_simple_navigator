#ifndef SCP_A2_GRAPH_ALGORITHMS_H_
#define SCP_A2_GRAPH_ALGORITHMS_H_

#include <random>
#include <vector>

#include "../containers/scp_queue.h"
#include "../containers/scp_stack.h"
#include "tsp/scp_tsm_result.h"

namespace scp {
class Graph;

class GraphAlgorithms {
 public:
  // Methods
  static std::vector<uint32_t> DepthFirstSearch(const Graph& graph,
                                                uint32_t start_vertex);
  static std::vector<uint32_t> BreadthFirstSearch(const Graph& graph,
                                                  uint32_t start_vertex);
  static int GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                            int vertex2);
  static std::vector<uint32_t> GetShortestPathsBetweenAllVertices(Graph& graph);
  static std::vector<uint32_t> GetLeastSpanningTree(const Graph& graph);
  static TsmResult SolveTravelingSalesmanProblem(Graph& graph);
  static TsmResult SolveTravelingSalesmanProblemAnnealing(
      const Graph& graph, const double initial_temperature,
      const double cooling_rate, const unsigned seed = std::random_device{}());
  static TsmResult SolveTravelingSalesmanProblemNearestNeighbor(
      const Graph& graph, const unsigned seed = std::random_device{}());
};
}  // namespace scp
#endif  // SCP_A2_GRAPH_ALGORITHMS_H_