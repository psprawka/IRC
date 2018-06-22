/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:29:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 04:05:00 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static int	init_client_socket(int port, char *address)
{
	struct protoent 	*protocol;
	struct sockaddr_in	client_addr;
	int					sockfd;
	
	protocol = getprotobyname("TCP");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
		return (error(0, "Socket", true));
	
	ft_bzero(&client_addr, sizeof(struct sockaddr_in));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = inet_addr(address);
	if (connect(sockfd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in)) == -1)
		return (error(0, "Connect", true));
	return (sockfd);
}

static int 	run_client(int sockfd, int max_fd, fd_set client_fds)
{
	fd_set		select_fds;
	int			i;
	
	select_fds = client_fds;
	while (select(FD_SETSIZE, &select_fds, NULL, NULL, NULL) > -1)
	{
		i = 0;
		while (i < FD_SETSIZE)
		{
			if (FD_ISSET(i, &select_fds))
			{
				if (i == 1)
					send_message_to_server(sockfd);
				else if (recv_message_from_server(sockfd) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			i++;
		}
		select_fds = client_fds;
	}
	close(sockfd);
	return (error(0, "Select", true));
}

int			main(int ac, char **av)
{

	fd_set		client_fds;
	int			sockfd;
	int			max_fd;

	max_fd = 0;
	if (parse_args_client(ac, av) == EXIT_FAILURE ||
		(sockfd = init_client_socket(ft_atoi(av[1]), av[2])) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	FD_ZERO(&client_fds);
	FD_SET(sockfd, &client_fds);
	FD_SET(1, &client_fds);
	max_fd = sockfd;
	return (run_client(sockfd, max_fd, client_fds));
}