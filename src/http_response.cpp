//
// Created by Honey on 4/12/2025.
//

#include "http_response.h"
std::string http_response::construct_response()
{
    std::string response;
    response.append(this->version);
    response.push_back(' ');
    response.append(this->status_code);
    response = response + '\r' + '\n';
    for (const auto& [key, value]: this->response_header)
    {
        response.append(key + ": " + value);
        response = response + '\r' + '\n';
    }
    response = response + '\r' + '\n';
    response.append(this->body);
    return response;
}