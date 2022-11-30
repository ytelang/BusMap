#include <catch2/catch_test_macros.hpp>

#include "busplanner.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <fstream>

using namespace cs225;

bool fileExists(std::string fileName) {
  std::ifstream f(fileName.c_str());
  bool exists = f.good();
  f.close();

  return exists;
}


//
// Basic tests
//
TEST_CASE("Runs without a seg fault", "[weight=2]") {
	REQUIRE(true);
}