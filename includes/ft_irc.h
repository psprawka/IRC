/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:30:53 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/23 15:47:57 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
# define FT_IRC_H

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

# define	BUFF_SIZE		64
# define	MAX_CLIENT_FD	10
# define	SERVPASSWD		"polcia"
# define 	DEF_COLOR		CYAN

typedef struct	s_client
{
	int		sockfd;
	char	*color;
	char	*name;
	char	*room;
}				t_client;

/*
**	server_parse.c
*/
void	error(int errnb, char *msg, bool ifexit);
void	parse_args_serv(int ac, char **av);
void	parse_args_client(int ac, char **av);

/*
**	server_process.c
*/
void	process_data(int currfd, int sockfd, fd_set *client_fds);

/*
**	server.c
*/
void	check_select_fds(fd_set *client_fds, int sockfd);
void	runserver(fd_set client_fds, int sockfd);
int		server_socket(int port);
int		main(int ac, char **av);

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
