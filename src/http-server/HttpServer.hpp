/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:10:43 by fahmadia          #+#    #+#             */
/*   Updated: 2024/07/09 00:48:37 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_SERVER_HPP
# define HTTP_SERVER_HPP

# include <string>
# include <netdb.h>
# include <stdexcept>
# include <vector>
#include <arpa/inet.h>
# include "Exception.hpp"
# include "ListeningSocket.hpp"
# include "ConnectedSocket.hpp"
# include "../HttpRequest.hpp"

class HttpServer {
	private:
		ListeningSocket _listeningSocket;
		std::vector<ConnectedSocket> _connectedSockets;

	public:
		HttpServer(void);
		HttpServer(int maxIncomingConnections, std::string const &ip, std::string const &port);
		HttpServer(HttpServer const &other);
		HttpServer &operator=(HttpServer const &rhs);
		~HttpServer(void);

		ListeningSocket const &getListeningSocket(void) const;
		
		void printConnectedSockets(void);

		void setPortAvailable(void);
		void bindSocket(void) const;
		void listenToRequests(void) const;
		void acceptFirstRequestInQueue(void);
};


#endif
