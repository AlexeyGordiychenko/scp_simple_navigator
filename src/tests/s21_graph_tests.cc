#include "s21_graph_tests.h"

TEST_F(LoadGraphErrorsTestCase, 0) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_size_negative",
                       "Failed to read the size of a graph");
}

TEST_F(LoadGraphErrorsTestCase, 1) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_size_extra_value",
                       "Too many values for the size of a graph.");
}

TEST_F(LoadGraphErrorsTestCase, 2) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_size_alpha",
                       "Failed to read the size of a graph");
}

TEST_F(LoadGraphErrorsTestCase, 3) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_size_float",
                       "Too many values for the size of a graph.");
}

TEST_F(LoadGraphErrorsTestCase, 4) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_value_negative",
                       "Failed to read a value on matrix row");
}

TEST_F(LoadGraphErrorsTestCase, 5) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_value_extra",
                       "Too much data for matrix columns");
}

TEST_F(LoadGraphErrorsTestCase, 6) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_value_insufficient",
                       "Not enough data for graph columns.");
}

TEST_F(LoadGraphErrorsTestCase, 7) {
  s21::Graph graph;
  CheckThrowAndMessage("inc_graph_value_alpha",
                       "Failed to read a value on matrix row");
}

TEST_F(LoadGraphErrorsTestCase, 8) {
  CheckThrowAndMessage("inc_graph_value_float",
                       "Failed to read a value on matrix row");
}

TEST_F(LoadGraphErrorsTestCase, 9) {
  CheckThrowAndMessage("missing_file", "Can't open the file.");
}

TEST_F(LoadGraphErrorsTestCase, 10) {
  CheckThrowAndMessage("inc_graph_empty", "The file is empty.");
}

TEST_F(LoadGraphErrorsTestCase, 11) {
  CheckThrowAndMessage("inc_graph_rows_insufficient",
                       "Not enough data for the graph's matrix.");
}

TEST_F(LoadGraphErrorsTestCase, 12) {
  CheckThrowAndMessage("inc_graph_rows_extra",
                       "Too much data for the graph's matrix.");
}

TEST(LoadGraphTestCase, 1) {
  s21::Graph graph;
  std::vector<uint32_t> result = {
      0,  29, 20,  21, 16, 31, 100, 12, 4,  31, 18,  29, 0,  15, 29,  28,
      40, 72, 21,  29, 41, 12, 20,  15, 0,  15, 14,  25, 81, 9,  23,  27,
      13, 21, 29,  15, 0,  4,  12,  92, 12, 25, 13,  25, 16, 28, 14,  4,
      0,  16, 94,  9,  20, 16, 22,  31, 40, 25, 12,  16, 0,  95, 24,  36,
      3,  37, 100, 72, 81, 92, 94,  95, 0,  90, 101, 99, 84, 12, 21,  9,
      12, 9,  24,  90, 0,  15, 25,  13, 4,  29, 23,  25, 20, 36, 101, 15,
      0,  35, 18,  31, 41, 27, 13,  16, 3,  99, 25,  35, 0,  38, 18,  12,
      13, 25, 22,  37, 84, 13, 18,  38, 0,
  };
  graph.LoadGraphFromFile("tests/files/graph_undirected_1.txt");
  EXPECT_EQ(graph.GetSize(), 11);
  EXPECT_EQ(graph.IsDirected(), false);
  EXPECT_EQ(graph.GetGraph(), result);
}

TEST(LoadGraphTestCase, 2) {
  s21::Graph graph;
  std::vector<uint32_t> result = {
      0,  29, 20,  21, 16, 31, 100, 12, 4,  31, 18,  29, 0,  15, 29,  28,
      40, 72, 21,  29, 41, 12, 20,  15, 0,  15, 14,  25, 81, 9,  23,  27,
      13, 21, 29,  15, 0,  4,  12,  92, 12, 25, 13,  25, 16, 28, 14,  4,
      0,  16, 94,  9,  20, 16, 22,  31, 40, 25, 12,  16, 0,  95, 24,  36,
      3,  37, 100, 72, 81, 92, 94,  95, 0,  90, 101, 99, 84, 12, 21,  9,
      12, 8,  24,  90, 0,  15, 25,  13, 4,  29, 23,  25, 20, 36, 101, 15,
      0,  35, 18,  31, 41, 27, 13,  16, 3,  99, 25,  35, 0,  38, 18,  12,
      13, 25, 22,  37, 84, 13, 18,  38, 0,
  };
  graph.LoadGraphFromFile("tests/files/graph_directed_1.txt");
  EXPECT_EQ(graph.GetSize(), 11);
  EXPECT_EQ(graph.IsDirected(), true);
  EXPECT_EQ(graph.GetGraph(), result);
}

TEST(LoadGraphTestCase, 3) {
  s21::Graph graph;
  std::vector<uint32_t> result = {0, 1, 0, 1, 0, 0, 1, 1,
                                  1, 0, 0, 0, 1, 0, 0, 0};
  graph.LoadGraphFromFile("tests/files/graph_directed_2.txt");
  EXPECT_EQ(graph.GetSize(), 4);
  EXPECT_EQ(graph.IsDirected(), true);
  EXPECT_EQ(graph.GetGraph(), result);
}

TEST(LoadGraphTestCase, 4) {
  s21::Graph graph;
  std::vector<uint32_t> result = {
      0, 10, 20, 30, 10, 0, 60, 40, 20, 60, 0, 50, 30, 40, 50, 0,
  };
  graph.LoadGraphFromFile("tests/files/graph_undirected_2.txt");
  EXPECT_EQ(graph.GetSize(), 4);
  EXPECT_EQ(graph.IsDirected(), false);
  EXPECT_EQ(graph.GetGraph(), result);
}

TEST(LoadGraphTestCase, 5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_1.txt");
  graph.LoadGraphFromFile("tests/files/graph_undirected_2.txt");
  std::vector<uint32_t> result = {
      0, 10, 20, 30, 10, 0, 60, 40, 20, 60, 0, 50, 30, 40, 50, 0,
  };
  EXPECT_EQ(graph.GetSize(), 4);
  EXPECT_EQ(graph.IsDirected(), false);
  EXPECT_EQ(graph.GetGraph(), result);
}

TEST_F(ExportGraphTestCase, 0) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_1.txt");
  graph.ExportGraphToDot("tests/files/graph_directed_1_test.dot");
  EXPECT_TRUE(CompareDotFiles("graph_directed_1", "graph_directed_1_test"));
}

TEST_F(ExportGraphTestCase, 1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_2.txt");
  graph.ExportGraphToDot("tests/files/graph_directed_2_test.dot");
  EXPECT_TRUE(CompareDotFiles("graph_directed_2", "graph_directed_2_test"));
}

TEST_F(ExportGraphTestCase, 2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_1.txt");
  graph.ExportGraphToDot("tests/files/graph_undirected_1_test.dot");
  EXPECT_TRUE(CompareDotFiles("graph_undirected_1", "graph_undirected_1_test"));
}

TEST_F(ExportGraphTestCase, 3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_2.txt");
  graph.ExportGraphToDot("tests/files/graph_undirected_2_test.dot");
  EXPECT_TRUE(CompareDotFiles("graph_undirected_2", "graph_undirected_2_test"));
}

TEST_F(ExportGraphTestCase, 4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_1.txt");
  EXPECT_THROW(
      graph.ExportGraphToDot("tests1/files/graph_undirected_1_test.dot"),
      std::runtime_error);
}