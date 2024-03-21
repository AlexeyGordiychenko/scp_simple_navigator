#ifndef SCP_A2_TSP_ANNEALING_H_
#define SCP_A2_TSP_ANNEALING_H_

#include <random>
#include <vector>

#include "../scp_graph.h"
#include "scp_tsm_result.h"

namespace scp {

class TSPAnnealing {
 public:
  // Constructors and the Destructor
  TSPAnnealing(const Graph& graph, const double initial_temperature,
               const double cooling_rate,
               const unsigned seed = std::random_device{}())
      : graph_(graph),
        temperature_(initial_temperature),
        cooling_rate_(cooling_rate),
        generator_(seed) {}
  TSPAnnealing(const TSPAnnealing&) = delete;
  TSPAnnealing& operator=(const TSPAnnealing&) = delete;
  TSPAnnealing(TSPAnnealing&&) = delete;
  TSPAnnealing& operator=(TSPAnnealing&&) = delete;
  ~TSPAnnealing() = default;

  // Main method
  TsmResult Solve();

 private:
  const Graph& graph_;
  double temperature_;
  const double cooling_rate_;
  std::mt19937 generator_;

  TsmResult GenerateRandomResult();
  TsmResult SwapVertices(const scp::TsmResult& result);
  void CalculateCost(TsmResult& result);
};
}  // namespace scp
#endif  // SCP_A2_TSP_ANNEALING_H_