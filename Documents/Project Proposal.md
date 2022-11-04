## Leading Question 
Our project consists of finding the fastest path from point A to point B using the CUMTD bus system. Users will be able to input their starting and end locations, and the best route from the two locations will be displayed. We will do this by making an weighted adjacency matrix (graph data algorithm) of the bus routes, and using Dijkstra's search algorithm (graph traversal), we will compute the shortest path between the two inputted locations.

## Dataset Acquisition
We will use the publicly available data of the bus routes at https://mtd.org/maps-and-schedules/routes/.

## Data Format

 The dataset will be imported manually, and there are 20 buses and routes for each bus that we will use data from. The dataset is not too large to use, so we will be able to use all the routes from each bus.

## Data Correction
We will manually parse the data entries from the data since it is not in an easily usable format. If we find a missing entry, we will disregard it in the adjacency matrix, since the user will not be able to use that location as a start/end point. The other data points will not have any correction needed as they are real routes that the buses take on a daily basis.

## Data Storage

To store the data of the buses and routes, we will use an adjacency matrix made from a directed graph. An estimate of the total storage costs for the dataset is O(1) since our adjacency matrix will be constant, as the buses and bus routes are unchanging. We will also memoize all intermediate steps from the source to the destination to reduce the computing time of future searches.

## Algorithm 

 The expected inputs for our algorithm are 2 locations, and the output will be found using the adjacency matrix that contains the buses and bus routes. We will use Dijkstra's algorithm to find the "best" path between these two locations. The output will be a combination of buses/bus routes as well as when walking between locations is required, which will be displayed as text to the user. This could also be displayed as a graph an image. The Big O estimate of our algorithm related to time will be O(n), where n is the distance (number of nodes) between the start and target location. The space complexity will also be O(n), because we will have traversed n nodes, which is our output (the best path to take). 

## Timeline

Week 1: Finalize project, submit team contract, project proposal, and create GitHub repository.

Week 2: Data acquisition and processing of buses and bus routes, create graph with data

Week 3: Start working on Dijkstra's algorithm to find shortest path between 2 locations.

Week 4: Finish working on Dijkstra's algorithm to find shortest path between 2 locations and store data.

Week 5: Finish project, record final presentation and write written report.
