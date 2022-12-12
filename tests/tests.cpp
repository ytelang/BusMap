#include <catch2/catch_test_macros.hpp>

#include "busplanner.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace cs225;
using std::vector;
using std::cout;
using std::endl;
using std::string;

bool fileExists(std::string fileName) {
  std::ifstream f(fileName.c_str());
  bool exists = f.good();
  f.close();

  return exists;
}



//
// Basic tests
//
TEST_CASE("Read Bus Data", "[weight=1]") {
  REQUIRE(fileExists("../Data/BusDataWeighted.csv"));
  V2D data = csvToVector("../Data/BusDataWeighted.csv");
  REQUIRE(data[0][0] == "Yellow 1");
  auto last_row = data[data.size()-1];
  REQUIRE(last_row[last_row.size()-1] == "-1");
  REQUIRE(data.size() == 12);
  REQUIRE(data[2].size() == 54);
}

TEST_CASE("Read Bus Coordinates", "[weight=1]") {

  REQUIRE(fileExists("../Data/BusCoordinates.csv"));
  V2D data = csvToVector("../Data/BusCoordinates.csv");
  REQUIRE(data[0][0] == "Name");
  auto last_row = data[data.size()-1];
  REQUIRE(last_row[last_row.size()-1] == "813");
  REQUIRE(data.size() == 68);
  REQUIRE(data[2].size() == 3);
}

TEST_CASE("Make Adjacency List", "[weight=10]") {
  REQUIRE(fileExists("../Data/BusDataWeighted.csv"));
  V2D data = csvToVector("../Data/BusDataWeighted.csv");
  V2D busRoutes = get_bus_routes(data);
  Graph g = make_adj_list(busRoutes);

  std::unordered_set<Vertex> water_survey_neighbors{"University and Wright", "Transit Plaza", "Lot E-14"};
  auto water_neighbors = g.getAdjacent("Water Survey");
  for(Vertex neighbor : water_neighbors)
  {
    REQUIRE(water_survey_neighbors.find(neighbor) != water_survey_neighbors.end());
  }
  std::unordered_set<Vertex> u_and_cg_neighbors{"Plastipak", "Round Barn Road", "Park and Wright", "Lincoln Square", "Illinois Terminal", "Butzow and Lierman", "US and 150 & Dodson Dr"};
  auto ucg_neighbors = g.getAdjacent("University and Cottage Grove");
  for(Vertex neighbor : ucg_neighbors)
  {
    REQUIRE(u_and_cg_neighbors.find(neighbor) != u_and_cg_neighbors.end());
  }
  std::unordered_set<Vertex> vet_med_neighbors{"Vet-Med", "Florida Ave. Residence Hall", "Illini Union", "Pennsylvania Ave. Residence Hall"};
  auto vm_neighbors = g.getAdjacent("Vet-Med");
  for(Vertex neighbor : vm_neighbors)
  {
    REQUIRE(vet_med_neighbors.find(neighbor) != vet_med_neighbors.end());
  }
}

TEST_CASE("Find Invalid Path", "[weight=5]") {
  REQUIRE(fileExists("../Data/BusDataWeighted.csv"));
  V2D data = csvToVector("../Data/BusDataWeighted.csv");
  V2D busRoutes = get_bus_routes(data);
  Graph g = make_adj_list(busRoutes);
  
  auto path = find_path(g,"Invalid Stop",g.getVertices()[0]);
  REQUIRE(path.weight_ == 0);
  REQUIRE(path.path_.size() == 0);

  path = find_path(g,g.getVertices()[0],"Invalid Stop");
  REQUIRE(path.weight_ == 0);
  REQUIRE(path.path_.size() == 0);

  path = find_path(g,"Invalid Stop","Invalid Stop");
  REQUIRE(path.weight_ == 0);
  REQUIRE(path.path_.size() == 0);
}

TEST_CASE("Find (Compressed) Path", "[weight=10]") {
  REQUIRE(fileExists("../Data/BusDataWeighted.csv"));
  V2D data = csvToVector("../Data/BusDataWeighted.csv");
  V2D busRoutes = get_bus_routes(data);
  Graph g = make_adj_list(busRoutes);
  
  auto path = find_path(g,"Illinois Terminal","Butzow and Lierman"); // one bus, multiple stops
  REQUIRE(path.weight_ == 19);
  REQUIRE(path.path_.size() == 1);
  REQUIRE(path.path_[0].source == "Butzow and Lierman");
  REQUIRE(path.path_[0].dest == "Illinois Terminal");
  REQUIRE(path.path_[0].getLabel() == "Orange 6");

  path = find_path(g,"Savoy Walmart","Market Place"); // several different buses, multiple stops
  REQUIRE(path.weight_ == 51);
  REQUIRE(path.path_.size() == 3);
  REQUIRE(path.path_[0].source == "Market Place");
  REQUIRE(path.path_[0].dest == "Illinois Terminal");
  REQUIRE(path.path_[0].getLabel() == "Red 2");

  REQUIRE(path.path_[1].source == "Illinois Terminal");
  REQUIRE(path.path_[1].dest == "Lot E-14");
  REQUIRE(path.path_[1].getLabel() == "Navy 14");

  REQUIRE(path.path_[2].source == "Lot E-14");
  REQUIRE(path.path_[2].dest == "Savoy Walmart");
  REQUIRE(path.path_[2].getLabel() == "Yellow 1");

  path = find_path(g,"Round Barn Road","Washington and Lierman"); // while all start and end are on one bus, faster to hop between buses
  REQUIRE(path.weight_ == 34);
  REQUIRE(path.path_.size() == 4);
  REQUIRE(path.path_[0].source == "Washington and Lierman");
  REQUIRE(path.path_[0].dest == "Florida and Philo");
  REQUIRE(path.path_[0].getLabel() == "Green 5");

  REQUIRE(path.path_[1].source == path.path_[0].dest);
  REQUIRE(path.path_[1].dest == "Lincoln Square");
  REQUIRE(path.path_[1].getLabel() == "Red 2");

  REQUIRE(path.path_[2].source == path.path_[1].dest);
  REQUIRE(path.path_[2].dest == "Illinois Terminal");
  REQUIRE(path.path_[2].getLabel() == "Orange 6");

  REQUIRE(path.path_[3].source == path.path_[2].dest);
  REQUIRE(path.path_[3].dest == "Round Barn Road");
  REQUIRE(path.path_[3].getLabel() == "Green 5");
}