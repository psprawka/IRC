/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:26:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 07:22:58 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	new_client(void)
{
	int 					connfd;
	struct sockaddr_in		temp;
	socklen_t				socklen;

	socklen = sizeof(struct sockaddr_in);
	ft_bzero(&temp, sizeof(struct sockaddr_in));
	if ((connfd = accept(g_server.serverfd, (struct sockaddr *)&temp, &socklen)) == -1)
		error(0, "Accept", false);
	else
	{
		printf("New client [%d] connected.\n", connfd);
		ft_set_max_fd(&g_server.max_fd, connfd);
		FD_SET(connfd, &g_server.client_fds);
		g_clients[connfd] = init_client(connfd, ft_strdup(getenv("USER")));
		ft_add_list(&g_server.clients, g_clients[connfd]);
		send_welcome_message(connfd);
	}
}