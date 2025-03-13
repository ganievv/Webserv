#include <iostream>
#include <fstream>
#include <sys/stat.h>

int main(void)
{
	std::string content = "Content-Pathfile=name";

	int f = content.find("?");
	std::cout << content.substr(0, f) << std::endl;
}
