#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Poller;

class Connection
{
	private:
		bool	isServerSocket(int fd, const std::vector<int>& server_fds);
	public:
		bool	handleServerFd(int pollfd_i, Poller& poller,
					const std::vector<int>& server_fds);
		void	handleClientFd(int fd);
};

#endif
