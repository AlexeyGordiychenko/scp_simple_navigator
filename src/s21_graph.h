#ifndef S21_A2_GRAPH_H_
#define S21_A2_GRAPH_H_

#include <string>

namespace s21 {
class Graph {
 public:
  // Constructors and the Destructor
  Graph() = default;
  Graph(const Graph&) = delete;
  Graph& operator=(const Graph&) = delete;
  Graph(Graph&&) = delete;
  Graph& operator=(Graph&&) = delete;
  ~Graph() = default;

  // Methods
  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
};
}  // namespace s21
#endif  // S21_A2_GRAPH_H_