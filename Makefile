# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 23:21:55 by psprawka          #+#    #+#              #
#    Updated: 2018/05/22 20:03:32 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
FLAGS = -g -Wall -Wextra -Werror

HEADERS = includes/
SRCS_DIR = srcs/

SRCS_CLIENT =	$(SRCS_DIR)client.c \
		$(SRCS_DIR)tools.c \
		$(SRCS_DIR)parse.c 
	
SRCS_SERVER =	$(SRCS_DIR)server.c \
		$(SRCS_DIR)server_process.c \
		$(SRCS_DIR)tools.c \
		$(SRCS_DIR)parse.c 

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

LIBFT = libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;206m[FT_IRC] \033[38;5;80mBuilding $<"
DONE_CLIENT = @echo "\033[K\033[1;38;5;44mCLIENT\033[K\033[1;38;5;200m ready to use!"
DONE_SERVER = @echo "\033[K\033[1;38;5;44mSERVER\033[K\033[1;38;5;200m ready to use!"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [FT_IRC]"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [FT_IRC]"
 
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(LIBFT) $(OBJS_CLIENT) $(HEADERS)
		@gcc $(FLAGS) -I $(HEADERS) $(OBJS_CLIENT) $(LIBFT) -lncurses -o $(NAME_CLIENT)
		$(DONE_CLIENT)

$(NAME_SERVER) : $(LIBFT) $(OBJS_SERVER) $(HEADERS)
		@gcc $(FLAGS) -I $(HEADERS) $(OBJS_SERVER) $(LIBFT) -lncurses -o $(NAME_SERVER)
		$(DONE_SERVER)

$(LIBFT):
	@make -C libft
	@echo ""

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(CLEAN_A)

re: fclean all
