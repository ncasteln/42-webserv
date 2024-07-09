/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:39:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/07/09 03:24:40 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

HTTPRequest::HTTPRequest(const std::string& req) : _request(req) {}

bool HTTPRequest::isValidMethod(const std::string& mthd) {
	return (mthd == "GET" || mthd == "POST" || mthd == "HEAD");
}

bool HTTPRequest::isValidHttpVersion(const std::string& ver) {
	return (ver == "HTTP/1.1" || ver == "HTTP/1.0");
}

bool HTTPRequest::parse() {
	std::istringstream requestStream(_request);
	std::string line;

	// Parse request line
	if (!std::getline(requestStream, line)) {
		return false;
	}
	std::istringstream requestLine(line);
	if (!(requestLine >> _method >> _uri >> _version)) {
		return false;
	}

	if (!isValidMethod(_method) || !isValidHttpVersion(_version)) {
		return false;
	}

	// Parse headers
	while (std::getline(requestStream, line) && line != "\r") {
		size_t pos = line.find(":");
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
			value.erase(0, value.find_first_not_of(" "));
			headers[key] = value;
		}
	}

	return true;
}

int HTTPRequest::validate() {
	if (headers.find("Host") == headers.end()) {
		return 400;
	}
	return 200;
}

std::string HTTPRequest::getResponse() {
	int statusCode = validate();

	if (statusCode == 200) {
		return httpStatusCode(200) + "Content-Type: text/html\r\n\r\n<html><body><h1>Success</h1></body></html>";
	} else {
		return httpStatusCode(400) + "Content-Type: text/html\r\n\r\n<html><body><h1>Bad Request</h1></body></html>";
	}
}

std::string HTTPRequest::httpStatusCode(int statusCode) {
	switch (statusCode)
	{
		case 200 : return "HTTP/1.1 200 OK\r\n";
		case 400 : return "HTTP/1.1 400 Bad Request\r\n";
		case 404 : return "HTTP/1.1 404 Not Found\r\n";
		default: return "HTTP/1.1 500 Internal Server Error";
	}
}

void HTTPRequest::handleRequest(int clientSocket) {
	char buffer[1024];
	ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
	if (bytesRead < 0) {
		perror("read");
		close(clientSocket);
		return;
	}
	buffer[bytesRead] = '\0';
	_request = buffer;

	HTTPRequest httpRequest(_request);

	if (!httpRequest.parse()) {
		std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Bad Request</h1></body></html>";
		write(clientSocket, response.c_str(), response.length());
	} else {
		std::string response = httpRequest.getResponse();
		write(clientSocket, response.c_str(), response.length());
	}

	close(clientSocket);
}
