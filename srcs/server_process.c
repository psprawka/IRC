/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:26:09 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/22 20:41:41 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"




void	process_data(int currfd, int sockfd, int maxfd, fd_set *client_fds)
{
	int		ret;
	char	buff[BUFF_SIZE];
	int 	i;

	ft_printf("hello\n");
	if ((ret = recv(currfd, buff, BUFF_SIZE, 0)) > 0)
	{
		i = 0;
		while (i < maxfd)
		{
			if (FD_ISSET(i, client_fds))
			{
				if (i != sockfd)
				{
					ft_printf("will send a message: [%s]\n", buff);
					if (send(i, buff, ret, 0) == -1)
							ft_printf("Sending unsuccessful\n");
					ft_bzero(buff, BUFF_SIZE);
				}
			}
			i++;
		}
	}
	else
	{
		ret == 0 ? ft_printf("Client quit\n") : ft_printf("Error recv\n");
		FD_CLR(currfd, client_fds);
		close(currfd);
	}
}

//					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
//					{
//						if (nbytes == 0)
//							printf("selectserver: socket %d hung up\n", i);
//						else
//							perror("recv");
//						close(i);
//						FD_CLR(i, &master);
//					}
//					else
//					{
//						for(j = 0; j <= fdmax; j++)
//						{
//							if (FD_ISSET(j, &master))
//							{
//								if (j != listener && j != i)
//								{
//									if (send(j, buf, nbytes, 0) == -1)
//										perror("send");
//								}
//							}
//						}
//					}