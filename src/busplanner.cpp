/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

#include "busplanner.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;


std::ostream& operator<<(std::ostream& os, const Path& path)
{
    for(auto edge : path.path_)
    {
        os << edge.getLabel() << " from " << edge.source << " to " << edge.dest << " with weight " << edge.getWeight() << "\n";
    }
    os << "Overall Travel Time (Est): " << path.weight_ << std::endl;
    return os;
}

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
        bool add = true;
        for (auto& e : splitStrings) {
            if(e == "")
            {
                add = false;
                break;
            }
            e = Trim(e);
            //std::cout << "Final split num: " << i << " " << e << std::endl;
        }
        if(add)
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

auto get_bus_routes(const V2D& data) -> V2D
{
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
    return busRoutes;
}

auto get_bus_coordinates(const V2D& data) -> std::unordered_map<std::string, std::pair<int,int>>
{
    std::unordered_map<std::string, std::pair<int,int>> coords;
    for(size_t i = 1; i < data.size(); i++)
    {
        auto row = data[i];
        coords.insert(std::make_pair(row[0],std::make_pair(std::stoi(row[1]),std::stoi(row[2]))));
    }
    return coords;
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
                        Edge e2 = g.setEdgeLabel(startVertex, endVertex, bus);
                    } 
                }
                
            }

        }
    }

    return g;
}

auto find_path(Graph g, Vertex start, Vertex end) -> Path
{
    Path rt;
    std::vector<Edge> rt_path;
    rt.path_ = rt_path;
    rt.weight_ = 0;
    auto vertices = g.getVertices();
    if(start == end || std::find(vertices.begin(), vertices.end(), start) == vertices.end() || std::find(vertices.begin(), vertices.end(), end) == vertices.end())
    {
        return rt; // check both endpoints exist and are not each other
    }
    std::unordered_set<Vertex> visited;
    visited.insert(start);
    size_t num_vert = g.getVertices().size();
    std::unordered_map<Vertex, std::pair<Vertex, int>> distances; // Vertex, Vertex, int
    distances.insert(std::make_pair(start,std::make_pair(start,0)));
    for(Vertex neighbor : g.getAdjacent(start))
    {
        distances.insert(std::make_pair(neighbor,std::make_pair(start,g.getEdgeWeight(start,neighbor))));
    }
    Vertex current = start;
    while(current != end)
    {
        int minimum_edge = INT_MAX;
        Vertex going_to;
        for(auto pair : distances)
        {
            if(pair.second.second < minimum_edge && visited.find(pair.first) == visited.end())
            {
                going_to = pair.first;
                minimum_edge = pair.second.second;
            }
        }
        visited.insert(going_to);
        for(Vertex neighbor : g.getAdjacent(going_to))
        {
            if(distances.find(neighbor) == distances.end())
                distances.insert(std::make_pair(neighbor,std::make_pair(going_to,distances[going_to].second + g.getEdgeWeight(going_to,neighbor)))); // this node has not yet been in the dictionary
            else
            {
                int current_distance_to_neighbor = distances[neighbor].second;
                int new_distance_to_neighbor = distances[going_to].second + g.getEdgeWeight(going_to,neighbor);
                if(current_distance_to_neighbor > new_distance_to_neighbor)
                    distances[neighbor] = std::make_pair(going_to,new_distance_to_neighbor);
                
            }
        }
        current = going_to;
    }
    // now current has reached end, should have guaranteed found a path (assume one connected component)
    while(current != start)
    {
        Vertex backtrack = distances[current].first;
        rt.path_.push_back(g.getEdge(current,backtrack));
        rt.weight_ += g.getEdgeWeight(current,backtrack);
        current = backtrack;
    }
    //rt = compress_path(rt);
    rt = compress_path(rt.path_);
    return rt;
}

auto compress_path(std::vector<Edge> path) -> Path
{
    Path rt;
    std::vector<Edge> rt_path;
    rt.path_ = rt_path;
    rt.weight_ = 0;
    if(path.empty())
    {
        return rt;
    }
    std::string previous_bus = path[0].getLabel();
    for(size_t i = 0; i < path.size(); i++)
    {
        int weight = 0;
        Vertex start = path[i].source;
        Vertex end = path[i].dest;
        while(i < path.size() && path[i].getLabel() == previous_bus)
        {
            weight += path[i].getWeight();
            end = path[i].dest;
            i++;
        }
        // path[i-1] is last path with previous bus

        Edge to_add(start, end, weight, previous_bus);
        rt.path_.push_back(to_add);
        rt.weight_ += weight;
        if(i < path.size())
            previous_bus = path[i].getLabel();
        i--;
    }
    return rt;
}

cs225::PNG draw_path(const std::string& filename, Path path, std::unordered_map<std::string, std::pair<int,int>> coordinates, size_t r)
{
    cs225::PNG rt;
    rt.readFromFile(filename);
    std::pair<int,int> start = coordinates[path.path_[0].source];
    std::pair<int,int> end = coordinates[path.path_[path.path_.size()-1].dest];
    cs225::HSLAPixel red_pixel(0,1,0.5);
    cs225::HSLAPixel green_pixel(40,0.93,0.57);
    draw_cell(rt,start,r,red_pixel);
    //draw_cell(rt,end,6);
    for(Edge edge : path.path_)
    {
        BFS(rt, coordinates[edge.source], coordinates[edge.dest],r/2,red_pixel);
        draw_cell(rt, coordinates[edge.dest], r, red_pixel);
    }
    rt.writeToFile("../Data/MapPath.png");
    return rt;
}

void draw_cell(cs225::PNG& img, std::pair<int,int> coord, size_t r, const cs225::HSLAPixel& color)
{
    int x = coord.first;
    int y = coord.second;
    int r_sq = r*r;
    for(size_t x_cur = x-r; x_cur <= x+r; x_cur++)
    {
        int x_diff = x-x_cur;
        for(size_t y_cur = y-r; y_cur <= y+r; y_cur++)
        {
            if(x_cur < 0 || y_cur < 0 || x_cur >= img.width() || y_cur >= img.height())
            {
                continue;
            }
            int y_diff = y-y_cur;
            if(x_diff * x_diff + y_diff * y_diff > r_sq)
            {
                continue;
            }
            cs225::HSLAPixel& current = img.getPixel(x_cur,y_cur);
            current = color;
        }
    }
}

auto BFS(cs225::PNG& img, std::pair<int,int> start, std::pair<int,int> end, size_t r, const cs225::HSLAPixel& color) -> void
{
    std::queue<int> q;
    int width = img.width();
    int height = img.height();
    int max_pixel = width*height;
    q.push(start.second*width+start.first);
    int end_pixel = end.second*width + end.first;
    std::unordered_map<int, int> pathways; // key is y*width+x
    std::unordered_set<int> visited;
    while(!q.empty())
    {
        auto current = q.front();
        q.pop();
        //std::cout << current % width << "," << current/width << "\n";
        if(current == end_pixel)
        {
            break;
        }
        if(visited.find(current) != visited.end())
        {
            continue;
        }
        visited.insert(current);
        // key is any cell, value is the cell that got us to the key
        int right = current+1;
        int left = current-1;
        int up = current+width;
        int down = current-width;
        if(right >= 0 && right < max_pixel)
            if(visited.find(right) == visited.end())
            {
                pathways.insert(std::make_pair(right,current));
                q.push(right);
            }
        if(left >= 0 && left < max_pixel)
            if(visited.find(left) == visited.end())
            {
                pathways.insert(std::make_pair(left,current));
                q.push(left);
            }
        if(up >= 0 && up < max_pixel)
            if(visited.find(up) == visited.end())
            {
                pathways.insert(std::make_pair(up,current));
                q.push(up);
            }
        if(down >= 0 && down < max_pixel)
            if(visited.find(down) == visited.end())
            {
                pathways.insert(std::make_pair(down,current));
                q.push(down);
            }
    }
    int current = end_pixel;
    int start_pixel = start.second*width + start.first;
    int count = 0;
    while(current != start_pixel)
    {
        if(count % (r << 2) == 0)
            draw_cell(img,std::make_pair(current % width, current / width),r,color);
        current = pathways[current];
        count++;
    }
}