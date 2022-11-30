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
TEST_CASE("Test Bus Yellow 1", "[weight=2]") {

  V2D data = csvToVector("/workspaces/CS225/CS225 Project/BusData.csv");

  V2D busRoutes;

  for (size_t j = 0; j < data[0].size(); j++) {
      vector<std::string> v;
      for (size_t i = 0; i < data.size(); i++) {
          
          if (data[i][j] != "NA" && data[i][j] != "IGNORE") {
              //std::cout << data[i][j] << std::endl;
              v.push_back(data[i][j]);
          }
          
      }
      busRoutes.push_back(v);
  }

  //REQUIRE(1 == 1);
  //REQUIRE(strcmp("Hello", "Hello") == 0);
  std::string a = "Yellow 1";
  //std::cout << typeid(a).name() << std::endl;
  //std::cout << typeid(busRoutes[0][0]).name() << std::endl;
  REQUIRE(busRoutes[0][0] == a);

  /*
  for (size_t i = 0; i < busRoutes[0][0].size(); i++) {
    std::cout << busRoutes[0][0][i] << std::endl;
  }

  std::cout << busRoutes[0][0].length() << std::endl;
  std::cout << busRoutes[0][0] << std::endl;
  std::cout << a.length() << std::endl;
  */

  std::vector<string> Yellow1Answer {"Yellow 1", "Savoy Walmart", "The Place at 117", "Fox and Windsor", "Lot E-14", "Transit Plaza", "Illnois Terminal", "Market Place", "Champaign Walmart"};
	REQUIRE(busRoutes[0] == Yellow1Answer);
}