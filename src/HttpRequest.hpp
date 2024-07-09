/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 02:33:30 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/07/09 03:23:43 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>
#include <map>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>    // For read, write, close
#include <iostream>    // For std::cout, std::endl
#include <cstdio>      // For perror
#include <cstring>     // For memset
#include <sstream>     // For std::istringstream
#include <algorithm>   // For std::remove


class HTTPRequest {
public:
	HTTPRequest(const std::string& request);
	bool parse();
	int validate();
	std::string getResponse();
	void handleRequest(int clientSocket);

private:
	std::string _request;
	std::string _method;
	std::string _uri;
	std::string _version;
	std::map<std::string, std::string> headers;

	bool isValidMethod(const std::string& method);
	bool isValidHttpVersion(const std::string& version);
	std::string  httpStatusCode(int code);
};

#endif
