/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AConf.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:24:02 by ncasteln          #+#    #+#             */
/*   Updated: 2024/08/06 12:55:52 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AConf.hpp"

AConf::AConf( std::map<std::string, std::string> settings, context type ): _type(type), _settings(settings) {
	setSharedSettingsDefaults();
};
AConf::AConf( context type ): _type(type) {
	setSharedSettingsDefaults();
};
const std::map<std::string, std::string> AConf::getSettings( void ) const { return (_settings); };

const std::string AConf::sharedSettings[N_SHARED_DIR] = {
	"keepalive_timeout",
	"client_body_buffer_size",
	"root",
	"index",
	"autoindex"
};

void AConf::setSharedSettingsDefaults( void ) {
	if (_settings.find("keepalive_timeout") == _settings.end()) _settings["keepalive_timeout"] = DEFAULT_TIMEOUT;
	if (_settings.find("client_body_buffer_size") == _settings.end()) _settings["client_body_buffer_size"] = DEFAULT_CLIENT_SIZE;
	if (_settings.find("root") == _settings.end()) _settings["index"] = DEFAULT_INDEX;
	if (_settings.find("index") == _settings.end()) _settings["autoindex"] = DEFAULT_AUTOINDEX;
	if (_settings.find("autoindex") == _settings.end()) _settings["root"] = DEFAULT_ROOT;
};

enum conf_err AConf::checkSharedSettings( void ) {
	// TIMEOUT			"75"				: set a limit?
	// CLIENT_SIZE		"80"				: set a limit?
	if (_settings["autoindex"] != "off" && _settings["autoindex"] != "on") return (E_AUTOINDEX);
	if (!isValidNumber("keepalive_timeout", _settings["keepalive_timeout"])) return (E_TIMEOUT);
	if (!isValidNumber("client_body_buffer_size", _settings["client_body_buffer_size"])) return (E_CLIENTSIZE);
	return (CONF_SUCCESS);
}
