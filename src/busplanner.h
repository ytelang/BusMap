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

#include "utils.h"
#include "adj_list.h"
typedef std::vector<std::vector<std::string>> V2D;

using std::vector;
using std::map;

void printVector(const std::vector<std::string>& v);
void printVector(const std::vector<int>& v);

V2D csvToVector(const std::string & filename);

Graph make_adj_list(const V2D &routes);

auto find_path(Graph g, Vertex start, Vertex end) -> std::vector<Edge>;

auto compress_path(std::vector<Edge> path) -> std::vector<Edge>;