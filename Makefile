all: test

test:
		gcc -g -Wall -Wextra -Werror *.c libft/libft.a -lreadline minishell.h -o minishell
