#include "../../includes/webserv.hpp"

void	Response::testInitRequest(HttpRequest& request)
{
	request.method = "GET";
	request.path = "/";
	request.httpVersion = "HTTP/1.1";

	request.headers.insert(std::pair("Host", "localhost"));
	request.headers.insert(std::pair("From", "someuser@jmarshall.com"));
	request.headers.insert(std::pair("User-Agent", "HTTPTool/1.1"));

	request.body = "";

	request.isValid = true;
}

std::string	Response::findHeaderValue(const std::string& name,
	const std::map<std::string, std::string>& headers) const
{
	const auto& it = headers.find(name);

	std::string value = "";
	if (it != headers.end())
		value = it->second;

	return value;
}

const serverConfig&	Response::chooseServer(const HttpRequest& request,
	const std::vector<serverConfig>& servers) const
{
	std::string value = findHeaderValue("Host", request.headers);

	for (const auto& server : servers) {
		for (const auto& name : server.serverNames ) {
			if (name == value)
				return server;
		}
	}

	return servers.front();
}
