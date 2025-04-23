#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helper_function.h"

#include "http_request.h"
#include "http_response.h"

#define HTTP_VERSION "HTTP/1.1"
#define Ok "Ok"
#define NotFound "Not Found"


//end points

std::string directory;


http_response* echo(std::string s="")
{
    std::unordered_map<std::string, std::string> header;
    header["Content-Length"] = std::to_string(s.size());
    header["Content-Type"] = "text/plain";
    auto res = new http_response;
    res->version = HTTP_VERSION;
    res->status_code = status_code[200];
    res->body = s;
    res->response_header = header;
    return res;
}

http_response* useragent(std::string header)
{
    return echo(header);
}

http_response* ok()
{
    auto res = new http_response;
    res->version = HTTP_VERSION;
    res->status_code = status_code[200];
    return res;
}
http_response* notfound()
{
    auto res = new http_response;
    res->version = HTTP_VERSION;
    res->status_code = status_code[404];
    return res;
}

http_response* files(std::string fileName) {
    FILE *file;
    char buffer[256];
    std::string path = " ../ " + directory + fileName + ".txt";
    std::cout<<path<<std::endl;
    file = fopen(path. c_str(), "r");
    if (file == nullptr)
        return notfound();
    while (fgets(buffer, sizeof(buffer), file));
    fclose(file);

    std::string fileText(buffer);
    std::unordered_map<std::string, std::string> header;
    header["Content-Length"] = std::to_string(fileText.size());
    header["Content-Type"] = "application/octet-stream";
    auto res = new http_response;
    res->version = HTTP_VERSION;
    res->status_code = status_code[200];
    res->body = fileText;
    res->response_header = header;
    return res;
}

std::unordered_map<std::string, http_response*(*)(std::string)> end_points;
std::unordered_map<std::string, http_response*(*)()> standard_end_points;
std::unordered_map<std::string, http_response*(*)(std::string)> header_end_points;



void* handleHttpResponse(void* arg) {
    char buf[1024];
    int client_fd = *(int *) arg;

    ssize_t received_bits = recv(client_fd, buf, sizeof(buf) - 1, 0);
    if (received_bits > 1)
        buf[received_bits] = '\0';
    else {
        close(client_fd);
        return nullptr;
    }
    std::string request(buf);
    if (request.empty()) {
        close(client_fd);
        return nullptr;
    }
    http_request *req = new http_request(request);
    http_response *res = standard_end_points[NotFound]();;

    ///
    if (req->URL.size() == 0) {
        res = standard_end_points[Ok]();
    } else if (req->URL.size() == 1) {
        if (tolower(req->URL[0]) == "index.html")
            res = standard_end_points[Ok]();
        else if (header_end_points.contains(tolower(req->URL[0])))
            res = header_end_points[tolower(req->URL[0])](req->request_header[req->URL[0]]);
        else
            res = standard_end_points[NotFound]();
    } else if (end_points.contains(tolower(req->URL[0]))) {
        res = end_points[tolower(req->URL[0])](req->URL[1]);
    }
    //
    auto temp = res->construct_response();
    const char *response_message = temp.c_str();
    int bytes_sent = send(client_fd, response_message, strlen(response_message), 0);
    close(client_fd);
    return nullptr;
}



int main(int argc, char** argv) {
    //initialization
    end_points["echo"] = echo;
    standard_end_points[Ok] = ok;
    standard_end_points[NotFound] = notfound;
    header_end_points["user-agent"] = useragent;
    end_points["files"] = files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--directory" && i + 1 < argc) {
            directory = argv[i + 1];
            break;
        }
    }

    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here!\n";

    // Uncomment this block to pass the first stage

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create server socket\n";
        return 1;
    }

    // Since the tester restarts your program quite often, setting SO_REUSEADDR
    // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(4221);

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to bind to port 4221\n";
        return 1;
    }

    int connection_backlog = 5;
    if (listen(server_fd, connection_backlog) != 0) {
        std::cerr << "listen failed\n";
        return 1;
    }

    int cnt = 0;
    while (1) {
        pthread_t thread;
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        std::cout << "Waiting for a client to connect...\n";
        int client_fd = accept(server_fd, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
        std::cout << "Client connected\n";
        cnt++;
        std::cout << cnt << std::endl;
        pthread_create(&thread, nullptr, handleHttpResponse, &client_fd);
        pthread_detach(thread);
    }
    close(server_fd);
    return 0;
}
