/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:25:37 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 14:30:36 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_server	g_server;
t_client	*g_clients[FD_SETSIZE];

static int	run_server(void)
{
	int		i;
	fd_set	select_fds;

	select_fds = g_server.client_fds;
	while (select(FD_SETSIZE, &select_fds, NULL, NULL, NULL) > -1)
	{
		i = 0;
		while (i < g_server.max_fd + 1)
		{
			if (FD_ISSET(i, &select_fds))
				i == g_server.serverfd ? new_client() : process_data(i);
			i++;
		}
		select_fds = g_server.client_fds;
	}
	return (error(0, "Select", true));
}

int		main(int ac, char **av)
{
	struct sockaddr_in		temp;
	
	if (parse_args_serv(ac, av) == EXIT_FAILURE ||
		init_server() == EXIT_FAILURE ||
		(g_server.serverfd = init_server_socket(ft_atoi(av[1]))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	if (listen(g_server.serverfd, 10) == -1)
		return (error(0, "Listen", true));
	ft_bzero(&g_server.client_fds, sizeof(fd_set));
	FD_SET(g_server.serverfd, &g_server.client_fds);
	g_server.max_fd = g_server.serverfd;
	return (run_server());
}