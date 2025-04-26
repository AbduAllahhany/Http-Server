
#include "http_request.h"
#include "helper_function.h"


// helper function
std::vector< std::string > split(const std::string &str,
                                 const std::string &delimiters,
                                 bool keepEmpty = false) {
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

