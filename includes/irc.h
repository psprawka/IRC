/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:30:53 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 11:16:29 by psprawka         ###   ########.fr       */
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

# define	SERVPASSWD		"polcia"
# define 	DEF_COLOR		CYAN
# define	BUFF_SIZE		2048
# define	SERV_BUFF_SIZE	2048

typedef struct	s_client
{
	int		fd;
	char	*color;
	char	*nick;
	char	*channel;
}				t_client;

typedef struct	s_server
{
	int		serverfd;
	int		max_fd;
	char	*buff;
	t_node	*clients;
	t_node	*channels;
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

//	todo:
//	-> add termcaps;								1-2h
//	-> leaks;										1h
//	-> norminette;									10mins
//	-> quit option;									20mins
//	-> connect option;								30mins
//	-> time option;									30mins
//	-> list option (lists all channels);			10mins
//	-> write strjoin_infinity;						30-60mins
//	-> circular buffer;								30-60mins
//	-> maybe add modes sometime in teh future;		5h

#endif
