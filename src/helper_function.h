//
// Created by Honey on 4/14/2025.
//

#ifndef HELPER_FUNCTION_H
#define HELPER_FUNCTION_H
#include "http_request.h"
#include <algorithm>

extern std::string tolower(const std::string& input);

extern http_method httpMethod(const std::string& methodStr);
extern std::vector< std::string > split(const std::string &str,
                                 const std::string &delimiters,
                                 bool keepEmpty = false);
#endif //HELPER_FUNCTION_H
