#include <limits>

#include "../lib/s21_graph.h"
#include "../lib/s21_graph_algorithms.h"
#include "s21_navigator_tests.h"

TEST(dijkstras_algorithm_test, simple_graph) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/simple_graph.txt");
  s21::GraphAlgorithms algorithms;
  int dist;
  dist = algorithms.GetShortestPathBetweenVertices(graph, 0, 1);
  EXPECT_EQ(dist, 3);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 1, 2);
  EXPECT_EQ(dist, 1);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 2, 3);
  EXPECT_EQ(dist, 5);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 0, 3);
  EXPECT_EQ(dist, 9);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 0, 2);
  EXPECT_EQ(dist, 4);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 1, 3);
  EXPECT_EQ(dist, 6);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 0, 0);
  EXPECT_EQ(dist, 0);
}

TEST(dijkstras_algorithm_test, graph_directed_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  s21::GraphAlgorithms algorithms;
  int dist;
  dist = algorithms.GetShortestPathBetweenVertices(graph, 17, 1);
  EXPECT_EQ(dist, 7);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 1, 17);
  EXPECT_EQ(dist, INT32_MAX);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 17, 7);
  EXPECT_EQ(dist, 9);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 7, 17);
  EXPECT_EQ(dist, INT32_MAX);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 12, 10);
  EXPECT_EQ(dist, 9);
  dist = algorithms.GetShortestPathBetweenVertices(graph, 10, 12);
  EXPECT_EQ(dist, 9);
}

TEST(floyd_warshall_algorithm_test, graph_directed_3) {
  unsigned int max = INT32_MAX;
  std::vector<unsigned int> expected = {
      0, 1, 3,  2, 3, 4, 1, 1, 7,  8,  4,  2, 6,  6,  5,  max, max, max,
      1, 0, 3,  2, 3, 4, 1, 2, 7,  8,  4,  2, 5,  6,  5,  max, max, max,
      3, 3, 0,  1, 2, 3, 2, 4, 6,  7,  1,  1, 8,  5,  4,  max, max, max,
      2, 2, 1,  0, 1, 2, 1, 3, 5,  6,  2,  2, 7,  4,  3,  max, max, max,
      3, 3, 2,  1, 0, 1, 2, 4, 4,  5,  3,  3, 8,  3,  2,  max, max, max,
      4, 4, 3,  2, 1, 0, 3, 5, 4,  5,  4,  4, 9,  4,  1,  max, max, max,
      1, 1, 2,  1, 2, 3, 0, 2, 6,  7,  3,  1, 6,  5,  4,  max, max, max,
      1, 2, 4,  3, 4, 5, 2, 0, 8,  7,  5,  3, 7,  7,  6,  max, max, max,
      7, 7, 6,  5, 4, 4, 6, 8, 0,  1,  7,  7, 12, 1,  3,  max, max, max,
      8, 8, 7,  6, 5, 5, 7, 7, 1,  0,  8,  8, 13, 2,  4,  max, max, max,
      4, 4, 1,  2, 3, 4, 3, 5, 7,  8,  0,  2, 9,  6,  5,  max, max, max,
      2, 2, 1,  2, 3, 4, 1, 3, 7,  8,  2,  0, 7,  6,  5,  max, max, max,
      6, 5, 8,  7, 8, 9, 6, 7, 12, 13, 9,  7, 0,  11, 10, max, max, max,
      6, 6, 5,  4, 3, 4, 5, 7, 1,  2,  6,  6, 11, 0,  4,  max, max, max,
      5, 5, 4,  3, 2, 1, 4, 6, 3,  4,  5,  5, 10, 4,  0,  max, max, max,
      2, 1, 4,  3, 2, 1, 2, 3, 5,  6,  5,  3, 6,  5,  2,  0,   max, max,
      7, 6, 9,  8, 7, 6, 7, 8, 10, 11, 10, 8, 11, 10, 7,  5,   0,   max,
      8, 7, 10, 9, 8, 7, 8, 9, 11, 12, 11, 9, 12, 11, 8,  6,   1,   0};
  s21::Graph graph;
  graph.LoadGraphFromFile("tests/files/graph_directed_3.txt");
  s21::GraphAlgorithms algorithms;
  auto dist = algorithms.GetShortestPathsBetweenAllVertices(graph);
  for (unsigned int i = 0; i < graph.GetSize(); i++) {
    for (unsigned int j = 0; j < graph.GetSize(); j++) {
      EXPECT_EQ(dist[i * graph.GetSize() + j],
                expected[i * graph.GetSize() + j]);
    }
  }
}