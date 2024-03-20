#ifndef S21_A2_TSP_ACO_H_
#define S21_A2_TSP_ACO_H_

#include <random>
#include <vector>

#include "../s21_graph.h"
#include "s21_tsm_result.h"

namespace s21 {
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
}  // namespace s21
#endif  // S21_A2_TSP_ACO_H_