#include "s21_tsp_NN.h"

#include <algorithm>
#include <stdexcept>

s21::TsmResult s21::TSPNearestNeighbor::Solve() {
  if (graph_.GetSize() <= 0) throw std::runtime_error("Graph is empty.");
  if (!graph_.IsConnected())
    throw std::runtime_error("Graph is not connected.");

  auto matrix = graph_.GetGraph();
  auto size = graph_.GetSize();

  TsmResult result = {{}, 0.0};
  std::vector<bool> visited(size, false);
  std::uniform_real_distribution<> dis(0, size - 1);
  uint32_t start_vertex = dis(generator_);
  uint32_t current_vertex = start_vertex;

  result.vertices.push_back(current_vertex + 1);
  visited[current_vertex] = true;

  // Main loop
  for (uint32_t i = 1; i < size; ++i) {
    uint32_t nearest_vertex = FindNearestUnvisited(current_vertex, visited);
    result.vertices.push_back(nearest_vertex + 1);
    result.distance += matrix[current_vertex * size + nearest_vertex];
    visited[nearest_vertex] = true;
    current_vertex = nearest_vertex;
  }

  // Return to the starting vertex
  result.distance += matrix[current_vertex * size + start_vertex];
  result.vertices.push_back(result.vertices.front());

  return result;
}

uint32_t s21::TSPNearestNeighbor::FindNearestUnvisited(
    const uint32_t current_vertex, const std::vector<bool>& visited) {
  auto matrix = graph_.GetGraph();
  auto size = graph_.GetSize();

  uint32_t nearest_vertex = 0;
  uint32_t min_distance = std::numeric_limits<uint32_t>::max();
  for (uint32_t vertex = 0; vertex < size; ++vertex) {
    if (!visited[vertex] &&
        matrix[current_vertex * size + vertex] < min_distance) {
      min_distance = matrix[current_vertex * size + vertex];
      nearest_vertex = vertex;
    }
  }
  return nearest_vertex;
}
