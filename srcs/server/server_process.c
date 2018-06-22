/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:26:09 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 04:05:26 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_request	g_requests[] = 
{
	{"/nick ", 6, request_nick},
	{"/color ", 7, request_color},
	{"/rainbow", 8, request_colors_list},
	{"/fd", 3, request_fd},
	{"/room ", 6, request_room},
	{NULL, 0, NULL}
};

int		process_request(int clientfd, char *msg)
{
	int i;

	i = 0;
	while (g_requests[i].request)
	{
		if (!ft_strncmp(msg, g_requests[i].request, g_requests[i].len))
		{
			g_requests[i].fct(clientfd, msg);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

void	process_data(int clientfd)
{
	int		ret;
	char	buff[BUFF_SIZE];

	ft_bzero(buff, BUFF_SIZE);
	if ((ret = recv(clientfd, buff, BUFF_SIZE, 0)) > 0)
	{
	
		if (process_request(clientfd, buff) == EXIT_SUCCESS)
			return ;
		if (send_message(clientfd, buff) == EXIT_FAILURE)
			error(0, "Send", false);
	}
	else
	{
		ret == 0 ? printf("Client [%d] quit\n", clientfd) :error(0, "Recv", false);
		FD_CLR(clientfd, &g_server.client_fds);
		close(clientfd);
	}
}