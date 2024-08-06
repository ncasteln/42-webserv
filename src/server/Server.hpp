/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:10:43 by fahmadia          #+#    #+#             */
/*   Updated: 2024/08/05 20:17:25 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <string>
#include <netdb.h>
#include <fcntl.h>
#include <stdexcept>
#include <vector>
#include <arpa/inet.h>
#include <poll.h>
#include <map>
#include <fstream>
#include <time.h>
#include "../request/HttpRequest.hpp"
#include "../request/HttpResponse.hpp"
#include <sstream>
#include "Exception.hpp"
#include "../sockets/listening-socket/ListeningSocket.hpp"
#include "../sockets/connected-socket/ConnectedSocket.hpp"
#include "../server/Server.hpp"
#include "HttpRequest.hpp"

#define MAX_CONNECTIONS 40

class Server
{
private:
	const std::string _port;
	std::vector<std::string> _serverNames;
	std::vector<std::string> _roots;
	std::vector<std::string> _indexes;
	int _keepAliveTimeout;
	// std::vector<std::string> _keepaliveTimeouts;
	// std::vector<std::string> _autoindexes;
	// std::vector<std::string> _clientSizes;
	ListeningSocket _listeningSocket;
	std::map<int, ConnectedSocket> _connectedSockets;
	HTTPRequest _httpReq; //navid_code
	HTTPResponse _httpResp; //navid_code

	Server(void);
	Server &operator=(Server const &rhs);
	
	std::string readHtmlFile(std::string path);

public:
	Server(std::map<std::string, std::string> settings);
	~Server(void);
	Server(const Server &other);

	ListeningSocket const &getListeningSocket(void) const;
	const std::string getPort(void) const;
	std::map<int, ConnectedSocket> &getConnectedSockets(void);
	HTTPRequest & getHttpReq(); //navid_code
	HTTPResponse & getHttpResp(); //navid_code
	int getKeepAliveTimeout(void) const;

	void setKeepAliveTimeout(int keepAliveTimeout);

	void addServerName(std::string newName);
	void addRoot(std::string newRoot);
	void addIndex(std::string newIndex);
	void setPortAvailable(void);
	void bindSocket(void) const;
	void listenToRequests(void) const;
	int acceptFirstRequestInQueue(void);
	void printConnectedSockets(void);
};

#endif
