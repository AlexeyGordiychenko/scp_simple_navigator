#include "s21_tsp_aco.h"

#include <algorithm>
#include <stdexcept>

#include "s21_ant.h"

s21::TsmResult s21::TSPAntColonyOptimization::Solve() {
  if (graph_.GetSize() <= 0) throw std::runtime_error("Graph is empty.");
  if (graph_.GetSize() == 1) {
    return {std::vector<u_int32_t>{0, 0}, (double)graph_.GetGraph()[0]};
  }

  const int NUM_ANTS = 1500;
  const int NUM_ITER = 30;
  const double ALPHA = 1;
  const double BETA = 2;
  const double Q = .4;
  const int SIZE = graph_.GetSize() * graph_.GetSize();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, graph_.GetSize());

  std::vector<double> pheromone(SIZE, 1.0);
  std::vector<double> visibility(SIZE, 1.0);
  for (int i = 0; i < SIZE; i++) {
    visibility[i] = 1.0 / graph_.GetGraph()[i];
    if (std::isnan(visibility[i])) visibility[i] = 0;
  }

  double best_distance = INT32_MAX;
  std::vector<u_int32_t> best_tour;

  for (int iter = 0; iter < NUM_ITER; iter++) {
    std::vector<double> deltapheromone(SIZE, 0.0);
    for (int i = 0; i < NUM_ANTS; i++) {
      Ant ant(graph_, pheromone, visibility, deltapheromone, gen, ALPHA, BETA);
      ant.constructTour();
      int distance = 0;
      for (int i = 0; i < (int)ant.GetTour().size() - 1; i++)
        distance += graph_.GetGraph()[ant.GetTour()[i] * graph_.GetSize() +
                                      ant.GetTour()[i + 1]];
      distance += graph_.GetGraph()[ant.GetTour().back() * graph_.GetSize() +
                                    ant.GetTour().front()];
      if (distance < best_distance) {
        best_distance = distance;
        best_tour = ant.GetTour();
      }
    }
    for (int i = 0; i < SIZE; i++)
      pheromone[i] = (1.0 - Q) * pheromone[i] + deltapheromone[i];
  }

  for_each(best_tour.begin(), best_tour.end(), [](u_int32_t &i) { ++i; });

  return {best_tour, best_distance};
}