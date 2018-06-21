/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:23:42 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/21 13:38:52 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int		error(int errnb, char *msg, bool ifexit)
{
	if (errnb == 1)
		printf("Usage: server <port number>\n");
	else if (errnb == 2)
		printf("Port number has to be between 1024 and 65535!\n");
	else if (errnb == 3)
		printf("Usage: server <port number> <server addres>\n");
	else 
		printf("%s%s: %s%s\n", RED, msg, strerror(errno), NORMAL);
	return (ifexit == true ? EXIT_FAILURE : EXIT_SUCCESS);
}

