#include "busplanner.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char** argv) {
    // sample input: ./main "Illinois Terminal" "University and Goodwin"
    V2D data = csvToVector("../Data/BusDataWeighted.csv"); // change this to the correct file path

    V2D busRoutes = get_bus_routes(data);
    V2D stopCoordinates = csvToVector("../Data/BusCoordinates.csv");
    std::unordered_map<std::string, std::pair<int,int>> coords = get_bus_coordinates(stopCoordinates);

    Graph g = make_adj_list(busRoutes);
    vector<Vertex> vertices = g.getVertices();
    Vertex end; // flip user start and end since we output in reverse order
    Vertex start;
    if(argc != 3)
    {
        printVector(vertices);
        std::cout << "Input ./main 'Start Location' 'End Location'" << std::endl;
        return 0;
    }
    end = argv[1];
    start = argv[2];
    if(std::find(vertices.begin(),vertices.end(),end) == vertices.end())
    {
        printVector(vertices);
        std::cout << "Start Location not valid, please enter a valid stop\n";
        return 0;
    }
    if(std::find(vertices.begin(),vertices.end(),start) == vertices.end())
    {
        printVector(vertices);
        std::cout << "End Location not valid, please enter a valid stop\n";
        return 0;
    }
    
    auto path = find_path(g,start,end);
    auto img = draw_path("../Data/Map.png",path,coords, 6);
    std::cout << path << std::endl;
    return path.weight_;
}
