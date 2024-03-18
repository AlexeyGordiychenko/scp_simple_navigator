#include "s21_graph_algorithms_tests.h"

TEST(DepthFirstSearchTestCase, 0) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_1.txt");
  std::vector<uint32_t> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 1), result);
}

TEST(DepthFirstSearchTestCase, 1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_1.txt");
  std::vector<uint32_t> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 1), result);
}

TEST(DepthFirstSearchTestCase, 2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  std::vector<uint32_t> result{1,  2, 6,  5,  4,  3,  11, 9,
                               10, 8, 14, 15, 13, 12, 7};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 1), result);
}

TEST(DepthFirstSearchTestCase, 3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  std::vector<uint32_t> result{18, 17, 16, 2,  1,  5, 4,  3,  11,
                               9,  10, 8,  14, 15, 6, 13, 12, 7};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 18), result);
}

TEST(DepthFirstSearchTestCase, 4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  std::vector<uint32_t> result{10, 8, 1,  2,  6,  5,  4, 3,
                               11, 9, 14, 15, 13, 12, 7};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 10), result);
}

TEST(DepthFirstSearchTestCase, 5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  std::vector<uint32_t> result{4, 3, 11, 9,  10, 8,  1, 2,
                               6, 5, 14, 15, 7,  12, 13};
  EXPECT_EQ(s21::GraphAlgorithms::DepthFirstSearch(graph, 4), result);
}

TEST(DepthFirstSearchTestCase, 6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, 20),
               std::out_of_range);
}

TEST(DepthFirstSearchTestCase, 7) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, 0),
               std::out_of_range);
}

TEST(DepthFirstSearchTestCase, 8) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, -1),
               std::out_of_range);
}

TEST(BreadthFirstSearchTestCase, 0) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_1.txt");
  std::vector<uint32_t> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 1), result);
}

TEST(BreadthFirstSearchTestCase, 1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_1.txt");
  std::vector<uint32_t> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 1), result);
}

TEST(BreadthFirstSearchTestCase, 2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  std::vector<uint32_t> result{1,  2,  5,  7,  8,  6, 13, 4,
                               14, 12, 10, 15, 11, 3, 9};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 1), result);
}

TEST(BreadthFirstSearchTestCase, 3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  std::vector<uint32_t> result{17, 16, 2,  6,  1,  7, 13, 5, 15,
                               8,  4,  12, 11, 14, 9, 10, 3};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 17), result);
}

TEST(BreadthFirstSearchTestCase, 4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  std::vector<uint32_t> result{1,  2,  5,  7,  8,  6, 13, 4,
                               14, 12, 10, 15, 11, 3, 9};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 1), result);
}

TEST(BreadthFirstSearchTestCase, 5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  std::vector<uint32_t> result{7,  1, 2, 4,  12, 5,  8, 6,
                               13, 3, 9, 14, 10, 15, 11};
  EXPECT_EQ(s21::GraphAlgorithms::BreadthFirstSearch(graph, 7), result);
}

TEST(BreadthFirstSearchTestCase, 6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, 21),
               std::out_of_range);
}

TEST(BreadthFirstSearchTestCase, 7) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, 0),
               std::out_of_range);
}

TEST(BreadthFirstSearchTestCase, 8) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_undirected_3.txt");
  EXPECT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, -1),
               std::out_of_range);
}

TEST(LeastSpanningTree, 0) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/spanning_tree_1.txt");
  std::vector<uint32_t> result{0, 4, 0, 0, 2, 0, 0, 0, 4, 0, 0, 5, 0, 0, 3, 0,
                               0, 0, 0, 0, 0, 4, 1, 0, 0, 5, 0, 0, 0, 0, 0, 0,
                               2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4,
                               0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0};
  EXPECT_EQ(s21::GraphAlgorithms::GetLeastSpanningTree(graph), result);
}

TEST(LeastSpanningTree, 1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/spanning_tree_2.txt");
  std::vector<uint32_t> result{
      0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 3, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0,
      0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0,
      0, 0, 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
  };
  EXPECT_EQ(s21::GraphAlgorithms::GetLeastSpanningTree(graph), result);
}

TEST(LeastSpanningTree, 2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/spanning_tree_3.txt");
  std::vector<uint32_t> result{
      0, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
      0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
      0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 4, 2,
      0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 5, 0};
  EXPECT_EQ(s21::GraphAlgorithms::GetLeastSpanningTree(graph), result);
}

TEST(LeastSpanningTree, 3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_2.txt");
  EXPECT_THAT([&]() { s21::GraphAlgorithms::GetLeastSpanningTree(graph); },
              testing::ThrowsMessage<std::runtime_error>(
                  testing::HasSubstr("It's not possible to find")));
}

TEST(LeastSpanningTree, 4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/spanning_tree_4.txt");
  std::vector<uint32_t> result = {0};
  EXPECT_EQ(s21::GraphAlgorithms::GetLeastSpanningTree(graph), result);
}

TEST(TheSalesmanProblem, 0) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_2.txt");
  s21::TsmResult result = {{10, 6, 4, 5, 3, 8, 1, 9, 11, 2, 7}, 173.0};
  auto solution = s21::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
      graph, 1000, 0.9, 42);
  EXPECT_EQ(solution.vertices, result.vertices);
  EXPECT_DOUBLE_EQ(solution.distance, result.distance);
}

TEST(TheSalesmanProblem, 1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_2.txt");
  s21::TsmResult result = {{5, 4, 6, 10, 8, 3, 11, 2, 1, 9, 7}, 306.0};
  s21::TsmResult solution =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(graph,
                                                                         69);
  std::cout << "SOLUTIONS DISTANCE: " << solution.distance << std::endl;
  EXPECT_EQ(solution.vertices, result.vertices);
  EXPECT_DOUBLE_EQ(solution.distance, result.distance);
}

TEST(TheSalesmanProblem, 3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_3.txt");
  EXPECT_THAT(
      [&]() {
        s21::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
            graph, 1000, 0.9, 42);
      },
      testing::ThrowsMessage<std::runtime_error>(
          testing::HasSubstr("Graph is not connected.")));
}

TEST(TheSalesmanProblem, 4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_3.txt");
  EXPECT_THAT(
      [&]() {
        s21::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(
            graph, 42);
      },
      testing::ThrowsMessage<std::runtime_error>(
          testing::HasSubstr("Graph is not connected.")));
}

TEST(TheSalesmanProblem, 5) {
  s21::Graph graph;
  EXPECT_THAT(
      [&]() {
        s21::GraphAlgorithms::SolveTravelingSalesmanProblemAnnealing(
            graph, 1000, 0.9, 42);
      },
      testing::ThrowsMessage<std::runtime_error>(
          testing::HasSubstr("Graph is empty.")));
}

TEST(TheSalesmanProblem, 6) {
  s21::Graph graph;
  EXPECT_THAT(
      [&]() {
        s21::GraphAlgorithms::SolveTravelingSalesmanProblemNearestNeighbor(
            graph, 42);
      },
      testing::ThrowsMessage<std::runtime_error>(
          testing::HasSubstr("Graph is empty.")));
}
