/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_nick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:15:35 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 13:22:56 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	request_nick(int fd, char *msg)
{
	int i;

	i = 0;
	while (msg[i] && !IS_WHITE(msg[i]))
		i++;
	while (msg[i] && IS_WHITE(msg[i]))
		i++;

	ft_bzero(g_server.buff, SERV_BUFF_SIZE);
	ft_strcpy(g_server.buff, g_clients[fd]->nick);
	ft_strcat(g_server.buff, " chnaged to ");
	ft_strcat(g_server.buff, &(msg[i]));
	ft_strcat(g_server.buff, "\n");
	if (send(fd, g_server.buff, ft_strlen(g_server.buff), 0) == -1)
		error(0, "Send", false);
	free(g_clients[fd]->nick);
	g_clients[fd]->nick = ft_strdup(&(msg[i]));
}