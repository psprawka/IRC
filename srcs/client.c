/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:29:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/05/23 19:34:45 by psprawka         ###   ########.fr       */
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

void	setup_termcaps(void)
{
	struct termios	tset;

	if (tcgetattr(ttyslot(), &tset))
		error(0, "Tcgetattr: Error applying terminal settings\n", true);
	tset.c_lflag &= ~ICANON;
	tset.c_lflag |= ECHO;
}

void	unset_termcaps(void)
{
	struct termios	tset;

	if (tcgetattr(ttyslot(), &tset))
		error(0, "Tcgetattr: Error restoring terminal settings\n", true);
	tset.c_lflag &= ~ECHO;
	tset.c_lflag |= ICANON;
	tcsetattr(ttyslot(), TCSANOW, &tset);
}

char	*assing_color(char *color)
{
	if (!ft_strncmp(color, "BLUE", 4))
		return (BLUE);
	if (!ft_strncmp(color, "CYAN", 4))
		return (CYAN);
	if (!ft_strncmp(color, "PINK", 4))
		return (PINK);
	if (!ft_strncmp(color, "ORANGE", 6))
		return (ORANGE);
	if (!ft_strncmp(color, "MAGNETA", 7))
		return (MAGNETA);
	if (!ft_strncmp(color, "YELLOW", 6))
		return (YELLOW);
	if (!ft_strncmp(color, "RED", 3))
		return (RED);
	if (!ft_strncmp(color, "GREEN", 5))
		return (GREEN);
	if (!ft_strncmp(color, "GREY", 4))
		return (RED);
	if (!ft_strncmp(color, "PURPLE", 6))
		return (PURPLE);
	
	return (DEF_COLOR);
}

void	change_color(t_client *me, char *buff)
{
	int i;

	i = 0;
	while (buff[i] && !IS_WHITE(buff[i]))
		i++;
	while (buff[i] && IS_WHITE(buff[i]))
		i++;
	me->color = assing_color(&(buff[i]));
}

int		commands(t_client *me, char *buff)
{
	if (!ft_strncmp("/nick ", buff, 6))
		change_nick(me, buff);
	else if (!ft_strncmp("/fd", buff, 3) && ft_strlen(buff) == 3)
		ft_printf("fd: %d\n", me->sockfd);
	else if (!ft_strncmp("/color ", buff, 7))
		change_color(me, buff);
	else return (0);
	return (1);
}

t_client	*create_client(int sockfd, char *name)
{
	t_client *client;

	client = (t_client *)ft_strnew(sizeof(t_client));
	client->name = name;
	client->sockfd = sockfd;
	client->color = DEF_COLOR;
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

int my_putchar(int n)
{
	return (write(1, &n, 1));
}

int main(int ac, char **av)
{
	char		getbuff[BUFF_SIZE];
	char		*sendbuff;
	t_client	*me;

	parse_args_client(ac, av);
	me = client_socket(ac, av);
	setup_termcaps();
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

	static char	*cache = NULL;
	
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
					cache = tgetstr("cl", NULL);
					tputs(cache, 1, &my_putchar);
					// ft_printf("I got this: [%s]\n", sendbuff);
					if (!commands(me, sendbuff))
					{
						sendbuff = ft_strjoin(me->color, sendbuff, 0);
						sendbuff = ft_strjoin(": ", sendbuff, 0);
						sendbuff = ft_strjoin(me->name, sendbuff, 0);
						sendbuff = ft_strjoin(sendbuff, NORMAL, 0);
						// ft_printf("I got this: [%s] %d\n", sendbuff, ft_strlen(sendbuff));
						if (send(me->sockfd, sendbuff, ft_strlen(sendbuff), 0) == -1)
							error(0, "Send", false);
					}
					free(sendbuff);
				}
				else
				{
					recv(me->sockfd, getbuff, BUFF_SIZE, 0);
					// ft_printf("thats what I got: [%s]\n", getbuff);
					ft_putendl_fd(getbuff, 1);
				}
			}
			i++;
		}
	}
	close(me->sockfd);
	unset_termcaps();
	return (0);
}
