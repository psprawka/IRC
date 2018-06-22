/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_channel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:28:41 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 07:22:52 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	notify_channel_join(int	fd, char *channel)
{
	t_client	*peer;
	t_node		*node;

	node = g_server.clients;
	ft_strcpy(g_server.buff, "User \"");
	ft_strcat(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, "\" joined channel.\n");;
	while (node)
	{
		peer = node->data;
		if (peer && peer->fd != fd && !ft_strcmp(peer->channel, channel))
			send_system_message(peer->fd, ft_strdup(g_server.buff));
		node = node->next;
	}
}

void	request_channel_join(int fd, char *msg)
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
			g_clients[fd]->channel = ft_strdup(&(msg[i]));
			send_system_message(fd, ft_strdup(g_server.buff));
			notify_channel_join(fd, &(msg[i]));
			return ;
		}
		node = node->next;
	}
	ft_add_list(&g_server.channels, ft_strdup(&(msg[i])));
	g_clients[fd]->channel = ft_strdup(&(msg[i]));
	send_system_message(fd, ft_strdup(g_server.buff));
	printf("New channel [%s] created.\n", &(msg[i]));
}

void	request_channel_leave(int fd, char *msg)
{
	;
	
}

void	request_channel_who(int fd, char *msg)
{
	;
	
}