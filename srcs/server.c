/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:25:37 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/19 22:51:22 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int main(int ac, char **av)
{
	int						sockfd;
	int						connection_fd;
	char					buff[BUFF_SIZE];
	struct sockaddr_in		server_addr;
	fd_set					select_fds;
	int						client_fds[MAX_CLIENT_FD];
	int						opt;
	struct protoent			*protocol;     
	
	if (ac != 2)
	{
		ft_printf("Usage: server <port number>\n");
		return ;
	}
	if (ft_atoi(av[1] > 65535) || ft_atoi(av[1] < 1024))
	{
		ft_printf("Port number has to be between 1024 and 65535!\n");
		return ;
	}
	
	ft_bzero(buff, BUFF_SIZE);
	ft_bzero(client_fds, MAX_CLIENT_FD);
	ft_bzero(&server_addr, sizeof(server_addr));
	opt = true;
	
	protocol = getprotobyname("TCP");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) < 0)
	{
		ft_printf("Failed to create a socket\n");
		return ;
	}
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt)))
	{
		ft_printf("Failed to set socket options\n");
		return ;	
	}
	
	ft_memset(&(server_addr.sin_zero), '\0', 8);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htonl(ft_atoi(av[1]));
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		ft_printf("Binding unsuccessful\n");
		return ;	
	}
	else
		ft_printf("\x1B[33mBinding successful!\n");
		
	while (1)
	{
		listen(sockfd, MAX_CLIENT_FD);
		connection_fd = accept(sockfd, (struct sockaddr *) NULL, NULL);
		ft_printf("\x1B[32mConnection accepted!\n");
		
		while (1)
		{
			printf("\x1B[33mWaiting for a message...\n");
			// recv(connection_fd, buff, BUFF_SIZE);
			
			printf("\x1B[32mMessage obtained!\n");
			if (strncmp("quit\n", buff, 5) == 0)
			break;
			if (strncmp("ping\n", buff, 5) == 0)
			// send(connection_fd, "pong pong\n", 10);
			// else
			// send(connection_fd, "try ping!\n", 10);
			bzero(buff, BUFF_SIZE);
		}
	}
	close(sockfd);
	close(connection_fd);
	return (0);

 while(1)  
    {  
        FD_ZERO(&select_fds);
        FD_SET(sockfd, &select_fds);  
        // for ( i = 0 ; i < max_clients ; i++)  
        // {  
        //     sd = client_socket[i];  
        //     if(sd > 0)  
        //         FD_SET( sd , &readfds);  
        //     if(sd > max_sd)  
        //         max_sd = sd;  
        // }  
        // activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
        // if ((activity < 0) && (errno!=EINTR))  
        //     printf("select error");  
        // if (FD_ISSET(master_socket, &readfds))  
        // {  
        //     if ((new_socket = accept(master_socket, 
        //             (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
        //         perror("accept");  
        //         exit(EXIT_FAILURE);  
        //     printf("New connection , socket fd is %d , ip is : %s , port : %d 
        //           \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
        //           (address.sin_port));  
        //     if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
        //         perror("send");  
        //     for (i = 0; i < max_clients; i++)  
		// 	{
        //         if (client_socket[i] == 0 )  
        //         {  
        //             client_socket[i] = new_socket;  
        //             printf("Adding to list of sockets as %d\n" , i);  
        //             break;  
        //         }  
        //     }  
        // }  

}
