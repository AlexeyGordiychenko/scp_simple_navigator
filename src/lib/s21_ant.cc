#ifndef S21_ANT_CC
#define S21_ANT_CC

#include "s21_ant.h"

s21::Ant::Ant(Graph& graph, std::vector<double>& pheromone,
              std::vector<double>& visibility,
              std::vector<double>& deltapheromone, std::mt19937& gen,
              double alpha, double beta)
    : graph_(graph),
      alpha_(alpha),
      beta_(beta),
      pheromone_(pheromone),
      deltapheromone_(deltapheromone),
      visibility_(visibility),
      gen(gen) {}

void s21::Ant::constructTour() {
  tour_.clear();
  vector<bool> visited(graph_.GetSize(), false);

  std::uniform_int_distribution<int> dist(0, graph_.GetSize() - 1);
  int start_city = dist(gen);

  tour_.push_back(start_city);
  visited[start_city] = true;

  for (int i = 0; i < (int)graph_.GetSize() - 1; i++) {
    int currentCity = tour_.back();
    int nextCity = selectNextCity(currentCity, visited);
    tour_.push_back(nextCity);
    visited[nextCity] = true;
  }
  tour_.push_back(start_city);

  double totalDistance = 0.0;
  for (int i = 0; i < (int)tour_.size() - 1; i++) {
    totalDistance +=
        graph_.GetGraph()[tour_[i] * graph_.GetSize() + tour_[i + 1]];
  }
  totalDistance +=
      graph_.GetGraph()[tour_.back() * graph_.GetSize() + tour_.front()];

  for (int i = 0; i < (int)tour_.size() - 1; i++) {
    int from = tour_[i];
    int to = tour_[i + 1];
    deltapheromone_[from * graph_.GetSize() + to] += 1.0 / totalDistance;
  }

  int distance = 0;
  for (int i = 0; i < (int)this->GetTour().size() - 1; i++)
    distance += graph_.GetGraph()[this->GetTour()[i] * graph_.GetSize() +
                                  this->GetTour()[i + 1]];
  distance += graph_.GetGraph()[this->GetTour().back() * graph_.GetSize() +
                                this->GetTour().front()];
}

int s21::Ant::selectNextCity(int currentCity, const vector<bool>& visited) {
  vector<double> probabilities(graph_.GetSize(), 0.0);
  double totalProbability = 0.0;
  for (int city = 0; city < (int)graph_.GetSize(); city++) {
    if (!visited[city]) {
      probabilities[city] =
          pow(pheromone_[currentCity * graph_.GetSize() + city], alpha_) *
          pow(visibility_[currentCity * graph_.GetSize() + city], beta_);
      totalProbability += probabilities[city];
    }
  }

  for (int city = 0; city < (int)graph_.GetSize(); city++) {
    if (!visited[city]) {
      probabilities[city] /= totalProbability;
    }
  }

  std::uniform_int_distribution<int> dist(0, 99);
  double selectionValue = ((double)dist(gen)) / 100.0;

  double currentSum = 0.0;
  for (int city = 0; city < (int)graph_.GetSize(); city++) {
    if (!visited[city]) {
      currentSum += probabilities[city];
      if (currentSum >= selectionValue) {
        return city;
      }
    }
  }
  return -1;
}

#endif  // S21_ANT_CC