# SimpleNavigator (Group project, 2 members)

Learning about graphs and their navigation, including the basic algorithms, such as: search, the shortest path, TSP.

## Task

Within this task, all graphs must meet the following requirements:
- Edge weights are only natural numbers
- There may be loops
- Weights may differ on all edges
- Only a nonzero connected graph

## Part 1. Depth- and Breadth-first search 

Implementation of the _scp_graph.h_  library:  
* The library must be developed in C++ language of C++17 standard
* The library must be represented as a `Graph` class that stores information about the graph using an **adjacency matrix**. The dimensionality of the adjacency matrix should be set dynamically when initializing the graph (when loading it from a file)
* The class `Graph` must contain at least the following public methods:
    + `LoadGraphFromFile(string filename)` - loading a graph from a file in the adjacency matrix format
    + `ExportGraphToDot(string filename)`- exporting a graph to a dot file (see materials)

Implementation of the _scp_graph_algorithms.h_ library:  
* The library must be developed in C++ language of C++17 standard
* The library must be represented as a ` GraphAlgorithms ` class that stores the implementation of algorithms on graphs. The class `GraphAlgorithms` itself must not know anything about the internal representation of the graph from the class `Graph`. To interact with graph data, the class `GraphAlgorithms` can only use the public methods and properties provided by the `Graph` class. 
* The class ` GraphAlgorithms ` must contain at least the following public methods:
    + `DepthFirstSearch(Graph &graph, int start_vertex)` - a *non-recursive* depth-first search in the graph from a given vertex
    + `BreadthFirstSearch(Graph &graph, int start_vertex)` - breadth-first search in the graph from a given vertex

*In this and the following tasks, consider that the vertex numbers start from 1*

## Part 2. Finding the shortest paths in a graph

* Add two new methods to the `GraphAlgorithms` class:
    + `GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)` - searching for the shortest path between two vertices in a graph using *Dijkstra's algorithm*. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them
    + `GetShortestPathsBetweenAllVertices(Graph &graph)` - searching for the shortest paths between all pairs of vertices in a graph using the *Floyd-Warshall algorithm*. As a result, the function returns the matrix of the shortest paths between all vertices of the graph

## Part 3. Finding the minimum spanning tree

* Add a new method to the `GraphAlgorithms` class:
    + `GetLeastSpanningTree(Graph &graph)` - searching for the minimal spanning tree in a graph using *Prim's algorithm*. As a result, the function should return the adjacency matrix for the minimal spanning tree

## Part 4. Traveling salesman problem

* Add a new method to the `GraphAlgorithms` class:
    + `SolveTravelingSalesmanProblem(Graph &graph)` - solving the traveling salesman's problem using the *ant colony algorithm*.
You need to find the shortest path that goes through all vertices of the graph at least once, followed by a return to the original vertex. As a result, the function should return the `TsmResult` structure described below:
    ```cpp
    struct TsmResult {
        std::vector<int>; // an array with the route you are looking for (with the vertex traverse order)
        double distance;  // the length of this route
    }
    ``` 

*If it is impossible to solve the problem with a given graph, output an error.*

## Part 5. Console interface

* You need to write the main program, which is a console application for testing the functionality of the implemented scp_graph.h and scp_graph_algorithms.h libraries 
* The console interface must provide the following functionality:
    1. loading the original graph from a file
    2. graph traversal in breadth with output of the result to the console   
    3. graph traversal in depth with output of the result to the console
    4. searching for the shortest path between any two vertices and displaying the result to the console
    5. searching for the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
    6. searching for the minimal spanning tree in the graph with the output of the resulting adjacency matrix to the console
    7. solving the salesman problem with the output of the resulting route and its length to the console

## Part 6. Bonus. Comparison of methods for solving the traveling salesman problem

* It is necessary to choose two additional algorithms to solve the traveling salesman problem and implement them as methods of the `GraphAlgorithms` class
* Add to the console interface the ability to perform a comparison of  speed of the three algorithms (the ant colony algorithm and two randomly selected algorithms)
    + The study starts for a graph that was previously loaded from a file.
    + As part of the study you need to keep track of the time it took to solve the salesman's problem `N` times in a row, by each of the algorithms. Where `N` is set from the keyboard.
    + The results of the time measurement must be displayed in the console.

*Example:* For `N = 1000` it will measure how long it will take to solve the traveling salesman problem 1000 times for the current given graph by an ant colony algorithm and two randomly chosen algorithms.
