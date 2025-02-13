#include "../../includes/webserv.hpp"

int	main(int argc, char **argv)
{
	ConfigParser	parser;
	Sockets			server_sockets;
	Poller			poller;
	Connection		connection;

	std::string	config_path = getConfigPath(argc, argv);
	std::map<int, std::string> status_code_info;
	initStatusCodeInfo(status_code_info);

	try {
		// parser.tester(config_path); //for printing (has checking call inside)
		parser.parseConfigFile(config_path); //no prints, needs checking called after
		parser.checkingFunction();

		// testParseHttpRequest(); //prints the tests for HTTP parsing, it now uses sokcets and file descriptor instead of rawString

		server_sockets.initSockets(parser.servers);
		poller.initPoll(server_sockets.server_fds);

		for (;;) {
			poller.processPoll();

			// check which fds in poll_fds are ready
			for (int i = 0; i < poller.nfds; ++i) {

				// POLLERR, POLLHUP, POLLNVAL

				if (!(poller.poll_fds[i].revents & POLLIN)) continue;

				if (connection.isServerFd(poller.poll_fds[i].fd,
						server_sockets.server_fds)) {
					connection.handleServerFd(poller.poll_fds[i].fd, poller);
				}
				else {
					//read data from the client socket (poller.poll_fds[i].fd)
					//alalize request
					//form response
					//send response
					connection.handleClientFd(poller.poll_fds[i]); // test for printing the request data
					//HttpRequest request;
					//Response response;
					//response.testInitRequest(request);
					//response.chooseServer(poller.poll_fds[i].fd, request, parser.servers);
					//response.formResponse(request, status_code_info);				
					//response.sendResponse(poller.poll_fds[i].fd);
					//std::cout << "\nresponse is send\n";
				}
			}
		}

	} catch (const std::exception& e) {
		std::cerr << "caught error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
