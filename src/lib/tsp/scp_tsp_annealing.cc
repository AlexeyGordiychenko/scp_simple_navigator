#include "scp_tsp_annealing.h"

#include <algorithm>
#include <stdexcept>

scp::TsmResult scp::TSPAnnealing::Solve() {
  if (graph_.GetSize() <= 0) throw std::runtime_error("Graph is empty.");
  if (!graph_.IsConnected())
    throw std::runtime_error("Graph is not connected.");

  auto result = GenerateRandomResult();

  while (temperature_ > 0.00001) {
    // Generate a random path
    auto new_result = SwapVertices(result);

    bool accept = new_result.distance < result.distance;
    if (!accept) {
      // Calculate the acceptance probability
      auto ap =
          std::exp((result.distance - new_result.distance) / temperature_);
      std::uniform_real_distribution<> dis(0.0, 1.0);
      accept = ap > dis(generator_);
    }
    // Accept or reject the new path
    if (accept) result = new_result;

    // Update the temperature
    temperature_ *= cooling_rate_;
  }
  // Return to the starting point
  result.vertices.push_back(result.vertices.front());
  return result;
}

scp::TsmResult scp::TSPAnnealing::GenerateRandomResult() {
  TsmResult result = {std::vector<uint32_t>(graph_.GetSize()), 0.0};
  std::iota(result.vertices.begin(), result.vertices.end(), 1);
  std::shuffle(result.vertices.begin(), result.vertices.end(), generator_);
  CalculateCost(result);
  return result;
}

scp::TsmResult scp::TSPAnnealing::SwapVertices(const scp::TsmResult& result) {
  auto new_result = result;
  std::uniform_int_distribution<> dis(0, graph_.GetSize() - 1);
  std::swap(new_result.vertices[dis(generator_)],
            new_result.vertices[dis(generator_)]);
  CalculateCost(new_result);
  return new_result;
}

void scp::TSPAnnealing::CalculateCost(scp::TsmResult& result) {
  auto size = graph_.GetSize();
  auto matrix = graph_.GetGraph();
  result.distance = 0;
  for (size_t i = 0; i < result.vertices.size() - 1; ++i) {
    result.distance +=
        matrix[(result.vertices[i] - 1) * size + (result.vertices[i + 1] - 1)];
  }
  // Add the distance of returning to the starting vertex
  result.distance += matrix[(result.vertices.back() - 1) * size +
                            (result.vertices.front() - 1)];
}
