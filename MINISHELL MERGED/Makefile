CC = cc

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g

SRC = minishell.c \
		noder.c \
		noder_utils.c \
		enveloper.c \
		env.c \
		fork.c \
		piping.c \
		executor.c \
		env_utils.c \
		utils_exec.c \
		builtin_pwd.c \
		redirections.c \
		utils_exec01.c \
		utils_exec02.c \
		env_to_struct.c \
		find_exec_file.c \
		execution_builtin.c \
		signal.c


LIBFT = libft/libft.a

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(LIBFT2) -lreadline -o $(NAME);\
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
