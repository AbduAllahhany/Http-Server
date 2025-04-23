
#include "helper_function.h"


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
