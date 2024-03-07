#ifndef S21_A2_CONTROLLER_H_
#define S21_A2_CONTROLLER_H_

#include "../lib/s21_graph.h"
#include "../lib/s21_graph_algorithms.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  ~Controller() = default;

  void LoadGraphFromFile(const std::string& filename);
  std::vector<uint32_t> DepthFirstSearch(uint32_t start_vertex);
  std::vector<uint32_t> BreadthFirstSearch(uint32_t start_vertex);
  int GetShortestPathBetweenVertices(int vertex1, int vertex2);
  void GetShortestPathsBetweenAllVertices();  // TODO: return value
  std::pair<std::vector<uint32_t>, uint32_t> GetLeastSpanningTree();
  TsmResult& SolveTravelingSalesmanProblem();

 private:
  Graph graph_;
};
}  // namespace s21
#endif  // S21_A2_CONTROLLER_H_
