#include "controller/s21_controller.h"
#include "view/s21_console_menu.h"

int main() {
  s21::Controller controller;
  bool running = true;
  s21::ConsoleMenu menu(
      "Choose an option:\n", "Invalid input; ", "> ",
      {{"Load graph from a file",
        [&menu, &controller] {
          menu.FunctionWithString([&controller](std::string& filename) {
            controller.LoadGraphFromFile(filename);
          });
        }},
       {"Bread first traversal",
        [&menu, &controller] {
          menu.PrintVector(controller.BreadthFirstSearch(1));
        }},
       {"Depth first traversal",
        [&menu, &controller] {
          menu.PrintVector(controller.DepthFirstSearch(1));
        }},
       //  {"The shortest path between any two vertices",
       //   [&menu, &controller] {
       //     menu.FunctionWithTwoUints([&controller](uint32_t a, uint32_t b) {
       //       controller.GetShortestPathBetweenVertices(a, b);
       //     });
       //   }},
       //  {"The shortest paths between all pairs of vertices",
       //   [&controller] { controller.GetShortestPathsBetweenAllVertices(); }},
       {"Minimal spanning tree",
        [&controller] { controller.GetLeastSpanningTree(); }},
       //  {"The salesman problem",
       //   [&controller] { controller.SolveTravelingSalesmanProblem(); }},
       {"Exit", [&running] { running = false; }}});
  while (running) {
    menu();
  }
  return 0;
}