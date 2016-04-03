#include <map>
#include <string>

//
// Loads the configuration file given by filename into a std::map
// 
// TODO: define input format
//
std::map<std::string, std::string> LoadConfig(std::string filename);

//
// This function will split the given string by the given delimiter and return
// the tokens as a vector of strings
//
std::vector<std::string> split_string(const std::string &str, char delim);

