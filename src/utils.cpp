#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>

std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;

    size_t i = str.length() - 1;

    while (str[i] < 32) {
        i--;
    }

    return tmp.erase(i + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;

    size_t i = 0;

    while (str[i] < 32) {
        i++;
    }

    return tmp.erase(0, i);
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    if(str.size() == 0)
    {
        std::cout << "EEEEEEEEEEEEEEEEE\n";
    }
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}