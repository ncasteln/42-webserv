/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:39:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/07/16 23:02:42 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

HTTPRequest::HTTPRequest(std::map<std::string, std::string> serverConfig) :
 _request(""),
 _method(""),
 _uri(""),
 _version(""),
 _body(""),
 _serverConfig(serverConfig) {}

bool HTTPRequest::isValidMethod(const std::string& mthd) {
	return (mthd == "GET" || mthd == "POST" || mthd == "HEAD");
}

bool HTTPRequest::isValidHttpVersion(const std::string& ver) {
	return (ver == "HTTP/1.1" || ver == "HTTP/1.0");
}

bool HTTPRequest::parse() {
	std::istringstream	requestStream(_request);
	std::string			line;

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

	// std::cout << RED "HIIIII\n" RESET;
	// std::istringstream streamTest(_request);
	// std::string stringTest;
	//     std::ofstream outFile("navid");
	// while (std::getline(streamTest, stringTest)){
	// 	std::cout  << ORG << stringTest << RESET<< std::endl;
    //     // Manually escape special characters
	// 	if (outFile.is_open()) {
	// 		for (std::string::size_type i = 0; i < stringTest.size(); ++i) {
    //         	char c = stringTest[i];
	// 			switch (c) {
	// 				case '\r':
	// 					outFile << "\\r";
	// 					break;
	// 				case '\n':
	// 					outFile << "\\n";
	// 					break;
	// 				case '\t':
	// 					outFile << "\\t";
	// 					break;
	// 				case '\v':
	// 					outFile << "\\v";
	// 					break;
	// 				case '\f':
	// 					outFile << "\\f";
	// 					break;
	// 				case ' ':
	// 					outFile << "' '";
	// 					break;
	// 				default:
	// 					outFile << c;
	// 			}
	// 		}
	// 	}
	// }
    // outFile.close();
	// exit(1);
	
	_headers["method"] = _method;
	_headers["uri"] = _uri;
	_headers["version"] = _version;

	// Parse headers
	while (std::getline(requestStream, line) && line != "\r") {
		size_t pos = line.find(":");
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
			value.erase(0, value.find_first_not_of(" "));
			_headers[key] = value;
		}
	}

	std::cout << ORG "parse headers as below:\n" << RESET;
	std::map<std::string, std::string>::iterator itr = _headers.begin();
	for(; itr != _headers.end(); itr++)
		std::cout << MAGENTA << itr->first << ":" BLUE << itr->second << RESET << std::endl;

	std::cout << ORG "parse server config as below:\n" << RESET;
	std::map<std::string, std::string>::iterator itrr = _serverConfig.begin();
	for(; itrr != _serverConfig.end(); itrr++)
		std::cout << MAGENTA << itrr->first << "--->" ORG << itrr->second << RESET << std::endl;

	return true;
}

int HTTPRequest::validate() {
	if (_headers.find("Host") == _headers.end()) {
		return 400;
	}
	return 200;
}

std::string HTTPRequest::getResponse() {
	int statusCode = validate();

    if (statusCode != 200) {
        return httpStatusCode(400) + "Content-Type: text/html\r\n\r\n<html><body><h1>Bad Request</h1></body></html>";
    }

	if (_serverConfig.find("If-None-Match: ") != _serverConfig.end()) {
		return httpStatusCode(304);
	}

    if (_method == "GET" || _method == "HEAD") {
        return handleGet();
    } else if (_method == "POST") {
        return handlePost();
    } else if (_method == "DELETE") {
        return handleDelete();
    }
    return httpStatusCode(405) + "Content-Type: text/html\r\n\r\n<html><body><h1>Method Not Allowed</h1></body></html>";

}

std::string HTTPRequest::handleGet() {
	std::ostringstream headers;
	if (_uri == "/" || _uri == "/index.html" || _uri == "/favicon.ico")
	{
		std::cout << RED "inside Get ......." RESET << std::endl;
		std::string path = "./src/index.html";
		std::string readHtml = readHtmlFile(path);

		std::string strETag = generateETag(path);

		headers << httpStatusCode(200);
		headers << "Server: " + _serverConfig["server_name"];
		headers << "\r\nContent-Type: text/html\r\n";
		headers << "Content-Length: " << readHtml.size() << "\r\n";
		headers << "ETag: " << strETag << "\r\n";
		headers << "Accept-Ranges: bytes\r\n\r\n";
		headers << readHtml;
    	return headers.str();
	}
	else
		return (std::string(STATUS_400));
    // Placeholder implementation
    // return httpStatusCode(200) + "Content-Type: text/html\r\n\r\n<html><body><h1>GET Request Received</h1></body></html>";
}

std::string HTTPRequest::handlePost() {
    // Placeholder implementation
    return httpStatusCode(200) + "Content-Type: text/html\r\n\r\n<html><body><h1>POST Request Received</h1></body></html>";
}

std::string HTTPRequest::handleDelete() {
    // Placeholder implementation
    return httpStatusCode(200) + "Content-Type: text/html\r\n\r\n<html><body><h1>DELETE Request Received</h1></body></html>";
}

std::string HTTPRequest::httpStatusCode(int statusCode) {
    switch (statusCode) {
        case 200: return (std::string(STATUS_200));
        case 400: return (std::string(STATUS_400));
        case 404: return (std::string(STATUS_404));
        case 405: return (std::string(STATUS_405));
		case 304: return (std::string(STATUS_304));
        default: return (std::string(STATUS_500));
    }
}

void HTTPRequest::handleRequest(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0) {
		throw Exception("Receive Failed", RECEIVE_FAILED);
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';
    _request = buffer;
	// std::cout << ORG "received request as below headers:\n" << CYAN << buffer << RESET << std::endl;

    if (!parse()) {
        std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Bad Request</h1></body></html>";
        send(clientSocket, response.c_str(), response.length(), 0);
    } else {
        std::string response = getResponse();
        send(clientSocket, response.c_str(), response.length(), 0);
    }

    close(clientSocket);
}

std::string HTTPRequest::readHtmlFile(std::string path) {
	std::ifstream fileStream(path.c_str());
	if (fileStream.is_open())
		std::cout << "file is open\n";
	else{
		perror("error:"); //check if the error method is addmited
		return ("");
	}
	std::ostringstream ss;
	ss << fileStream.rdbuf();
	return ss.str();
}

std::string generateETag(const std::string& filePath) {
    struct stat fileInfo;

    if (stat(filePath.c_str(), &fileInfo) != 0) {
        std::cerr << "Error getting file information: " << filePath << std::endl; //check if the error method is addmited
        return "";
    }

    std::ostringstream etag;
    etag << "\"" << fileInfo.st_mtime << "-" << fileInfo.st_size << "\"";

    return etag.str();
}