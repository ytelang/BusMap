<p align = "center">
    <h1>Written Report</h1>
  </p>

For this project, we wanted to create a program which would find the quickest path using the MTD transit system. Using our algorithms (Dijkstra's, BFS, and the graphic output of the graph) we were able to create an efficient mode of transport between bus stops all around campus.

In order to run these algorithms, we first had to create a meaningful data structure to store the data that was parsed from the CSV file. We felt that the best way to represent bus stops and the routes between them was an undirected, weighted graph. We took inspiration from lab_ml and utilized the graph class from that lab, which utilized an edge list to store the data in the graph, because it was the most efficient for our purposes. The first feature we implemented was finding the shortest path between any two nodes on the graph, or any two bus stops. As the graph was undirected and weighted, it meant we needed to utilize Dijkstra's algorithm. From this, we get a `Path` object, which contains a vector of edges and the total weight (estimated time) of the path. This means we now have a list of bus routes to take and the total number of minutes it would take to get to our destination.

We then parsed the coordinates of each bus stop from the `Data/BusCoordinates.csv` and used BFS to find the shortest path between each stop that was in our Path object. Using the shortest path between 2 stops found from BFS, we created a graphical output which highlighted the start and end locations, and the path between them. From this, we wrote the output to a PNG, which is displayed to the user after running the program.
