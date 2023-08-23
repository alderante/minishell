# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 17:05:49 by rkhinchi          #+#    #+#              #
#    Updated: 2023/08/21 18:35:28 by rkhinchi         ###   ########.fr        #
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
		builtin/original_itoa.c \
		builtin/builtin_export_utils.c \
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
		parser/parser_check01.c \
		parser/parser_check02.c \
		parser/parser_check03.c \
		parser/majia.c \
		parser/easy_split_utils.c \
		parser/easy_split.c \
		parser/easy_split_rows_counter.c \
		parser/enveloper.c \
		parser/env_to_struct.c \
		parser/expander.c \
		parser/expander_utils.c \
		parser/noder.c \
		parser/noder_utils.c \
		parser/quote_cleaner_node_deleter.c

OBJ = $(SRC:.c=.o)

TEMP = .heredoc_tmp

TXT = .txt

LIBFT = libft/libft.a

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

#-fsanitize=address

$(NAME): $(OBJ)
	@make -sC libft
	@rm -rf $(TEMP)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "\e[92m$(NAME) compiled\e[0m"

re:	fclean all
	@rm -rf $(TEMP)

clean:
	@make clean -sC libft
	@rm -rf $(OBJ)
	@echo "\e[90mNothing to clean\e[0m"

fclean:
	@make fclean -sC libft
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@rm -rf $(TEMP)
	@rm -rf $(TXT)
	@echo "\e[92m$(NAME) removed\e[0m"

.PHONY: all re clean fclean bonus

#.SILENT: