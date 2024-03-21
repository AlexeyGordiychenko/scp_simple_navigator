#ifndef SCP_A2_TSP_NEAREST_NEIGHBOR_H_
#define SCP_A2_TSP_NEAREST_NEIGHBOR_H_

#include <random>
#include <vector>

#include "../scp_graph.h"
#include "scp_tsm_result.h"

namespace scp {
class TSPNearestNeighbor {
 public:
  // Constructors and the Destructor
  TSPNearestNeighbor(const Graph& graph,
                     const unsigned seed = std::random_device{}())
      : graph_(graph), generator_(seed) {}
  TSPNearestNeighbor(const TSPNearestNeighbor&) = delete;
  TSPNearestNeighbor& operator=(const TSPNearestNeighbor&) = delete;
  TSPNearestNeighbor(TSPNearestNeighbor&&) = delete;
  TSPNearestNeighbor& operator=(TSPNearestNeighbor&&) = delete;
  ~TSPNearestNeighbor() = default;

  // Main method
  TsmResult Solve();

 private:
  const Graph& graph_;
  std::mt19937 generator_;

  uint32_t FindNearestUnvisited(const uint32_t current,
                                const std::vector<bool>& visited);
};
}  // namespace scp
#endif  // SCP_A2_TSP_NEAREST_NEIGHBOR_H_