/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_channel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:28:41 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 09:29:30 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void		request_channel_join(int fd, char *msg)
{
	t_node	*node;
	int		i;

	node = g_server.channels;
	skip_request_token(&i, msg);
	ft_strcpy(g_server.buff, "Joined \"");
	ft_strcat(g_server.buff, &(msg[i]));
	ft_strcat(g_server.buff, "\" channel.\n");
	while (node)
	{
		if (!ft_strcmp((char *)(node->data), &(msg[i])))
		{
			// notify_channel_leave(fd, g_clients[fd]->channel);
			g_clients[fd]->channel = ft_strdup(&(msg[i]));
			send_system_message(fd, ft_strdup(g_server.buff));
			notify_channel_join(fd, &(msg[i]));
			return ;
		}
		node = node->next;
	}
	ft_add_list(&g_server.channels, ft_strdup(&(msg[i])));
	send_system_message(fd, ft_strdup(g_server.buff));
	notify_channel_leave(fd, g_clients[fd]->channel);
	g_clients[fd]->channel = ft_strdup(&(msg[i]));
	printf("New channel [%s] created.\n", &(msg[i]));
}

void		request_channel_leave(int fd, char *msg)
{
	if (!g_clients[fd]->channel)
		return ;
	ft_strcpy(g_server.buff, "Left \"");
	ft_strcat(g_server.buff, g_clients[fd]->channel);
	ft_strcat(g_server.buff, "\" channel.\n");

	send_system_message(fd, ft_strdup(g_server.buff));
	notify_channel_join(fd, NULL);
	notify_channel_leave(fd, g_clients[fd]->channel);
	free(g_clients[fd]->channel);
	g_clients[fd]->channel = NULL;
}

void	request_channel_who(int fd, char *msg)
{
	t_client	*peer;
	t_node		*node;
	
	node = g_server.clients;
	ft_strcpy(g_server.buff, "Users in this channel:\n");
	while (node)
	{
		peer = node->data;
		if (peer && !ft_strcmp(peer->channel, g_clients[fd]->channel))
		{
			ft_strcat(g_server.buff, " -> ");
			ft_strcat(g_server.buff, peer->nick);
			ft_strcat(g_server.buff, "\n");
		}
		node = node->next;
	}
	send_system_message(fd, ft_strdup(g_server.buff));
}