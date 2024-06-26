#include "scp_graph_algorithms.h"

#include <algorithm>
#include <limits>

#include "scp_graph.h"
#include "tsp/scp_tsp_NN.h"
#include "tsp/scp_tsp_aco.h"
#include "tsp/scp_tsp_annealing.h"

std::vector<uint32_t> scp::GraphAlgorithms::DepthFirstSearch(
    const scp::Graph &graph, uint32_t start_vertex) {
  if (graph.IsEmpty()) throw std::runtime_error("Graph is empty.");
  auto size = graph.GetSize();
  if (start_vertex > size || start_vertex <= 0) {
    throw std::out_of_range("Vertex doesn't exist.");
  }
  std::vector<bool> visited(size, false);
  scp::stack<uint32_t> stack;
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

std::vector<uint32_t> scp::GraphAlgorithms::BreadthFirstSearch(
    const scp::Graph &graph, uint32_t start_vertex) {
  if (graph.IsEmpty()) throw std::runtime_error("Graph is empty.");
  auto size = graph.GetSize();
  if (start_vertex > size || start_vertex <= 0) {
    throw std::out_of_range("Vertex doesn't exist.");
  }
  std::vector<bool> visited(size, false);
  scp::queue<uint32_t> queue;
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

std::vector<uint32_t> scp::GraphAlgorithms::GetLeastSpanningTree(
    const scp::Graph &graph) {
  if (graph.IsEmpty()) throw std::runtime_error("Graph is empty.");
  if (graph.IsDirected()) {
    throw std::runtime_error(
        "It's not possible to find a least spanning tree in a directed graph "
        "with Prim's algorithm.");
  }
  auto size = graph.GetSize();
  auto matrix = graph.GetGraph();

  std::vector<uint32_t> mst(size * size, 0);

  if (size == 1) {
    mst[0] = matrix[0];
    return mst;
  }

  std::vector<bool> visited(size, false);
  // The first vertex is a starting point
  visited[0] = true;

  // Keep track of the order of connecting vertices
  std::vector<uint32_t> vertices_order = {0};

  // Repeat until all the vertices are visited
  while (true) {
    // Find the minimum weight edge that connects a visited vertex to an
    // unvisited vertex
    uint32_t min_weight = std::numeric_limits<uint32_t>::max();
    uint32_t min_i = 0;
    uint32_t min_j = 0;

    for (auto i : vertices_order) {
      for (uint32_t j = 0; j < size; ++j) {
        if (!visited[j] && matrix[i * size + j] > 0 &&
            matrix[i * size + j] < min_weight) {
          min_weight = matrix[i * size + j];
          min_i = i;
          min_j = j;
        }
      }
    }

    // If no such edge exists, then the MST is complete
    if (min_weight == std::numeric_limits<uint32_t>::max()) {
      break;
    }

    // Add the edge to the MST matrix
    mst[min_i * size + min_j] = min_weight;
    mst[min_j * size + min_i] = min_weight;

    // Mark the vertex as visited and add it to the order
    visited[min_j] = true;
    vertices_order.push_back(min_j);
  }

  return mst;
}

scp::TsmResult scp::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
    const scp::Graph &graph, const double initial_temperature,
    const double cooling_rate, const unsigned seed) {
  TSPAnnealing tsp(graph, initial_temperature, cooling_rate, seed);
  return tsp.Solve();
}

scp::TsmResult
scp::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(
    const scp::Graph &graph, const unsigned seed) {
  TSPNearestNeighbor tsp(graph, seed);
  return tsp.Solve();
}

int scp::GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  if (graph.IsEmpty()) throw std::runtime_error("Graph is empty.");
  int size = graph.GetSize();
  if (vertex1 > size || vertex2 > size || vertex1 < 1 || vertex2 < 1) {
    throw std::out_of_range("Vertex doesn't exist.");
  }

  --vertex1;
  --vertex2;

  if (vertex1 == vertex2) {
    return graph.GetGraph()[vertex1 * size + vertex2];
  }

  int max_dist = INT32_MAX;
  std::vector<unsigned int> dist(size, max_dist);
  std::vector<bool> visited(size, false);
  dist[vertex1] = 0;

  while (true) {
    unsigned int minDist = max_dist;
    int j = -1;
    for (int i = 0; i < size; ++i) {
      if (!visited[i] && dist[i] < minDist) {
        minDist = dist[i];
        j = i;
      }
    }
    if (j == -1) {
      break;
    }
    visited[j] = true;
    for (int i = 0; i < size; ++i) {
      if (graph.GetGraph()[j * size + i] != 0 &&
          dist[j] + graph.GetGraph()[j * size + i] < dist[i]) {
        dist[i] = dist[j] + graph.GetGraph()[j * size + i];
      }
    }
  }

  for_each(dist.begin(), dist.end(), [max_dist](unsigned int &x) {
    if (x == static_cast<unsigned int>(max_dist)) x = 0;
  });
  return dist[vertex2];
}

scp::Graph::Matrix scp::GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    Graph &graph) {
  if (graph.IsEmpty()) throw std::runtime_error("Graph is empty.");
  int size = graph.GetSize();
  unsigned int max_dist = INT32_MAX;
  scp::Graph::Matrix dist(size * size, max_dist);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (graph.GetGraph()[i * size + j] == 0 && i != j) continue;
      dist[i * size + j] = graph.GetGraph()[i * size + j];
    }
  }

  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (dist[i * size + j] > dist[i * size + k] + dist[k * size + j]) {
          dist[i * size + j] = dist[i * size + k] + dist[k * size + j];
        }
      }
    }
  }

  for_each(dist.begin(), dist.end(), [max_dist](unsigned int &x) {
    if (x == static_cast<unsigned int>(max_dist)) x = 0;
  });
  return dist;
}

scp::TsmResult scp::GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph &graph) {
  scp::TSPAntColonyOptimization tsp(graph);
  return tsp.Solve();
}