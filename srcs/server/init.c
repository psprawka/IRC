/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:13:04 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 14:13:17 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_client	*init_client(int sockfd, char *nick)
{
	t_client *new;

	new = (t_client *)ft_strnew(sizeof(t_client));
	new->nick = nick;
	new->fd = sockfd;
	new->color = DEF_COLOR;
	new->room = NULL;
	return (new);	
}

int		init_server(void)
{
	if (!(g_server.buff = ft_strnew(SERV_BUFF_SIZE)))
		return (error(0, "Ft_strnew", true));
	return (EXIT_SUCCESS); 
}

int		init_server_socket(int port)
{
	int					opt;
	int					sockfd;
	struct protoent		*protocol;
	struct sockaddr_in	server_addr;
	
	opt = true;
	protocol = getprotobyname("TCP");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
		return (error(0, "Socket", true));
	ft_bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1)
		return (error(0, "Bind", true));
	printf("Server created succesfully!\n");
	return (sockfd);
}