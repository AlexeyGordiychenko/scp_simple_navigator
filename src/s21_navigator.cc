#include "controller/s21_controller.h"
#include "view/s21_console_menu.h"

int main() {
  s21::Controller controller;
  bool running = true;
  s21::ConsoleMenu menu(
      "Choose an option:\n", "Invalid input\n", "> ",
      {{"Load graph from a file",
        [&menu, &controller] {
          menu.FunctionWithArgs(static_cast<std::function<void(std::string)>>(
                                    [&controller](std::string filename) {
                                      controller.LoadGraphFromFile(filename);
                                    }),
                                std::make_tuple("Enter the file path: "));
        }},
       {"Bread first traversal",
        [&menu, &controller] {
          menu.FunctionWithArgs(
              static_cast<std::function<void(uint32_t)>>(
                  [&menu, &controller](uint32_t a) {
                    menu.PrintVector(controller.BreadthFirstSearch(a));
                  }),
              std::make_tuple("Enter the start vertex: "));
        }},
       {"Depth first traversal",
        [&menu, &controller] {
          menu.FunctionWithArgs(
              static_cast<std::function<void(uint32_t)>>(
                  [&menu, &controller](uint32_t a) {
                    menu.PrintVector(controller.DepthFirstSearch(a));
                  }),
              std::make_tuple("Enter the start vertex: "));
        }},
       //  {"The shortest path between any two vertices",
       //   [&menu, &controller] {
       //     menu.FunctionWithArgs(
       //         static_cast<std::function<void(uint32_t, uint32_t)>>(
       //             [&controller](uint32_t a, uint32_t b) {
       //               controller.GetShortestPathBetweenVertices(a, b);
       //             }),
       //         std::make_tuple("Enter the first vertex: ",
       //                         "Enter the second vertex: "));
       //   }},
       //  {"The shortest paths between all pairs of vertices",
       //   [&controller] { controller.GetShortestPathsBetweenAllVertices(); }},
       {"Minimal spanning tree",
        [&menu, &controller] {
          menu.FunctionWithArgs(
              static_cast<std::function<void()>>([&menu, &controller]() {
                menu.PrintMatrix(controller.GetLeastSpanningTree());
              }),
              std::make_tuple());
        }},
       //  {"The salesman problem",
       //   [&controller] { controller.SolveTravelingSalesmanProblem(); }},
       {"Exit", [&running] { running = false; }}});
  while (running) {
    menu();
  }
  return 0;
}