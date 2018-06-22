/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 06:59:07 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 06:59:57 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	skip_request_token(int *i, char *msg)
{
	*i = 0;

	while (msg[*i] && IS_WHITE(msg[*i]))
		(*i)++;
	while (msg[*i] && !IS_WHITE(msg[*i]))
		(*i)++;
	while (msg[*i] && IS_WHITE(msg[*i]))
		(*i)++;
}
