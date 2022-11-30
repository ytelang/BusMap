/**
 * @file sketchify.h
 * Declaration of the sketchify function.
 */

#pragma once

#include <string>
#include <vector>
#include "utils.h"
typedef std::vector<std::vector<std::string>> V2D;

void printVector(const std::vector<std::string>& v);

V2D csvToVector(const std::string & filename);
