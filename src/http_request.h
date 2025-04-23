#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include "helper_function.h"


enum http_method
{
    GET = 0,
    POST,
    OPTION,
    PUT,
    DELETE,
    PATCH
};

class http_request
{
public:
    http_request(std::string url);
    ~http_request();
    http_method method;
    std::vector<std::string> URL;
    std::string version;
    std::unordered_map<std::string, std::string> request_header;
    std::string body;

private:
    void extract_data(std::string url);
};


#endif //HTTP_REQUEST_H
