/**
 * @file sketchify.h
 * Declaration of the sketchify function.
 */

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "utils.h"
#include "Graph.h"
typedef std::vector<std::vector<std::string>> V2D;

using std::vector;
using std::map;

struct Path
{
    std::vector<Edge> path_;
    int weight_;
};

void printVector(const std::vector<std::string>& v);
void printVector(const std::vector<int>& v);

V2D csvToVector(const std::string & filename);

auto get_bus_routes(const V2D& data) -> V2D;

auto get_bus_coordinates(const V2D& data) -> std::unordered_map<std::string, std::pair<int,int>>;

Graph make_adj_list(const V2D &routes);

auto find_path(Graph g, Vertex start, Vertex end) -> Path;

auto compress_path(std::vector<Edge> path) -> Path;

std::ostream& operator<<(std::ostream& os, const Path& path);

cs225::PNG draw_path(const std::string& filename, Path path, std::unordered_map<std::string, std::pair<int,int>> coordinates, size_t r);

void draw_cell(cs225::PNG& img, std::pair<int,int> coord, size_t r, const cs225::HSLAPixel& color);

auto BFS(cs225::PNG& img, std::pair<int,int> start, std::pair<int,int> end, size_t r, const cs225::HSLAPixel& color) -> void;