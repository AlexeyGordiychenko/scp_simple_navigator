#include "scp_graph.h"

#include <fstream>
#include <sstream>

void scp::Graph::LoadGraphFromFile(const std::string& filename) {
  ClearGraph();

  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  std::string line;
  char temp = 0;
  int size = 0;
  if (std::getline(file, line)) {
    std::istringstream iss(line);
    if (!(iss >> size) || size < 0) {
      throw std::runtime_error("Failed to read the size of a graph.");
    } else if (iss >> temp) {
      throw std::runtime_error("Too many values for the size of a graph.");
    }
  } else {
    throw std::runtime_error("The file is empty.");
  }

  int rowscount = 0;
  while (rowscount < size && std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    int64_t value;
    for (auto i = 0; i < size; ++i) {
      if (iss >> value && value >= 0) {
        graph_.push_back(value);
        if (value == 0 && i != rowscount) connected_ = false;
      } else if (iss.eof() && value >= 0) {
        throw std::runtime_error("Not enough data for graph columns.");
      } else {
        throw std::runtime_error("Failed to read a value on matrix row " +
                                 std::to_string(rowscount + 1) + ".");
      }
      if (!directed_ && i < rowscount &&
          value != graph_[i * size + rowscount]) {
        directed_ = true;
      }
    }
    if (iss >> temp) {
      throw std::runtime_error("Too much data for matrix columns.");
    }
    rowscount++;
  }

  if (graph_.size() != size_t(size * size)) {
    throw std::runtime_error("Not enough data for the graph's matrix.");
  }

  while (std::getline(file, line)) {
    if (!line.empty())
      throw std::runtime_error("Too much data for the graph's matrix.");
  }

  size_ = size;
}

void scp::Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file for saving.");
  }

  file << (directed_ ? "digraph" : "graph") << " G {\n";
  auto sep = (directed_ ? " -> " : " -- ");
  u_int32_t i = 1, j = 1;
  for (auto value : graph_) {
    if (j == 1) file << '\t' << i;
    if (value > 0 && (directed_ || (!directed_ && i <= j))) file << sep << j;
    if (j >= size_) {
      ++i;
      j = 1;
      file << ";\n";
    } else {
      ++j;
    }
  }
  file << "}";
  file.close();
}

void scp::Graph::ClearGraph() {
  graph_.clear();
  size_ = 0;
  directed_ = false;
  connected_ = true;
}

const scp::Graph::Matrix& scp::Graph::GetGraph() const { return graph_; }
uint32_t scp::Graph::GetSize() const { return size_; }
bool scp::Graph::IsDirected() const { return directed_; }
bool scp::Graph::IsConnected() const { return connected_; }
bool scp::Graph::IsEmpty() const { return size_ == 0; }