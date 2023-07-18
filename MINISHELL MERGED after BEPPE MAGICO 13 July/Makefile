# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 17:05:49 by rkhinchi          #+#    #+#              #
#    Updated: 2023/07/18 17:41:12 by rkhinchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g

SRC = minishell.c \
		builtin/execution_builtin.c \
		builtin/builtin_pwd.c \
		builtin/builtin_echo.c \
		builtin/builtin_cd.c \
		executor/env_to_struct.c \
		executor/env_utils.c \
		executor/env.c \
		executor/executor.c \
		executor/find_exec_file.c \
		executor/fork.c \
		executor/piping.c \
		executor/redirections.c \
		executor/signal.c \
		executor/utils_exec.c \
		executor/utils_exec01.c \
		executor/utils_exec02.c \
		executor/organise_arg.c \
		noder.c \
		noder_utils.c \
		enveloper.c \


LIBFT = libft/libft.a

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(FLAGS) -fsanitize=address $(SRC) $(LIBFT) $(LIBFT2) -lreadline -o $(NAME);\
	echo "\e[92m$(NAME) compiled\e[0m";\

re:	fclean all

clean:
	make clean -C libft
	@echo "\e[90mNothing to clean\e[0m"

fclean:
	make fclean -C libft
	rm -rf $(NAME);\
	echo "\e[92m$(NAME) removed\e[0m";\

.PHONY: all re clean fclean bonus

.SILENT:
