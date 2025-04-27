
#include "http_request.h"
#include "helper_function.h"



http_request::http_request(std::string url)
{
    extract_data(url);
}

http_request::~http_request()
= default;

void http_request::extract_data(std::string url)
{
    int body_pos                       = url.find("\r\n\r\n");

    std::vector< std::string > request = split(url.substr(0, body_pos), "\r\n");
    std::string  body    = url.substr(body_pos+4);
    std::vector< std::string > start_line   = split(request[0], " ");

    this->method                        = httpMethod(start_line[0]);
    this->URL                           = split(start_line[1], "/");
    this->version                       = start_line[2];

    this->body                          = body;
    for (int i = 1; i < request.size(); i++)
    {
        auto temp                    = split(request[i], ":");
        this->request_header[tolower(temp[0])] = temp[1].substr(1);
    }
}

