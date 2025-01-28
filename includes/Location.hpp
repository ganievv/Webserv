#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>

/**
 * routing rules based on the requested URL (see NGINX)
 */

class Location
{
	/**
	 * location /htmls/errors {}
	 * 
	 * /htmls/errors -> route
	 * 
	 */
	private:
		bool		is_internal; // (?)
		std::string	path;
		std::string	root;
		std::string alias;

		/**
		 * "Define a list of accepted HTTP methods for the route"
		 * 
		 * limit_except GET POST DELETE;
		 * 
		 * (?)
		 * bool	can_get;	|
		 * bool	can_post;	|
		 * bool	can_delete;	|-> by default all false
		 * 
		 */

		/**
		 * "Define a HTTP redirection"
		 * 
		 * return 301 /new_path;
		 */
		bool		is_redir;
		int			status_code;
		std::string	new_path;

		bool		autoindex;

		std::string	index;

	public:
};

#endif
