#ifndef S21_A2_GRAPH_TESTS_H
#define S21_A2_GRAPH_TESTS_H

#include <fstream>

#include "../lib/s21_graph.h"
#include "s21_navigator_tests.h"

class LoadGraphErrorsTestCase : public ::testing::Test {
 protected:
  void CheckThrowAndMessage(const std::string& file,
                            const std::string& message) {
    s21::Graph graph;
    EXPECT_THAT(
        [&]() { graph.LoadGraphFromFile("tests/files/" + file + ".txt"); },
        testing::ThrowsMessage<std::runtime_error>(
            testing::HasSubstr(message)));
  }
};

class ExportGraphTestCase : public ::testing::Test {
 protected:
  bool CompareDotFiles(const std::string& file1, const std::string& file2) {
    std::ifstream f1("tests/files/" + file1 + ".dot", std::ios::binary);
    std::ifstream f2("tests/files/" + file2 + ".dot", std::ios::binary);

    if (!f1.is_open() || !f2.is_open()) return false;

    auto pair = std::mismatch(std::istreambuf_iterator<char>(f1),
                              std::istreambuf_iterator<char>(),
                              std::istreambuf_iterator<char>(f2));

    return pair.first == std::istreambuf_iterator<char>() &&
           pair.second == std::istreambuf_iterator<char>();
  }
};

#endif  // S21_A2_GRAPH_TESTS_H
