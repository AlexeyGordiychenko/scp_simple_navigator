#include "scp_controller.h"

void scp::Controller::LoadGraphFromFile(const std::string& filename) {
  graph_.LoadGraphFromFile(filename);
}

std::vector<uint32_t> scp::Controller::DepthFirstSearch(uint32_t start_vertex) {
  return scp::GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);
}

std::vector<uint32_t> scp::Controller::BreadthFirstSearch(
    uint32_t start_vertex) {
  return scp::GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);
}

int scp::Controller::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  return scp::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, vertex1,
                                                              vertex2);
}

std::pair<std::vector<uint32_t>, uint32_t>
scp::Controller::GetShortestPathsBetweenAllVertices() {
  return std::pair<std::vector<uint32_t>, uint32_t>(
      scp::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_),
      graph_.GetSize());
}

std::pair<std::vector<uint32_t>, uint32_t>
scp::Controller::GetLeastSpanningTree() {
  return std::pair<std::vector<uint32_t>, uint32_t>(
      scp::GraphAlgorithms::GetLeastSpanningTree(graph_), graph_.GetSize());
}

scp::TsmResult scp::Controller::SolveTravelingSalesmanProblem() {
  return scp::GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
}

scp::TsmResult scp::Controller::SolveTravelingSalesmanProblemAnnealing() {
  return scp::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
      graph_, 1000, 0.9);
}

scp::TsmResult scp::Controller::SolveTravelingSalesmanProblemNearestNeighbor() {
  return scp::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(
      graph_);
}
