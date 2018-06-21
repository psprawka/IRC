/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 13:10:17 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 13:24:28 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int		send_message_to_server(int sockfd)
{
	char		*sendbuff;

	gnl(1, &sendbuff);
	if (send(sockfd, sendbuff, ft_strlen(sendbuff), 0) == -1)
		return (error(0, "Send", true));
	free(sendbuff);
	return (EXIT_SUCCESS);
}

int		recv_message_from_server(int sockfd)
{
	char		getbuff[BUFF_SIZE];
	int			ret;

	if ((ret = recv(sockfd, getbuff, BUFF_SIZE, 0)) < 1)
	{
		printf("Server quit, try again later!\n");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(getbuff, 1);
	return (EXIT_SUCCESS);
}
