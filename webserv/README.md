*This project has been created as part of the 42 curriculum by mnjie-me and iranieri.*

# Webserv

## Description

Webserv is a simplified HTTP server inspired by NGINX, developed in C++98 as part of the 42 curriculum. The goal is to implement a fully functional HTTP/1.1 server capable of handling multiple simultaneous clients, serving static files, executing CGI scripts, and processing different HTTP methods.

Concepts learned and implemented:

1. TCP socket communication
2. HTTP request parsing
3. Static file serving
4. CGI execution
5. Multiple client handling
6. Configuration file parsing
7. HTTP response generation

## Instructions

### Installation

* Clone the repository

```bash
git clone https://...
```

### Compilation

* Enter the repository and compile

```bash
cd Webserv
make
```

### Run

```bash
./Webserv config.conf
```

### Test

* Open a different terminal and use one of the following:

```bash
nc localhost 8080
```
```bash
curl -v http://localhost:8080
```

* Write the request (first two lines are mandatory):
  * Line 1: `Method | route | HTTP version` (e.g. `GET / HTTP/1.1`)
  * Line 2: `Host: localhost`

## Configuration

The server is configured via a `.conf` file. A basic example:

```nginx
server {
    listen 8080;
    server_name localhost;

    location / {
        methods GET;
        root /path/to/www;
        index index.html;
        autoindex off;
    }

    location /post_body {
        methods POST;
        client_max_body_size 100;
    }

    location /directory {
        methods GET POST;
        root /path/to/YoupiBanane;
        index youpi.bad_extension;
        autoindex off;
        cgi_pass .bla /path/to/cgi_tester;
    }
}
```

Key directives:
- `listen`: port the server listens on
- `methods`: allowed HTTP methods for the location
- `root`: root directory for file serving
- `index`: default file when no file is requested
- `autoindex`: enable/disable directory listing
- `client_max_body_size`: maximum allowed request body size in bytes
- `cgi_pass`: file extension and executable for CGI handling
- `return`: HTTP redirect (e.g. `return 301 https://example.com`)

## Resources

- [MDN HTTP Guide](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides)
- [RFC 7230 - HTTP/1.1 Message Syntax](https://datatracker.ietf.org/doc/html/rfc7230)

### AI Usage

AI tools were used during the development of this project in the following ways:
- **Debugging**: resolving HTTP parsing edge cases and understanding 4xx/5xx status code behavior
- **Configuration**: understanding NGINX-style config structure and virtual hosting
- **Documentation**: clarifying HTTP/1.1 spec details from RFC 7230 where the standard was ambiguous

AI was used as a support tool to resolve doubts, not to generate core project logic.