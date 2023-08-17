# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 17:05:49 by rkhinchi          #+#    #+#              #
#    Updated: 2023/08/17 15:56:52 by cpopolan         ###   ########.fr        #
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
		builtin/builtin_env.c \
		builtin/builtin_unset.c \
		builtin/builtin_export.c \
		builtin/builtin_exit.c \
		executor/env_to_struct.c \
		executor/env_utils.c \
		executor/value_env.c \
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
		executor/01redirections.c \
		executor/heredoc.c \
		parser/easy_split_utils.c \
		parser/easy_split.c \
		parser/easy_split_rows_counter.c \
		parser/enveloper.c \
		parser/env_to_struct.c \
		parser/expander.c \
		parser/noder.c \
		parser/noder_utils.c \
		parser/quote_cleaner_node_deleter.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	#@printf "creazione del file \e[92m $@ \e[0m\n"

all: $(NAME)

#-fsanitize=address

$(NAME): $(OBJ)
	make -C libft
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "\e[92m$(NAME) compiled\e[0m"

re:	fclean all

clean:
	make clean -C libft
	rm -rf $(OBJ)
	@echo "\e[90mNothing to clean\e[0m"

fclean:
	make fclean -C libft
	rm -rf $(OBJ)
	rm -rf $(NAME)
	@echo "\e[92m$(NAME) removed\e[0m"

.PHONY: all re clean fclean bonus

.SILENT: