/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:12:43 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 09:30:14 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void		notify_channel_join(int	fd, char *channel)
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

void		notify_channel_leave(int fd, char *channel)
{
	t_node		*node;
	t_client	*peer;

	node = g_server.clients;
	ft_strcpy(g_server.buff, "User \"");
	ft_strcat(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, "\" left channel.\n");;
	while (node)
	{
		peer = node->data;
		if (peer && peer->fd != fd && !ft_strcmp(peer->channel, channel))
			send_system_message(peer->fd, ft_strdup(g_server.buff));
		node = node->next;
	}
}
