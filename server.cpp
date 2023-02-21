/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:15:09 by ayassin           #+#    #+#             */
/*   Updated: 2023/02/21 19:05:55 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <iostream> // For cout
#include <unistd.h> // For read
// https://ncona.com/2019/04/building-a-simple-server-with-cpp/
// https://www.geeksforgeeks.org/socket-programming-cc/
int main()
{
	int			sockfd;
	sockaddr_in	sockaddr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
    	exit(EXIT_FAILURE);
	}
	
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = (in_port_t) htonl(777);
	if (listen(sockfd, 10) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    	exit(EXIT_FAILURE);
	}

	socklen_t addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr *)&sockaddr, &addrlen);
	if (connection < 0)
	{
		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    	exit(EXIT_FAILURE);
	}

	std::cout << "Success" << errno << std::endl;

	char buff[100];
	int bytesRead = read(connection, buff, 100);
	if (bytesRead < 0)
	{
		std::cout << "Failed to read connection. errno: " << errno << std::endl;
    	exit(EXIT_FAILURE);
	}
	std::cout << "The message is: " << buff;
	
	std::string response = "Good talking to you\n";
	send(connection, response.c_str(), response.size(), 0);

	close(connection);
	close(sockfd);
}