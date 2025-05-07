/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:58:19 by bposa             #+#    #+#             */
/*   Updated: 2025/05/05 17:05:04 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

while (serverFd_.accept(clientSock) == false) { //can be while(maxRetries_ private const) or similar
	switch (errno)
	{
		case EINTR:
			continue;
		#if EAGAIN != EWOULDBLOCK
		case EAGAIN:
		#endif
		case EWOULDBLOCK:
		case ECONNABORTED:
		case ENETDOWN:
		case EPROTO:
		case ENOPROTOOPT:
		case EHOSTDOWN:
		case ENONET:
		case EHOSTUNREACH:
		case EOPNOTSUPP:
		case ENETUNREACH:
			return;
		default:
			throw std::system_error(errno, std::generic_category(), "accept() failed");// Fatal errors
	}
};