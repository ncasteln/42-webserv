/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:03:53 by ncasteln          #+#    #+#             */
/*   Updated: 2024/07/16 15:52:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_H__
# define __PARSER_H__

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>	// stat()
#include "../../include/errors.h"
#include "colors.h"

#define DEFAULT_FILE_PATH		"./conf/default.conf"

/* NUMBER OF DIRECTIVES */
#define N_SHARED_DIR	5
#define N_SERVER_DIR	3
#define N_LOCATION_DIR	3

/* SHARED DIRECTIVE DEFAULTS */
#define DEFAULT_TIMEOUT			"75"
#define DEFAULT_CLIENT_SIZE		"80"
#define DEFAULT_INDEX			"index index.html"
#define DEFAULT_AUTOINDEX		"off"
#define DEFAULT_ROOT			"./www/"

/* SERVER DIRECTIVE DEFAULTS */
#define DEFAULT_HOST			"127.0.0.1"
#define DEFAULT_PORT			"8080"
#define DEFAULT_SERVER_NAME		""

/* LOCATION DIRECTIVE DEFAULTS */
#define DEFAULT_URI				"" /* need to decide something */
#define DEFAULT_METHOD			"GET"
#define DEFAULT_CGI				"" /* need to decide something */

#define	SPACES				" \t\v\f\r"
#define	COMMENT(c)			((c) == '#')
#define	ENDVALUE(c)			((c) == ';')

enum context {
	INIT = -1,
	HTTP,
	SERVER,
	LOCATION,
	COMMENT
};

#endif /* __PARSER_H__ */
