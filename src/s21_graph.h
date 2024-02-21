#ifndef S21_A2_GRAPH_H_
#define S21_A2_GRAPH_H_

#include <string>
#include <vector>

namespace s21 {
class Graph {
 public:
  using Matrix = std::vector<int>;

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

  const Matrix& GetGraph() const;
  int GetSize() const;

 private:
  // Variables
  Matrix graph_;
  int size_;

  // Methods
  void ClearGraph();
};
}  // namespace s21
#endif  // S21_A2_GRAPH_H_