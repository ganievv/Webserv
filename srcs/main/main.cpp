#include "../../includes/webserv.hpp"

int	main(int argc, char **argv)
{
	(void)argc;

	ConfigParser	parser;
	Sockets			server_sockets;
	Poller			poller;
	Connection		connection;

	try {
		//parser.tester(argv[1]); //for printing (has dup check call inside)
		parser.parseConfigFile(argv[1]); //no prints, needs dup check called after
		parser.checkDuplicateServer();

		server_sockets.initSockets(parser.servers);
		poller.initPoll(server_sockets.server_fds);

		for (;;) {
			poller.processPoll();

			// check which fds in poll_fds are ready
			for (int i = 0; i < poller.nfds; ++i) {

				// POLLERR, POLLHUP, POLLNVAL

				if (!(poller.poll_fds[i].revents & POLLIN)) continue;

				bool is_server = connection.handleServerFd(i, poller,
						server_sockets.server_fds);
				if (!is_server) {
					//read data from the client socket (poller.poll_fds[i].fd)
					//alalize request
					//form response
					//send response
					connection.handleClientFd(poller.poll_fds[i].fd); // test for printing the request data
				}
			}
		}

	} catch (const std::exception& e) {
		std::cerr << "caught error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
