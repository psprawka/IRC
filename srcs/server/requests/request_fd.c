/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:28:32 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 13:22:51 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	request_fd(int fd, char *msg)
{
	ft_bzero(g_server.buff, SERV_BUFF_SIZE);
	ft_strcpy(g_server.buff, ft_itoa(fd));
	ft_strcat(g_server.buff, "\n");
	if (send(fd, g_server.buff, ft_strlen(g_server.buff), 0) == -1)
		error(0, "Send", false);
}
