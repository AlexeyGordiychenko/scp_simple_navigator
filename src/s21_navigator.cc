#include "controller/s21_controller.h"
#include "view/s21_console_menu.h"

void Load(s21::ConsoleMenu& menu, s21::Controller& controller) {
  menu.CallMenuFunction(static_cast<std::function<void(std::string)>>(
                            [&menu, &controller](std::string filename) {
                              menu.SetCurrentFile("");
                              controller.LoadGraphFromFile(filename);
                              menu.SetCurrentFile(filename);
                            }),
                        std::make_tuple("Enter the file path: "));
}

void Traversal(s21::ConsoleMenu& menu,
               std::function<std::vector<uint32_t>(uint32_t)> traversal_func,
               const std::string& traversal_type) {
  menu.CallMenuFunction(
      static_cast<std::function<void(uint32_t)>>([&menu, traversal_func,
                                                  traversal_type](uint32_t a) {
        menu.PrintVector(traversal_func(a),
                         traversal_type + "first traversal, starting from " +
                             std::to_string(a) + ":\n");
      }),
      std::make_tuple("Enter the start vertex: "));
}

void TheShortestPath(s21::ConsoleMenu& menu, s21::Controller& controller) {
  menu.CallMenuFunction(
      static_cast<std::function<void(uint32_t, uint32_t)>>(
          [&menu, &controller](uint32_t a, uint32_t b) {
            menu.PrintValue(controller.GetShortestPathBetweenVertices(a, b),
                            "The shortest path is: ");
          }),
      std::make_tuple("Enter the first vertex: ", "Enter the second vertex: "));
}

void TheShortestPathAll(s21::ConsoleMenu& menu, s21::Controller& controller) {
  menu.CallMenuFunction(
      static_cast<std::function<void()>>([&menu, &controller]() {
        menu.PrintMatrix(controller.GetShortestPathsBetweenAllVertices(),
                         "The shortest path between all pairs of vertices:\n");
      }),
      std::make_tuple());
}

void MinimalSpanningTree(s21::ConsoleMenu& menu, s21::Controller& controller) {
  menu.CallMenuFunction(
      static_cast<std::function<void()>>([&menu, &controller]() {
        menu.PrintMatrix(controller.GetLeastSpanningTree(),
                         "Minimal spanning tree:\n");
      }),
      std::make_tuple());
}

void TSP(s21::ConsoleMenu& menu, std::function<s21::TsmResult()> tsp_func,
         const std::string& tsp_type) {
  menu.CallMenuFunction(
      static_cast<std::function<void()>>([&menu, tsp_func, tsp_type]() {
        auto result = tsp_func();
        menu.PrintVector(
            result.vertices,
            "TSM result (" + tsp_type + ") with distance " +
                std::to_string(static_cast<uint32_t>(result.distance)) + ":\n");
      }),
      std::make_tuple());
}

void TSPCompare(s21::ConsoleMenu& menu, s21::Controller& controller) {
  menu.CallMenuFunction(
      static_cast<std::function<void(uint32_t)>>([&menu,
                                                  &controller](uint32_t n) {
        menu.MeasureFunctionsTime(
            n,
            std::make_pair(
                std::bind(&s21::Controller::SolveTravelingSalesmanProblem,
                          &controller),
                std::string("ant colony algorithm")),
            std::make_pair(
                std::bind(
                    &s21::Controller::SolveTravelingSalesmanProblemAnnealing,
                    &controller),
                std::string("annealing algorithm")),
            std::make_pair(
                std::bind(&s21::Controller::
                              SolveTravelingSalesmanProblemNearestNeighbor,
                          &controller),
                std::string("nearest neighbor algorithm")));
      }),
      std::make_tuple("Enter the number of executions: "));
}

int main() {
  s21::Controller controller;
  bool running = true;
  s21::ConsoleMenu menu(
      "Choose an option:\n", "Invalid input\n", "> ",
      {{"Load graph from a file", [&]() { Load(menu, controller); }},
       {"Bread first traversal",
        [&]() {
          Traversal(menu,
                    std::bind(&s21::Controller::BreadthFirstSearch, &controller,
                              std::placeholders::_1),
                    "Bread ");
        }},
       {"Depth first traversal",
        [&]() {
          Traversal(menu,
                    std::bind(&s21::Controller::DepthFirstSearch, &controller,
                              std::placeholders::_1),
                    "Depth ");
        }},
       {"The shortest path between any two vertices",
        [&]() { TheShortestPath(menu, controller); }},
       {"The shortest paths between all pairs of vertices",
        [&]() { TheShortestPathAll(menu, controller); }},
       {"Minimal spanning tree",
        [&]() { MinimalSpanningTree(menu, controller); }},
       {"The salesman problem (ant colony)",
        [&]() {
          TSP(menu,
              std::bind(&s21::Controller::SolveTravelingSalesmanProblem,
                        &controller),
              "ant colony");
        }},
       {"The salesman problem (annealing)",
        [&]() {
          TSP(menu,
              std::bind(
                  &s21::Controller::SolveTravelingSalesmanProblemAnnealing,
                  &controller),
              "annealing");
        }},
       {"The salesman problem (nearest neighbor)",
        [&]() {
          TSP(menu,
              std::bind(&s21::Controller::
                            SolveTravelingSalesmanProblemNearestNeighbor,
                        &controller),
              "nearest neighbor");
        }},
       {"Compare TSP algorithms", [&]() { TSPCompare(menu, controller); }},
       {"Exit", [&running] { running = false; }}});
  while (running) {
    menu();
  }
  return 0;
}