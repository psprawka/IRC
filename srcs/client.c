/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:29:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/19 20:26:16 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int main(void)
{
	int						sockfd;
	char					get[BUFF_SIZE];
	char					send[BUFF_SIZE];
	struct sockaddr_in		server_addr;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		ft_printf("Failed to create a socket\n");
		return (1);
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(av[1]);
	server_addr.sin_addr.s_addr = inet_addr(av[2]);
	
	inet_pton(AF_INET, "10.114.12.7", &server_addr.sin_addr);
	connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	while (1)
	{
		bzero(get, BUFF_SIZE);
		bzero(send, BUFF_SIZE);
		fgets(send, BUFF_SIZE, stdin);
		
		if (write(sockfd, send, strlen(send)) == -1)
        {
			ft_printf("Wrinting to socket failed.\n");
			return (1);
        }
		if (strncmp("/join ", send, 6) == 0)
		    
		read(sockfd, get, BUFF_SIZE);
		write(1, get, strlen(get));
	}
	close(sockfd);
	return (0);
}
