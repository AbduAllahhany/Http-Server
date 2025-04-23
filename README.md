##🚀 Simple HTTP Server

A lightweight and efficient HTTP server written in C++ designed for learning, experimenting, and basic web serving needs. This project demonstrates how to build a basic server from scratch, including request handling, routing, and response generation.

## 🛠️ Technologies

- C++
- POSIX Sockets
- CMake (for building)
- Multithreading with `pthread`

## 🚀 Getting Started

### 🔧 Prerequisites

- C++17 or higher
- CMake
- Linux/macOS or WSL for Windows

## Testing the Server

You can test the server using curl. Below are some examples:

1. Simple GET Request

```bash
curl -v http://localhost:4221/
```

2. Echo Request

```bash
curl -v http://localhost:4221/echo/hello
```

3. User-Agent Request
```bash
curl -v http://localhost:4221/user-agent
```

4. File Upload
```bash
curl -v -X POST http://localhost:4221/files/upload.txt -d 'Hello World'
```

5. File Download
```bash
curl -v http://localhost:4221/files/upload.txt
```

