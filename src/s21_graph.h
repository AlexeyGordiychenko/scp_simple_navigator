#ifndef S21_A2_GRAPH_H_
#define S21_A2_GRAPH_H_

#include <string>
#include <vector>

namespace s21 {
class Graph {
 public:
  using Matrix = std::vector<uint32_t>;

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
  bool IsDirected() const;

 private:
  // Variables
  Matrix graph_;
  uint32_t size_;
  bool directed_;

  // Methods
  void ClearGraph();
};
}  // namespace s21
#endif  // S21_A2_GRAPH_H_