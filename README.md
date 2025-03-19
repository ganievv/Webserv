# Webserv

## Introduction
Webserv is a custom HTTP server written in **C++17** as part of the 42 school curriculum. The goal of this project is to understand and implement core HTTP functionalities while maintaining compliance with HTTP/1.1 standards. This server can handle multiple clients, process HTTP requests, and serve static files.

## Features
- Serves static websites
- Supports **GET, POST, and DELETE** methods
- Handles **CGI execution** (Python scripts)
- Implements **non-blocking I/O** using `poll()`
- Supports **multipart file uploads**
- Provides configurable error pages
- Allows custom **configuration file** to define server behavior
- Manages multiple **virtual servers on different ports**

## Installation
### Prerequisites
Ensure you have the following installed on your system:
- **C++17 compliant compiler**
- **Make**
- **POSIX-compliant system** (Linux, MacOS)

### Compilation
Clone the repository and build the project using:
```bash
make
```
This will generate the `webserv` executable.

## Usage
### Running the Server
```bash
./webserv [configuration file]
```
If no configuration file is provided, a default one will be used.

### Example Configuration File
The server behavior can be customized using a configuration file similar to an Nginx config:
```nginx
server {
    listen 8080;
    server_name localhost;
    root ./website;

    client_max_body_size 10M;

    error_page 404 /errors/404.html;

    location / {
        index index.html;
    }

    location /cgi-bin {
        limit_except GET POST DELETE;
    }

    location /errors {
      return 301 /;
    }
}
```

## Features Breakdown
### HTTP Methods Supported
- **GET**: Retrieve resources from the server
- **POST**: Submit data to the server (e.g., file uploads)
- **DELETE**: Remove specified resources

### Non-Blocking I/O
- Uses **poll()** to handle multiple clients efficiently
- No blocking operations allowed (except for reading configuration files at startup)

### CGI Execution
- Supports CGI scripts based on file extensions (`.py`)
- Handles input and output properly using environment variables
- Ensures proper execution within a secure directory

### File Uploads
- Supports multipart form-data uploads
- Configurable upload directory via the configuration file

### Error Handling
- Custom error pages can be configured
- Default error pages provided for missing configurations

### Multi-Port & Virtual Hosts
- Can serve multiple domains and subdomains on different ports
- The first server entry for a given host/port acts as the default

## Testing
### Using a Web Browser
Once the server is running, open a web browser and navigate to:
```
http://localhost:8080
```

### Using `curl`
```bash
curl -X GET http://localhost:8080
```

---
**Maintainers:**  
- Semen Ganiev

