/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_prototypes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:06:46 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 04:04:40 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PROTOTYPES_H
# define IRC_PROTOTYPES_H

#include "irc.h"

typedef struct	s_client	t_client;

/*
**	client/client_messages.c
*/
int		send_message_to_server(int sockfd);
int		recv_message_from_server(int sockfd);

/*
**	client/client_main.c
*/
static int	init_client_socket(int port, char *address);
static int 	run_client(int sockfd, int max_fd, fd_set client_fds);
// int			main(int ac, char **av);


/*
**	server/client.c
*/
void		new_client(void);

/*
**	server/init.c
*/
t_client	*init_client(int sockfd, char *nick);
int			init_server(void);
int			init_server_socket(int port);

/*
**	server/server_process.c
*/
int			process_request(int clientfd, char *msg);
void		process_data(int clientfd);

/*
**	server/server_send_message.c
*/
void		send_welcome_message(int clientfd);
int			send_message(int clientfd, char *msg);

/*
**	server/server_main.c
*/
static		int	run_server(void);
// int			main(int ac, char **av);

/*
**	server/requests
*/
void		request_colors_list(int fd, char *msg);
void		request_color(int fd, char *msg);
void		request_fd(int fd, char *msg);
void		request_nick(int fd, char *msg);
void		request_room(int fd, char *msg);

/*
**	parse.c
*/
int			parse_args_serv(int ac, char **av);
int			parse_args_client(int ac, char **av);

/*
**	tools.c
*/
int			error(int errnb, char *msg, bool ifexit);
#endif
