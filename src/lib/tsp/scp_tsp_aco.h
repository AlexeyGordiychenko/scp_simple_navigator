#ifndef SCP_A2_TSP_ACO_H_
#define SCP_A2_TSP_ACO_H_

#include <random>
#include <vector>

#include "../scp_graph.h"
#include "scp_tsm_result.h"

namespace scp {
class TSPAntColonyOptimization {
 public:
  // Constructors and the Destructor
  TSPAntColonyOptimization(Graph& graph) : graph_(graph) {}
  TSPAntColonyOptimization(const TSPAntColonyOptimization&) = delete;
  TSPAntColonyOptimization& operator=(const TSPAntColonyOptimization&) = delete;
  TSPAntColonyOptimization(TSPAntColonyOptimization&&) = delete;
  TSPAntColonyOptimization& operator=(TSPAntColonyOptimization&&) = delete;
  ~TSPAntColonyOptimization() = default;

  // Main method
  TsmResult Solve();

 private:
  Graph& graph_;
};
}  // namespace scp
#endif  // SCP_A2_TSP_ACO_H_