#include "busplanner.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::vector;
using std::string;

int main() {
    std::cout << "hello world" << std::endl;

    V2D data = csvToVector("/workspaces/CS225/CS225 Project/BusData.csv");


    
    for (auto v : data) {
        //vector<string> vec;
        //int num = utils::SplitString()

        cout << "Vector: ";
        printVector(v);
        cout << "\n";
    }







    return 0;
}
