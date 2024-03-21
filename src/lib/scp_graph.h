#ifndef SCP_A2_GRAPH_H_
#define SCP_A2_GRAPH_H_

#include <string>
#include <vector>

namespace scp {
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
  uint32_t GetSize() const;
  bool IsDirected() const;
  bool IsConnected() const;
  bool IsEmpty() const;

 private:
  // Variables
  Matrix graph_;
  uint32_t size_ = 0;
  bool directed_ = false, connected_ = true;

  // Methods
  void ClearGraph();
};
}  // namespace scp
#endif  // SCP_A2_GRAPH_H_