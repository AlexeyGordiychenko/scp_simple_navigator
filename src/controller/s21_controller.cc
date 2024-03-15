#include "s21_controller.h"

void s21::Controller::LoadGraphFromFile(const std::string& filename) {
  graph_.LoadGraphFromFile(filename);
}

std::vector<uint32_t> s21::Controller::DepthFirstSearch(uint32_t start_vertex) {
  return s21::GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);
}

std::vector<uint32_t> s21::Controller::BreadthFirstSearch(
    uint32_t start_vertex) {
  return s21::GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);
}

int s21::Controller::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  return s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, vertex1,
                                                              vertex2);
}

std::pair<std::vector<uint32_t>, uint32_t>
s21::Controller::GetShortestPathsBetweenAllVertices() {
  return std::pair<std::vector<uint32_t>, uint32_t>(
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_),
      graph_.GetSize());
}

std::pair<std::vector<uint32_t>, uint32_t>
s21::Controller::GetLeastSpanningTree() {
  return std::pair<std::vector<uint32_t>, uint32_t>(
      s21::GraphAlgorithms::GetLeastSpanningTree(graph_), graph_.GetSize());
}

s21::TsmResult s21::Controller::SolveTravelingSalesmanProblemAnnealing() {
  return s21::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
      graph_, 1000, 0.9);
}

s21::TsmResult s21::Controller::SolveTravelingSalesmanProblemNearestNeighbor() {
  return s21::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(
      graph_);
}
