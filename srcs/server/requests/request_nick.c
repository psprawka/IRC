/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_nick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:15:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 02:47:58 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

# define MSG_NONICK "This nick is already taken. Try something different.\n"

static int	check_availability(char *nick)
{
	t_client	*peer;
	t_node		*node;

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


void		request_nick(int fd, char *msg)
{
	int i;

	i = 0;
	while (msg[i] && !IS_WHITE(msg[i]))
		i++;
	while (msg[i] && IS_WHITE(msg[i]))
		i++;
	if (check_availability(&(msg[i])) == EXIT_FAILURE)
		return ;
	ft_bzero(g_server.buff, SERV_BUFF_SIZE);
	ft_strcpy(g_server.buff, "Nick \"");
	ft_strcat(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, "\" changed to \"");
	ft_strcat(g_server.buff, &(msg[i]));
	ft_strcat(g_server.buff, "\"\n");
	if (send(fd, g_server.buff, ft_strlen(g_server.buff), 0) == -1)
		error(0, "Send", false);
	free(g_clients[fd]->nick);
	g_clients[fd]->nick = ft_strdup(&(msg[i]));
}