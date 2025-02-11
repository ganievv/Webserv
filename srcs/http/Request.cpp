#include "../../includes/webserv.hpp"

//keep in mind potential timeout
//potential \r\n\r\n missing
//no content length may cause issues

//have to rewrite handleClientFd potentially

//create checker for parseHttpRequest and then try to implement it through sockets

/*
To do: 
DONE 1. Make all header names, but not values follow the same case format:
	-First letter -> Uppercase
	-Everything else -> Lowercase
	(Host, From, ...)
*/

HttpRequest	parseHttpRequest(const std::string &rawRequest) {
	std::istringstream	stream(rawRequest);
	HttpRequest	request;
	std::string	line;

	//check for valid request line
	if (!std::getline(stream, line) || line.empty()) {
		request.isValid = false;
		request.errorMessage = "Invalid or empty request line.";
		return request;
	}

	//get request line
	std::istringstream	lineStream(line);
	if (!(lineStream >> request.method >> request.path >> request.httpVersion)) {
		request.isValid = false;
		request.errorMessage = "Invalid request line.";
		return request;
	}

	//check http method
	static const std::set<std::string>	validMethods = {"GET", "POST", "DELETE"};
	if (validMethods.find(request.method) == validMethods.end()) {
		request.isValid = false;
		request.errorMessage = "Invalid HTTP method: " + request.method;
		return request;
	}

	//check http version									//R: define a string without having to escape special characters like backslashes.
	if (!std::regex_match(request.httpVersion, std::regex(R"(HTTP\/\d\.\d)"))) { //matches strings that start with "HTTP/", then a digit, a dot, and another digit
		request.isValid = false;
		request.errorMessage = "Invalid HTTP version: " + request.httpVersion;
		return request;
	}

	//read headers
	while (std::getline(stream, line) && line != "\r") {
		size_t	colonPos = line.find(':');

		if (colonPos == std::string::npos) {
			request.isValid = false;
			request.errorMessage = "Invalid header: " + line;
			return request;
		}

		std::string	key = line.substr(0, colonPos);
		std::string	val = line.substr(colonPos + 1);

		//trim whitespaces
		key.erase(0, key.find_first_not_of(" \t")); //trim leading whitespaces
		key.erase(key.find_last_not_of(" \t") + 1); // trim trailing whitespaces
		val.erase(0, val.find_first_not_of(" \t"));
		val.erase(val.find_last_not_of(" \t") + 1);

		key[0] = std::toupper(key[0]); //this ugly bit of code makes first letters capitalized, while keeping everything else lowercase
		size_t j = 0;
		for (size_t i = 1; i < key.size() - 1; i++) {
			if (key[i] == '-' && i + 1 < key.size()) {
					key[i + 1] = std::toupper(key[i + 1]);
					j = i + 1;
			} else if (j != i) {
				key[i] = std::tolower(key[i]);
			}
		}

		request.headers[key] = val;
	}

	//handle body if there is content-length
	if (request.headers.find("Content-Length") != request.headers.end()) { //checks if "Content-Length" header was found.
		try {
			int	contentLen = std::stoi(request.headers.at("Content-Length")); // check .at!!! returns CL and throws an exception if the key is not found
			if (contentLen == 0) { //may be unnecessary
				request.body = "";
			} else if (contentLen < 0) {
				request.isValid = false;
				request.errorMessage = "Invalid Content Length: " + std::to_string(contentLen);
				return request;
			}

			//extract body based on contentLen
			size_t	bodyStart = rawRequest.find("\r\n\r\n") + 4;
			if (bodyStart + contentLen > rawRequest.length()) { //prevents a potential out-of-bounds read
				request.isValid = false;
				request.errorMessage = "Content Length mismatch. Expected " + std::to_string(contentLen) +
						", but only " + std::to_string(rawRequest.length() - bodyStart) + " bytes available.";
				return request;
			}
			request.body = rawRequest.substr(bodyStart, contentLen);

		} catch (const std::exception &e) {
			request.isValid = false;
			request.errorMessage = "Invalid Content-Length format.";
			return request;
		}
	}
	request.isValid = true; //should be redundant
	return request;
}

int	httpRequestTester(void) {
	return 0;
}