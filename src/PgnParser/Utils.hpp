/**
* @file Utils.hpp
*
* Contains generics tools.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/
#ifndef INCLUDE_PGN_PARSER_UTILS_HPP_
#define INCLUDE_PGN_PARSER_UTILS_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace m8db
{
  // This function returns a vector of strings containing the substring 
  // contained in s and separated by delim.
  inline std::vector<std::string> split(const std::string& s, char delim)
  {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while(getline(iss, token, delim))
    {
      tokens.push_back(token);
    }
    return tokens;    
  }
}

#endif // INCLUDE_PGN_PARSER_UTILS_HPP_
