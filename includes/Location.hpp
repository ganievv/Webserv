#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

/**
 * routing rules based on the requested URL (see NGINX)
 */

class Location
{
	/**
	 * location = /errors/404.html {}
	 * 
	 * /errors/404.html -> path
	 * 
	 */
	private:
		bool		is_internal;
		std::string	path;
		std::string	root;
		std::string alias; // (?)
	public:
};

#endif
