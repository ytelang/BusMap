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
    int count = 0;
    
    for (std::string s : v){
        cout << s << ", ";
        count++;
    }
    cout << '\n';
}

