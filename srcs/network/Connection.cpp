#include "../../includes/webserv.hpp"

bool	Connection::isServerSocket(int fd, const std::vector<int>& server_fds)
{
	const auto& it = std::find(server_fds.begin(), server_fds.end(), fd);

	return it != server_fds.end();
}

bool	Connection::handleServerFd(int pollfd_i, Poller& poller,
	const std::vector<int>& server_fds)
{
	int fd = poller.poll_fds[pollfd_i].fd;

	if (isServerSocket(fd, server_fds)) {
		for (;;) {

			if (poller.nfds >= Poller::MAX_FDS_POLL)
				break;

			int client_fd = accept(fd, nullptr, nullptr);

			if (client_fd == -1) {
				// EAGAIN or EWOULDBLOCK -> no pending connections are present
				if (errno != EAGAIN && errno != EWOULDBLOCK)
					error_exit("failed to call accept", "");
				break;
			}

			poller.poll_fds[poller.nfds].fd = client_fd;
			poller.poll_fds[poller.nfds].events = POLLIN;
			poller.nfds++;
		}
		return true;
	}
	return false;
}

void	Connection::handleClientFd(int fd)
{
	char buff[1000];
	for (;;) {
		int res = recv(fd, &buff, sizeof(buff), 0);
		if (res == -1)
			break;
		if (res == 0) {
			//delete 'pollfd' from the 'poll_fds' array
		}
		std::cout << buff << std::endl;
		break;
	}
}
