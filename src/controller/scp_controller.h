#ifndef SCP_A2_CONTROLLER_H_
#define SCP_A2_CONTROLLER_H_

#include "../lib/scp_graph.h"
#include "../lib/scp_graph_algorithms.h"
#include "../lib/tsp/scp_tsm_result.h"

namespace scp {

class Controller {
 public:
  Controller() = default;
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  ~Controller() = default;

  void LoadGraphFromFile(const std::string& filename);
  std::vector<uint32_t> DepthFirstSearch(uint32_t start_vertex);
  std::vector<uint32_t> BreadthFirstSearch(uint32_t start_vertex);
  int GetShortestPathBetweenVertices(int vertex1, int vertex2);
  std::pair<std::vector<uint32_t>, uint32_t>
  GetShortestPathsBetweenAllVertices();
  std::pair<std::vector<uint32_t>, uint32_t> GetLeastSpanningTree();
  TsmResult SolveTravelingSalesmanProblem();
  TsmResult SolveTravelingSalesmanProblemAnnealing();
  TsmResult SolveTravelingSalesmanProblemNearestNeighbor();

 private:
  Graph graph_;
};
}  // namespace scp
#endif  // SCP_A2_CONTROLLER_H_
