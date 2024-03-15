#ifndef S21_ANT_H

#include <math.h>

#include <algorithm>
#include <random>
#include <vector>

#include "s21_graph.h"

using namespace std;

namespace s21 {

class Ant {
 public:
  Ant(Graph& graph, std::vector<double>& pheromone,
      std::vector<double>& visibility, std::vector<double>& deltapheromone,
      std::mt19937& gen, double alpha, double beta);
  void constructTour();
  vector<int> GetTour() { return tour_; }

 private:
  vector<int> tour_;
  Graph& graph_;
  double alpha_;
  double beta_;
  std::vector<double>& pheromone_;
  std::vector<double>& deltapheromone_;
  std::vector<double>& visibility_;
  std::mt19937& gen;

  int selectNextCity(int currentCity, const vector<bool>& visited);
};

}  // namespace s21

#endif  // S21_ANT_H_