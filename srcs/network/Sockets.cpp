#include "../../includes/webserv.hpp"

unsigned short	Sockets::convertStrToUShort(const std::string& s)
{
	unsigned short	nbr;
	unsigned long	temp = std::stoul(s);

	if (temp > std::numeric_limits<unsigned short>::max())
		error_exit("failed to convert std::string to unsigned short nbr", "");

	nbr = static_cast<unsigned short>(temp);

	return nbr;
}

void	error_exit(const std::string& msg, const std::string& server_name)
{
	std::cerr << msg << (!server_name.empty()
		? " (server name: " + server_name + ")" : ".") << std::endl;
	std::exit(EXIT_FAILURE);
}

void	Sockets::setNonblockMode(int fd, const std::string& server_name)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		error_exit("failed to SET the O_NONBLOCK flag for a socket",
			server_name);
}

struct in_addr	Sockets::convertStrIpToBinIP(std::string& ip_str, const serverConfig& server)
{
	struct addrinfo hints, *res = nullptr;
	std::memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICHOST;

	int status = getaddrinfo(ip_str.c_str(), server.port.c_str(), &hints, &res);
	if (status != 0)
	{
		error_exit(std::string("getaddrinfo error: ") + gai_strerror(status),
			server.serverNames.front());
	}

	struct in_addr bin_addr = ((struct sockaddr_in*)(res->ai_addr))->sin_addr;

	freeaddrinfo(res);
	return bin_addr;
}

void	Sockets::bindSocket(int sock_fd, const serverConfig& server)
{
	struct sockaddr_in	sock_addr;

	std::memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;

	unsigned short server_port = convertStrToUShort(server.port);
	sock_addr.sin_port = htons(server_port);

	std::string str_ip = (server.host.empty() ? "0.0.0.0" : server.host);

	sock_addr.sin_addr = convertStrIpToBinIP(str_ip, server);

	if (bind(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
		error_exit("failed to bind a socket", server.serverNames.front());
}

void	Sockets::initSockets(std::vector<serverConfig>& servers)
{
	for (const auto& server : servers) {

		/*create a socket*/
		int	fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd == -1)
			error_exit("failed to create a socket", server.serverNames.front());

		/**
		 * allow the socket to be reuseable
		 */
		int	on = 1;
		int res = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (res == -1)
			error_exit("failed to set the SO_REUSEADDR option for a socket",
				server.serverNames.front());

		/**
		 * set the socket to be nonblocking;
		 * 
		 * all of the sockets for the incoming connections
		 * are also nonblocking because they inherit that state
		 * from the listening socket - is it correct ?
		 */
		setNonblockMode(fd, server.serverNames.front());

		/**
		 * bind the socket
		 */
		bindSocket(fd, server);

		/**
		 * set the listen back log
		 */
		if (listen(fd, BACKLOG) == -1)
			error_exit("failed to listen on socket", server.serverNames.front());

		/**
		 * save the socket
		 */
		server_fds.push_back(fd);
	}
}
