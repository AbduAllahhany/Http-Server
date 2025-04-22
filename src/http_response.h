//
// Created by Honey on 4/12/2025.
//

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#include <map>
#include <string>
#include <unordered_map>

static std::unordered_map<int,std::string> status_code {
    {100,"100 Continue"},
    {101,"101 Switching Protocols"},
    {200,"200 OK"},
    {201,"201 Created"},
    {202,"202 Accepted"},
    {203,"203 Non-Authoritative Information"},
    {204,"204 No Content"},
    {205,"205 Reset Content"},
    {206,"206 Partial Content"},
    {300,"300 Multiple Choices"},
    {301,"301 Moved Permanently"},
    {302,"302 Found"},
    {303,"303 See Other"},
    {304,"304 Not Modified"},
    {307,"307 Temporary Redirect"},
    {308,"308 Permanent Redirect"},
    {400,"400 Bad Request"},
    {401,"401 Unauthorized"},
    {402,"402 Payment Required"},
    {403,"403 Forbidden"},
    {404,"404 Not Found"},
    {405,"405 Method Not Allowed"},
    {406,"406 Not Acceptable"},
    {408,"408 Request Timeout"},
    {409,"409 Conflict"},
    {410,"410 Gone"},
    {411,"411 Length Required"},
    {412,"412 Precondition Failed"},
    {413,"413 Content Too Large"},
    {414 ,"414 URI Too Long"},
    {500,"500 Internal Server Error"},
    {501,"501 Not Implemented"},
    {502,"502 Bad Gateway"},
    {503,"503 Service Unavailable"},
    {504,"504 Gateway Timeout"},
    {505,"505 HTTP Version Not Supported"},
};
class http_response
{
public:
    std::string version;
    std::string status_code;
    std::unordered_map<std::string, std::string> response_header;
    std::string body;
    std::string construct_response();
};



#endif //HTTP_RESPONSE_H
