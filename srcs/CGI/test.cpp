/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:34:29 by ashirzad          #+#    #+#             */
/*   Updated: 2025/02/11 12:42:20 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void)
{
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<title>Hello World - First CGI Program</title>\n";
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	std::cout << "<h2>Hello World - This is my first CGI program</h2>\n";
	std::cout << "</body>\n";
	std::cout << "</html>\n";

	return (0);
}
