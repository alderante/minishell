CC = cc

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g

SRC = minishell.c \
		noder.c \
		noder_utils.c \
		enveloper.c

LIBFT = libft/libft.a

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(FLAGS) $(SRC) $(LIBFT) -lreadline -o $(NAME);\
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
