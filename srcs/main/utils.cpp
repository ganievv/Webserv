#include "../../includes/webserv.hpp"

std::string getConfigPath(int argc, char **argv)
{
	std::string	path = "./webserv.conf"; // define a default path

	if (argc > 1)
		path = argv[1];

	return path;
}
