/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:30:53 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 14:16:21 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <errno.h>
# include <term.h>
# include <curses.h>
# include "libft.h"

# include "irc_prototypes.h" 

# define	BUFF_SIZE		64
# define	SERVPASSWD		"polcia"
# define 	DEF_COLOR		CYAN
# define	SERV_BUFF_SIZE	2048

typedef struct	s_client
{
	int		fd;
	char	*color;
	char	*nick;
	char	*room;
}				t_client;

typedef struct	s_server
{
	int		serverfd;
	int		max_fd;
	char	*buff;
	t_node	*clients;
	t_node	*rooms;
	fd_set	client_fds;
}				t_server;

typedef struct	s_request
{
	char	*request;
	int		len;
	void	(*fct)(int, char *);
}				t_request;

extern t_client *g_clients[FD_SETSIZE];
extern t_server	g_server;

/*
**	struct sockaddr_in
**	{
**		sa_family_t sin_family; 		ddress Family/rodzina adresów
**		uint16_t sin_port;				Port number/numer portu
**		struct in_addr sin_addr;		Internet address/adres internetowy
**		unsigned char sin_zero[8];		Pad bytes/ dla zachowania rozmiaru struct sockaddr
**	};
**
**	my_addr.sin_port = 0; // wybierz losowo nieu˙zywany port
**	my_addr.sin_addr.s_addr = INADDR_ANY; // u˙zyj mojego adresu IP
**
**	FD_SETSIZE is 1024
*/

#endif
