#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "SimUtil.h"

#define DEBUG false

//
// The LoadConfig function loads the configuration file given by filename
// It returns a map of key-value pairs stored in the conifuration file
//
std::map<std::string,std::string> LoadConfig(std::string filename)
{
    if (DEBUG) { std::cout << "Loading configuration..." << std::endl; }

    std::ifstream input(filename);
    std::map<std::string,std::string> ans;
    while(input)
    {
        std::string key;
        std::string value;

        //
        // Read up to the : delimiter into key, read up to the newline into value
        //
        std::getline(input, key, ':'); 
        std::getline(input, value, '\n'); 

        //
        // Read between the double quotes
        //
        std::string::size_type pos1 = value.find_first_of("\""); //Find the first quote in the value
        std::string::size_type pos2 = value.find_last_of("\""); //Find the last quote in the value

        //
        // Ensure valid positions and store the result
        //
        if(pos1 != std::string::npos && pos2 != std::string::npos && pos2 > pos1)
        {
            value = value.substr(pos1+1,pos2-pos1-1);
            ans[key] = value;
            if (DEBUG)
            {
                std::cout << "Adding " << key << " -> " << value << std::endl;
            }
        }
    }

    input.close();
    return ans;
}

//
// This function will split the given string by the given delimiter and return
// the tokens as a vector of strings
//
std::vector<std::string> split_string(const std::string &str, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delim))
    {
        tokens.push_back(token);
    }

    return tokens;
}
