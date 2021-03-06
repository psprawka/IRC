/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:24:12 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 13:38:27 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int		parse_args_serv(int ac, char **av)
{
	if (ac != 2)
		error(1, NULL, true);
	if (ft_atoi(av[1]) > 65535 || ft_atoi(av[1]) < 1024)
		return (error(2, NULL, true));
	return (EXIT_SUCCESS);
}

int		parse_args_client(int ac, char **av)
{
	if (ac != 3)
		return (error(3, NULL, true));
	if (ft_atoi(av[1]) > 65535 || ft_atoi(av[1]) < 1024)
		return (error(2, NULL, true));
	return (EXIT_SUCCESS);
}