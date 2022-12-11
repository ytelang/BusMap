#include "busplanner.h"
#include "utils.h"
#include "adj_list.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {

    V2D data = csvToVector("/workspaces/cs225/final_project/BusDataWeighted.csv"); // change this to the correct file path

    /*
    for (auto v : data) {
        //vector<string> vec;
        //int num = utils::SplitString()

        cout << "Vector: ";
        printVector(v);
        cout << "\n";

        cout << v.size() << endl;
    }
    */
    
    V2D busRoutes;

    for (size_t j = 0; j < data[0].size(); j++) {
        vector<string> v;
        for (size_t i = 0; i < data.size(); i++) {
            
            if (data[i][j] != "NA") {
                //std::cout << data[i][j] << " , length is: " << data[i][j].length() << std::endl;
                v.push_back(data[i][j]);
            }
            
        }
        busRoutes.push_back(v);
    }

    //std::cout << busRoutes.size() << std::endl;

    /*
    for (auto v : busRoutes) {
        //vector<string> vec;
        //int num = utils::SplitString()

        //cout << "Vector size is " << v.size() << ": ";
        printVector(v);
        cout << "\n";
    }
    */

    //vector<vector<int>> adj_matrix = make_adjacency_matrix(busRoutes);

    Graph g = make_adj_list(busRoutes);
    vector<Vertex> vertices = g.getVertices();
    /*
    for (auto vertex : vertices) {
        vector<Vertex> adj_vertices = g.getAdjacent(vertex);

        for (auto e : adj_vertices) {
            cout << "Edge from " << vertex << " to " << e << " by taking bus " << g.getEdgeLabel(vertex, e) << " with weight " << g.getEdgeWeight(vertex, e) << endl;
        }
    }    
    std::cout << "\n\n\n\n\n\n\n";
    */
    Vertex start = "High Cross and Kyle";
    Vertex end = "Champaign Walmart";
    auto path = find_path(g,start,end);
    for(auto edge : path)
    {
        std::cout << g.getEdgeLabel(edge.source,edge.dest) << " | from " << edge.source << " to " << edge.dest << std::endl;
    }
    
    return 0;
}
