
#include "helper_function.h"

// helper function
std::vector< std::string > split(const std::string &str,
                                 const std::string &delimiters,
                                 bool keepEmpty) {
    std::vector< std::string > tokens;
    std::string::size_type pos  = 0;
    std::string::size_type prev = 0;

    while ((pos = str.find_first_of(delimiters, prev)) != std::string::npos) {
        if (keepEmpty || pos > prev) {
            tokens.push_back(str.substr(prev, pos - prev));
        }
        prev = pos + 1;
    }

    if (prev < str.length()) {
        tokens.push_back(str.substr(prev));
    } else if (keepEmpty && prev == str.length()) {
        tokens.push_back("");
    }
    return tokens;
}


std::string tolower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

http_method httpMethod(const std::string& methodStr) {
    static const std::unordered_map<std::string, http_method> httpMethodMap = {
            {"option", http_method::OPTION},
            {"post", http_method::POST},
            {"delete", http_method::DELETE},
            {"put", http_method::PUT},
            {"patch", http_method::PATCH},
            {"get", http_method::GET}};

    auto it = httpMethodMap.find(tolower(methodStr));
    return (it != httpMethodMap.end()) ? it->second : http_method::UNKNOWN;
}
