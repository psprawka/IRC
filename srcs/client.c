/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:29:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/22 20:48:29 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

#define IS_ALPHA(c)	((c > 64 && c < 91) || (c > 96 && c < 123)) ? 1 : 0
#define IS_WHITE(c)	(c == '\t' || c == ' ' || c == '\v') ? 1 : 0

void	change_nick(t_client *me, char *buff)
{
	int i;

	i = 0;
	// ft_printf("before\n");
	while (buff[i] && !IS_WHITE(buff[i]))
		i++;
	while (buff[i] && IS_WHITE(buff[i]))
		i++;
	ft_printf("[%s] changed to [%s]\n", me->name, &(buff[i]));
	free(me->name);
	me->name = &(buff[i]);
}

int		commands(t_client *me, char *buff)
{
	// ft_printf("yoooo\n");
	if (!ft_strncmp("/nick ", buff, 6))
	{
		change_nick(me, buff);
		return (1);
	}
	// ft_printf("yoooo2\n");
	return (0);
}

t_client	*create_client(int sockfd, char *name)
{
	t_client *client;

	client = (t_client *)ft_strnew(sizeof(t_client));
	client->name = name;
	client->sockfd = sockfd;
	client->color = CYAN;
	client->room = NULL;

	return (client);	
}

t_client *client_socket(int ac, char **av)
{
	struct protoent 	*protocol;
	struct sockaddr_in	client_addr;
	static t_client		*clients[FD_SETSIZE];
	int					sockfd;
	
	protocol = getprotobyname("TCP");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
		error(0, "Socket", true);
	ft_bzero(&client_addr, sizeof(struct sockaddr_in));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(ft_atoi(av[1]));
	client_addr.sin_addr.s_addr = inet_addr(av[2]);
	
	if (connect(sockfd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in)) == -1)
		error(0, "Connect", true);

	clients[sockfd] = create_client(sockfd, ft_strdup(getenv("USER"))); 
	return (clients[sockfd]);
}

int main(int ac, char **av)
{
	char		getbuff[BUFF_SIZE];
	char		*sendbuff;
	t_client	*me;

	parse_args_client(ac, av);
	me = client_socket(ac, av);
	
	// while (1)
	// {
	// 	ft_bzero(getbuff, BUFF_SIZE);
	// 	ft_printf("Enter password:\n");
	// 	gnl(1, &sendbuff);
	// 	if (send(sockfd, sendbuff, sizeof(sendbuff), 0) == -1)
	// 		error(0, "Send", false);
	// 	ft_printf("passwd entered [%s]\n", sendbuff);
	// 	recv(sockfd, getbuff, BUFF_SIZE, 0);
	// 	if (!ft_strcmp(getbuff, SERVPASSWD))
	// 	{
	// 		ft_printf("%sPassword correct!%s\n", GREEN, NORMAL);
	// 		break ;
	// 	}
	// }

	fd_set	client_fds;
	int		i;
	ft_bzero(&client_fds, sizeof(fd_set));
	
	while (1)
	{
		FD_ZERO(&client_fds);
		FD_SET(me->sockfd, &client_fds);
		FD_SET(1, &client_fds);
		ft_bzero(getbuff, BUFF_SIZE);
		i = 0;
		if (select(me->sockfd + 1, &client_fds, NULL, NULL, NULL) == -1)
			error(0, "Select", true);
		while (i < me->sockfd + 1)
		{
			if (FD_ISSET(i, &client_fds))
			{
				if (i == 1)
				{
					gnl(1, &sendbuff);
					// ft_printf("I got this: [%s]\n", sendbuff);
					if (!commands(me, sendbuff))
					{
						sendbuff = ft_strjoin(": ", sendbuff, 0);
						sendbuff = ft_strjoin(me->name, sendbuff, 0);
						// ft_printf("I got this: [%s] %d\n", sendbuff, ft_strlen(sendbuff));
						if (send(me->sockfd, sendbuff, ft_strlen(sendbuff), 0) == -1)
							error(0, "Send", false);
					}
					free(sendbuff);
				}
				else
				{
					recv(me->sockfd, getbuff, BUFF_SIZE, 0);
					ft_putendl_fd(getbuff, 1);
				}
			}
			i++;
		}
	}
	close(me->sockfd);
	return (0);
}
