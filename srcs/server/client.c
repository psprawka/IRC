/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:26:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 09:37:54 by psprawka         ###   ########.fr       */
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
		printf("%sNew client [%d] joined.%s\n", ORANGE, connfd, NORMAL);
		ft_set_max_fd(&g_server.max_fd, connfd);
		FD_SET(connfd, &g_server.client_fds);
		g_clients[connfd] = init_client(connfd, ft_strdup(getenv("USER")));
		ft_add_list(&g_server.clients, g_clients[connfd]);
		notify_channel_join(connfd, NULL);
		send_welcome_message(connfd);
	}
}

void	client_quit(int clientfd)
{
	printf("%sClient [%d] quit.%s\n", YELLOW, clientfd, NORMAL);
	notify_channel_leave(clientfd, g_clients[clientfd]->channel);
	ft_remove_list(&g_server.clients, g_clients[clientfd]);
	free_client(g_clients[clientfd]);
	g_clients[clientfd] = NULL;
	FD_CLR(clientfd, &g_server.client_fds);
	close(clientfd);
}