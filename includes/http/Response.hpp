#ifndef RESPONSE_HPP
#define RESPONSE_HPP

struct HttpRequest;

class Response
{
	private:
	public:
		void	testInitRequest(HttpRequest& request);
		std::string findHeaderValue(const std::string& name,
			const std::map<std::string, std::string>& headers) const;
		const serverConfig&	chooseServer(const HttpRequest& request,
			const std::vector<serverConfig>& servers) const;
};

#endif
