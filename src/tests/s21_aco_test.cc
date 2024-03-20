#include <limits>

#include "s21_graph_algorithms_tests.h"

TEST(aco_algorithm_test, tsp_graph_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_1.txt");
  s21::GraphAlgorithms algorithms;
  s21::TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 52);
}

TEST(aco_algorithm_test, tsp_graph_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_2.txt");
  s21::GraphAlgorithms algorithms;
  s21::TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 253);
}

TEST(aco_algorithm_test, single_node_graph) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_single_node.txt");
  s21::GraphAlgorithms algorithms;
  s21::TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 5);
}

TEST(aco_algorithm_test, not_connected_graph) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  s21::GraphAlgorithms algorithms;
  EXPECT_THROW(algorithms.SolveTravelingSalesmanProblem(graph);
               , std::runtime_error);
}

TEST(aco_algorithm_test, empty_graph) {
  s21::Graph graph;
  EXPECT_THROW(graph.LoadGraphFromFile("tests/files/inc_graph_empty.txt"),
               std::runtime_error);
  s21::GraphAlgorithms algorithms;
  EXPECT_THROW(algorithms.SolveTravelingSalesmanProblem(graph);
               , std::runtime_error);
}