/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_nick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:15:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 10:51:31 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

# define MSG_NONICK		"This nick is already taken. Try something different.\n"
# define MSG_NOWHITE	"Whitespaces are not allowed in your nick.\n"
# define MSG_LONGNICK	"Selected nick is too long (max 9 characters).\n"

static int	check_availability(int fd, char *nick)
{
	t_client	*peer;
	t_node		*node;

	if (ft_strlen(nick) > 9)
	{	
		send_system_message(fd, ft_strdup(MSG_LONGNICK));
		return (EXIT_FAILURE);
	}
	if (ft_are_whitespaces(nick))
	{	
		send_system_message(fd, ft_strdup(MSG_NOWHITE));
		return (EXIT_FAILURE);
	}
	node = g_server.clients;
	while (node)
	{
		peer = node->data;
		if (peer && !ft_strcmp(peer->nick, nick))
		{
			send(peer->fd, MSG_NONICK, ft_strlen(MSG_NONICK), 0);
			return (EXIT_FAILURE);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

static void	notify_nick_change(int fd, char *nick)
{
	t_client	*peer;
	t_node		*node;

	node = g_server.clients;
	ft_strcpy(g_server.buff, "User \"");
	ft_strcat(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, "\" changed its nick to \"");
	ft_strcat(g_server.buff, nick);
	ft_strcat(g_server.buff, "\".\n");
	while (node)
	{
		peer = node->data;
		if (peer && peer->fd != fd && !ft_strcmp(peer->channel, g_clients[fd]->channel))
			send_system_message(peer->fd, ft_strdup(g_server.buff));
		node = node->next;
	}
}

void		request_nick(int fd, char *msg)
{
	int i;

	i = 0;
	while (msg[i] && !IS_WHITE(msg[i]))
		i++;
	while (msg[i] && IS_WHITE(msg[i]))
		i++;
	if (check_availability(fd, &(msg[i])) == EXIT_FAILURE)
		return ;
	ft_strcpy(g_server.buff, "Nick \"");
	ft_strcat(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, "\" has been changed to \"");
	ft_strcat(g_server.buff, &(msg[i]));
	ft_strcat(g_server.buff, "\".\n");
	send_system_message(fd, ft_strdup(g_server.buff));
	notify_nick_change(fd, &(msg[i]));
	free(g_clients[fd]->nick);
	g_clients[fd]->nick = ft_strdup(&(msg[i]));
}