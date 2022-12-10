/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "busplanner.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

V2D csvToVector(const std::string & filename){
    V2D rtn;
    
    string str = file_to_string(filename);
    vector<string> split;

    int splitNum = SplitString(str, '\n', split);

    //for (auto e : split) {
    //    std::cout << "Original split: " << e << std::endl;
    //}

    for (int i = 0; i < splitNum; i++) {
        vector<string> splitStrings;
        int splitStringsNum = SplitString(split[i], ',', splitStrings);

        for (auto& e : splitStrings) {
            e = Trim(e);
            //std::cout << "Final split num: " << i << " " << e << std::endl;
        }

        rtn.push_back(splitStrings);
    }


    return rtn;
}



void printVector(const std::vector<std::string>& v){
    
    for (size_t i = 0; i < v.size(); i++) {
        if (i != v.size() - 1) {
            std::cout << v[i] << ", ";
        } else {
            std::cout << v[i] << std::endl;
        }
    }
}

void printVector(const std::vector<int>& v){
    
    for (size_t i = 0; i < v.size(); i++) {
        if (i != v.size() - 1) {
            std::cout << v[i] << ", ";
        } else {
            std::cout << v[i] << std::endl;
        }
    }
}

Graph make_adj_list(const V2D &routes) {
    Graph g(true);

    for (size_t i = 0; i < routes.size(); i += 3) {
        string bus = routes[i][0];
        for (size_t j = 1; j < routes[i].size(); j++) {
            Vertex startVertex = routes[i][j];
            int currentDistance = 0;
            
            for (size_t k = j + 1; k < routes[i].size(); k++) {
                Vertex endVertex = routes[i][k];
                currentDistance += std::stoi(routes[i+2][k]);
                
                if (!g.edgeExists(startVertex, endVertex)) {
                    bool b = g.insertEdge(startVertex, endVertex);
                    Edge e = g.setEdgeWeight(startVertex, endVertex, currentDistance);
                    Edge e2 = g.setEdgeLabel(startVertex, endVertex, bus);
                } else {
                    int currWeight = g.getEdgeWeight(startVertex, endVertex);
                    if (currentDistance < currWeight) {
                        Edge e = g.setEdgeWeight(startVertex, endVertex, currentDistance);
                    } 
                }
                
            }

        }
    }

    return g;
}