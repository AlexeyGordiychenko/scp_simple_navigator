#include "controller/s21_controller.h"
#include "view/s21_console_menu.h"

int main() {
  s21::Controller controller;
  bool running = true;
  s21::ConsoleMenu menu(
      "Choose an option:\n", "Invalid input\n", "> ",
      {{"Load graph from a file",
        [&menu, &controller] {
          menu.CallMenuFunction(static_cast<std::function<void(std::string)>>(
                                    [&menu, &controller](std::string filename) {
                                      menu.SetCurrentFile("");
                                      controller.LoadGraphFromFile(filename);
                                      menu.SetCurrentFile(filename);
                                    }),
                                std::make_tuple("Enter the file path: "));
        }},
       {"Bread first traversal",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void(uint32_t)>>(
                  [&menu, &controller](uint32_t a) {
                    menu.PrintVector(controller.BreadthFirstSearch(a),
                                     "Bread first traversal, starting from " +
                                         std::to_string(a) + ":\n");
                  }),
              std::make_tuple("Enter the start vertex: "));
        }},
       {"Depth first traversal",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void(uint32_t)>>(
                  [&menu, &controller](uint32_t a) {
                    menu.PrintVector(controller.DepthFirstSearch(a),
                                     "Depth first traversal, starting from " +
                                         std::to_string(a) + ":\n");
                  }),
              std::make_tuple("Enter the start vertex: "));
        }},
       // {"The shortest path between any two vertices",
       //  [&menu, &controller] {
       //    menu.CallMenuFunction(
       //        static_cast<std::function<void(uint32_t, uint32_t)>>(
       //            [&controller](uint32_t a, uint32_t b) {
       //              controller.GetShortestPathBetweenVertices(a, b);
       //            }),
       //        std::make_tuple("Enter the first vertex: ",
       //                        "Enter the second vertex: "));
       //  }},
       // {"The shortest paths between all pairs of vertices",
       //  [&controller] { controller.GetShortestPathsBetweenAllVertices(); }},
       {"Minimal spanning tree",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void()>>([&menu, &controller]() {
                menu.PrintMatrix(controller.GetLeastSpanningTree(),
                                 "Minimal spanning tree:\n");
              }),
              std::make_tuple());
        }},
       //  {"The salesman problem",
       //   [&controller] { controller.SolveTravelingSalesmanProblem(); }},
       {"The salesman problem (annealing)",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void()>>([&menu, &controller]() {
                auto result =
                    controller.SolveTravelingSalesmanProblemAnnealing();
                menu.PrintVector(
                    result.vertices,
                    "TSM result (annealing) with distance " +
                        std::to_string(static_cast<uint32_t>(result.distance)) +
                        ":\n");
              }),
              std::make_tuple());
        }},
       {"The salesman problem (nearest neighbor)",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void()>>([&menu, &controller]() {
                auto result =
                    controller.SolveTravelingSalesmanProblemNearestNeighbor();
                menu.PrintVector(
                    result.vertices,
                    "TSM result (nearest neighbor) with distance " +
                        std::to_string(static_cast<uint32_t>(result.distance)) +
                        ":\n");
              }),
              std::make_tuple());
        }},
       {"Compare TSP algorithms",
        [&menu, &controller] {
          menu.CallMenuFunction(
              static_cast<std::function<void(uint32_t)>>([&menu, &controller](
                                                             uint32_t n) {
                menu.MeasureFunctionsTime(
                    n,
                    std::make_pair(
                        std::bind(&s21::Controller::
                                      SolveTravelingSalesmanProblemAnnealing,
                                  &controller),
                        std::string("annealing algorithm")),
                    std::make_pair(
                        std::bind(
                            &s21::Controller::
                                SolveTravelingSalesmanProblemNearestNeighbor,
                            &controller),
                        std::string("nearest neighbor algorithm")));
              }),
              std::make_tuple("Enter the number of executions: "));
        }},
       {"Exit", [&running] { running = false; }}});
  while (running) {
    menu();
  }
  return 0;
}