/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:25:37 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/22 21:06:31 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	check_select_fds(fd_set *client_fds, int sockfd, int *maxfd)
{
	int connfd;

	if ((connfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) == -1)
		ft_printf("Accept error\n");
	else
	{
		ft_printf("New client connected\n");
		FD_SET(connfd, client_fds);
		if (connfd > *maxfd)
			*maxfd = connfd;
	}
}

void	runserver(fd_set client_fds, int maxfd, int sockfd)
{
	int		i;
	fd_set	select_fds;

	while (1)
	{
		i = 0;
		select_fds = client_fds;
		if (select(maxfd + 1, &select_fds, NULL, NULL, NULL) == -1)
			error(0, "Select", true);
		while (i < maxfd + 1)
		{
			if (FD_ISSET(i, &select_fds))
			{
				if (i == sockfd)
					check_select_fds(&client_fds, sockfd, &maxfd);
				else
					process_data(i, sockfd, maxfd, &client_fds);
			}
			i++;
		}
	}
}

int		server_socket(int port)
{
	int					opt;
	int					sockfd;
	struct protoent		*protocol;
	struct sockaddr_in	server_addr;
	
	opt = true;
	protocol = getprotobyname("TCP");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) < 0)
		error(0, "Socket", true);
	ft_bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1)
		error(0, "Bind", true);
	ft_printf("Binding successful!\n");
	return (sockfd);
}

int		main(int ac, char **av)
{
	int						sockfd;
	int						connfd;
	fd_set					client_fds;
	struct sockaddr_in		temp;
	// socklen_t				socklen;
	
	parse_args_serv(ac, av);
	sockfd = server_socket(ft_atoi(av[1]));
	if (listen(sockfd, MAX_CLIENT_FD) == -1)
		error(0, "Listen", true);
	// ft_printf("Accept before\n");
	// ft_bzero(&temp, sizeof(struct sockaddr_in));
	// socklen = sizeof(struct sockaddr_in);
	// accept(sockfd, (struct sockaddr *)&temp, &socklen);
	// ft_printf("Accept after\n");
	ft_bzero(&client_fds, sizeof(fd_set));
	// ft_printf("%d I was listening!\n", sockfd);
	FD_SET(sockfd, &client_fds);
	runserver(client_fds, sockfd, sockfd);
	return (0);
}