/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 08:27:33 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/22 08:53:32 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	request_clear(int fd, char *msg)
{
	int save_stdout;

	save_stdout = dup(1);
	dup2(fd, 1);
	system("clear");
	dup2(save_stdout, 1);
	close(save_stdout);
}
