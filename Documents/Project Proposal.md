## Leading Question 
Our project consists of finding the fastest path from point A to point B using the CUMTD bus system. Users will be able to input their starting and end locations, and the best route from the two locations will be displayed. We will do this by making an weighted adjacency matrix of the bus routes, using BFS to find the shortest path between 2 nodes in the graph that the adjacency matrix represents, and then using Dijkstra's search algorithm and the A* search algorithm (with a search heuristic to improve optimality, where if the current path is worse than the best path already found, it is disregarded) to find and store the best path to take. Using these 3 algorithms, we will compute, store, and output the fastest path between the two inputted locations.

## Dataset Acquisition
We will use the publicly available data of the bus routes at https://mtd.org/maps-and-schedules/routes/.  We will be using the "currently running routes" on weekdays (which are the same for every weekday), which means there are 20 buses (Yellow, Red, Lavender, Blue, etc) and their routes that we will use.

## Data Format

 The dataset will be imported manually (hardcoded from the entries on the website), and we will use the aforementioned 20 buses and routes for each bus to get our data from. The dataset is not too large to use, so we will be able to use all the routes from each bus in our adjacency matrix.

## Data Correction
We will manually parse the data entries from the data since it is not in an easily usable format. If we find a missing entry, we will disregard it in the adjacency matrix, since the user will not be able to use that location as a start/end point. The other data points will not have any correction needed as they are real routes that the buses take on a daily basis.

## Data Storage

To store the data of the buses and routes, we will use an adjacency matrix made from a directed graph. An estimate of the total storage costs for the dataset is O(n^2) since our adjacency matrix will contain a path from one bus stop to another, for all bus stops (if it doesn't exist, it will be 0 and we can disregard it). We will also memoize all intermediate steps from the source to the destination to reduce the computing time of future searches.

## Algorithm 

 The expected inputs for our algorithm are 2 locations, and the output will be found using the adjacency matrix that contains the buses and bus routes and the following algorithms. We will use BFS to find the shortest path between 2 nodes in the graph that the adjacency matrix represents, and then use Dijkstra's search algorithm and the A* search algorithm (with a search heuristic to improve optimality, where if the current path is worse than the best path already found, it is disregarded) to find and store the best path to take. The output will be a combination of buses/bus routes as well as when walking between locations is required, which will be displayed as text to the user. This could also be displayed as a graph or an image. The Big O estimate of our algorithm related to time will be O(n^2), where n is the distance (number of nodes) between the start and target location. The space complexity will also be O(n^2), because we will have traversed n nodes and their neighbors in the graph to get our output (the best path to take). 

## Timeline

Week 1: Finalize project, submit team contract, project proposal, and create GitHub repository.

Week 2: Resubmit project proposal, start data acquisition and processing of buses and bus routes to create graph with data.

Week 3: Finish creation of graph with data, work on BFS to find shortest path between 2 nodes of the graph.

Week 4: Work on Dijkstra's algorithm and the A* search algorithm to find shortest path between 2 locations and store data.

Week 5: Finish Dijkstra's algorithm and A* search algorithm to store/output best path between two inputted locations, record final presentation and write written report.
