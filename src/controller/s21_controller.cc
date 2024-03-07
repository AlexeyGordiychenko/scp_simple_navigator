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

std::pair<std::vector<uint32_t>, uint32_t>
s21::Controller::GetLeastSpanningTree() {
  return std::pair<std::vector<uint32_t>, uint32_t>(
      s21::GraphAlgorithms::GetLeastSpanningTree(graph_), graph_.GetSize());
}
