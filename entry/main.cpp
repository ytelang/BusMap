#include "busplanner.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    std::cout << "hello world" << std::endl;

    V2D data = csvToVector("/workspaces/CS225/CS225 Project/BusData.csv");

    /*
    for (auto v : data) {
        //vector<string> vec;
        //int num = utils::SplitString()

        cout << "Vector: ";
        printVector(v);
        cout << "\n";

        cout << v.size() << endl;
    }
    */
    
    V2D busRoutes;

    for (size_t j = 0; j < data[0].size(); j++) {
        vector<string> v;
        for (size_t i = 0; i < data.size(); i++) {
            
            if (data[i][j] != "NA" && data[i][j] != "IGNORE") {
                std::cout << data[i][j] << " , length is: " << data[i][j].length() << std::endl;
                v.push_back(data[i][j]);
            }
            
        }
        busRoutes.push_back(v);
    }

    
    for (auto v : busRoutes) {
        //vector<string> vec;
        //int num = utils::SplitString()

        cout << "Vector size is " << v.size() << ": ";
        printVector(v);
        cout << "\n";
    }
    
    return 0;
}
