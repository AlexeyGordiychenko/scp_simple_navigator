#include <limits>

#include "../lib/s21_graph.h"
#include "../lib/s21_graph_algorithms.h"
#include "s21_navigator_tests.h"

TEST(aco_algorithm_test, tsp_graph_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_1.txt");
  s21::GraphAlgorithms algorithms;
  s21::TsmResult& result = algorithms.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 52);
  delete &result;
}

TEST(aco_algorithm_test, tsp_graph_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/tsp_graph_2.txt");
  s21::GraphAlgorithms algorithms;
  s21::TsmResult& result = algorithms.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 253);
  delete &result;
}