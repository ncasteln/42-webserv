/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:54:45 by ncasteln          #+#    #+#             */
/*   Updated: 2024/08/03 16:50:14 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __POLL_HPP__
#define __POLL_HPP__

#include "Server.hpp"
#include "Parser.hpp"

class Poll
{
public:
	Poll(const Parser &configuration);
	~Poll(void);

	void init(void);
	void start(void);

private:
	std::vector<Server> _serverList;
	nfds_t _currentMonitored;
	size_t _totalMonitored;
	struct pollfd *_totalFds;
	int _eventsNum;

	std::map<int, int> _POLLINCheck; //navid_check

	void createServers(const Parser &configuration);
	bool mergeServerWithSamePort(std::map<std::string, std::string> serverConf);
	void initFds(void);

	void handleEvent(nfds_t i);
	void handleListeningEvent(size_t i, Server &s);
	void handleConnectedEvent(size_t i, Server &s);
	void addConnectedSocketToMonitoredList(int connectedSocketFd);
	void removeClosedSocketsFromMap(Server &s);
	void removeClosedSocketsFromPollFds(void);
	void printCurrentPollFds(void);
	void printAllPollFds(void);

	// UN-USED CONSTRUCTORS
	Poll(void);
	Poll(const Poll &);
	Poll &operator=(const Poll &);
};

#endif /* __POLL_HPP__ */
