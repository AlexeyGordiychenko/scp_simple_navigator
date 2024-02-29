#include "s21_graph_algorithms.h"

#include "s21_graph.h"

std::vector<uint32_t> s21::GraphAlgorithms::DepthFirstSearch(
    s21::Graph &graph, uint32_t start_vertex) {
  auto size = graph.GetSize();
  if (start_vertex > size) {
    throw std::out_of_range("Vertex doesn't exist.");
  }
  std::vector<bool> visited(size, false);
  s21::stack<uint32_t> stack;
  std::vector<uint32_t> traversal;

  stack.push(start_vertex - 1);

  while (!stack.empty()) {
    uint32_t vertex = stack.top();
    stack.pop();

    if (visited[vertex]) continue;
    traversal.push_back(vertex + 1);
    visited[vertex] = true;

    auto matrix = graph.GetGraph();
    for (uint32_t i = size - 1; i != UINT32_MAX; --i) {
      if (matrix[vertex * size + i] > 0 && !visited[i]) {
        stack.push(i);
      }
    }
  }

  return traversal;
}

std::vector<uint32_t> s21::GraphAlgorithms::BreadthFirstSearch(
    s21::Graph &graph, uint32_t start_vertex) {
  auto size = graph.GetSize();
  if (start_vertex > size) {
    throw std::out_of_range("Vertex doesn't exist.");
  }
  std::vector<bool> visited(size, false);
  s21::queue<uint32_t> queue;
  std::vector<uint32_t> traversal;

  queue.push(start_vertex - 1);

  while (!queue.empty()) {
    uint32_t vertex = queue.front();
    queue.pop();

    if (visited[vertex]) continue;
    traversal.push_back(vertex + 1);
    visited[vertex] = true;

    auto matrix = graph.GetGraph();
    for (uint32_t i = 0; i < size; ++i) {
      if (matrix[vertex * size + i] > 0 && !visited[i]) {
        queue.push(i);
      }
    }
  }

  return traversal;
}
