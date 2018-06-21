/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:24:12 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 08:27:14 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	error(int errnb, char *msg, bool ifexit)
{
	if (errnb == 1)
		ft_printf("Usage: server <port number>\n");
	else if (errnb == 2)
		ft_printf("Port number has to be between 1024 and 65535!\n");
	else if (errnb == 3)
		ft_printf("Usage: server <port number> <server addres>\n");
	else 
		ft_printf("%s%s: %s%s\n", RED, msg, strerror(errno), NORMAL);	
	if (ifexit == true)
		exit(1);
}

void	parse_args_serv(int ac, char **av)
{
	if (ac != 2)
		error(1, NULL, true);
	if (ft_atoi(av[1]) > 65535 || ft_atoi(av[1]) < 1024)
		error(2, NULL, true);
}

void	parse_args_client(int ac, char **av)
{
	if (ac != 3)
		error(3, NULL, true);
	if (ft_atoi(av[1]) > 65535 || ft_atoi(av[1]) < 1024)
		error(2, NULL, true);
}