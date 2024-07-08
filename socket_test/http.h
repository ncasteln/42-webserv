/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 02:33:30 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/07/08 06:33:04 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
# define HTTP_HPP

typedef struct s_http
{
}		t_http;


class http {
	public:
		std::string setHttp( void ) {
			std::string re("HI");
			return (re);
		}
	private:
		std::string		HTTP_VERSION;
		std::string		MSG_CODE;
		std::string		CONTENT_TYPE;
		std::string		CONTENT_LENGTH;
};

#endif
