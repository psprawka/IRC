/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_send_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:23:26 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 04:07:36 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	send_welcome_message(int clientfd)
{
	int		len;

	ft_bzero(g_server.buff, SERV_BUFF_SIZE);
	ft_strcpy(g_server.buff, "\nWelcome ");
	ft_strcat(g_server.buff, g_clients[clientfd]->color);
	ft_strcat(g_server.buff, g_clients[clientfd]->nick);
	ft_strcat(g_server.buff, "\x1B[0m!\n");
	ft_strcat(g_server.buff, "Following commands are available:\n");
	ft_strcat(g_server.buff, " -> \"/join <channel_name>\" - join channel of your choice,\n");
	ft_strcat(g_server.buff, " -> \"/color <color>\" - change your color,\n");
	ft_strcat(g_server.buff, " -> \"/nick <nickname>\" - choose your nickname,\n");
	ft_strcat(g_server.buff, " -> \"/fd\" - find out what's your unique client number.\n\n");
	ft_strcat(g_server.buff, "You can find a list of available colors under \"/rainbow\" comamnd.\n");
	ft_strcat(g_server.buff, "Thank you for joining our chat! - teamserver\n\n");
	len = ft_strlen(g_server.buff);
	if (send(clientfd, ft_strdup(g_server.buff), len, 0) == -1)
		error(0, "Send", false);
}

int		send_message(int clientfd, char *msg)
{
	int			i;
	t_node		*node;
	t_client	*peer;
	
	node = g_server.clients;
	while (node)
	{
		peer = node->data;
		if (peer && !ft_strcmp(peer->room, g_clients[clientfd]->room))
		{
			ft_bzero(g_server.buff, SERV_BUFF_SIZE);
			ft_strcpy(g_server.buff, peer->nick);
			ft_strcat(g_server.buff, ": ");
			ft_strcat(g_server.buff, peer->color);
			ft_strcat(g_server.buff, msg);
			ft_strcat(g_server.buff, NORMAL);
			ft_strcat(g_server.buff, "\n");
			if (send(peer->fd, g_server.buff, ft_strlen(g_server.buff), 0) == -1)
				return (EXIT_FAILURE);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
