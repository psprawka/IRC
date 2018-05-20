/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:30:53 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/19 22:31:12 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
# define FT_IRC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include "libft.h"

# define	BUFF_SIZE       64
# define    MAX_CLIENT_FD   10



typedef struct  s_client
{
    int     fd;
    char    *color;
    char    *user;
    char    *room;
}               t_client;


/*
**  There is a possobility of casting sockaddr_in to sockaddr 
** 	struct sockaddr_in
** 	{
** 		sa_family_t sin_family;    		Address Family/rodzina adresów
** 		uint16_t sin_port;        	 	Port number/numer portu
** 		struct in_addr sin_addr;   		Internet address/adres internetowy
** 		unsigned char sin_zero[8];  	Pad bytes/ dla zachowania rozmiaru struct sockaddr
** 	};
**
**  my_addr.sin_port = 0; // wybierz losowo nieu˙zywany port
**  my_addr.sin_addr.s_addr = INADDR_ANY; // u˙zyj mojego adresu IP
**
**  FD_SETSIZE is 1024
*/

#endif
