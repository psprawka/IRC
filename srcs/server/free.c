/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:36:59 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 09:41:45 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	free_client(void *client)
{
	free(((t_client *)client)->nick);
	free(((t_client *)client)->channel);
	free(client);
}
