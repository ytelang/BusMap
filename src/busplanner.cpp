/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "busplanner.h"
using namespace std;

V2D csvToVector(const std::string & filename){
    V2D result;
    std::string full = file_to_string(filename);
    std::vector<std::string> rows;
    SplitString(full, '\n', rows);
    for (int i=0; i<(int)rows.size(); i++){
        std::vector<std::string> indiv;
        SplitString(rows[i], ',', indiv);
        for (int j=0; j<(int)indiv.size(); j++){
            if (j>0) indiv[j] = TrimLeft(indiv[j]);
        }
        result.push_back(indiv);
    }
    
    return result;
}



void printVector(const std::vector<std::string>& v){
    for (std::string s : v){
        cout << s << ',';
    }
    cout << '\n';
}
