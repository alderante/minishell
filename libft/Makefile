# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:37:27 by rkhinchi          #+#    #+#              #
#    Updated: 2023/03/15 17:44:16 by rkhinchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memcpy.c \
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
		ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
		get_next_line.c ft_strcmp.c \

OBJS	=	$(SRCS:.c=.o)

BONUS	=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c

BOBJS	=	$(BONUS:.c=.o)

CC	=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM	=	rm -f
NAME	=	libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus:		$(OBJS) $(BOBJS)
			ar rcs $(NAME) $(OBSJ) $(BOBJS)

clean:
		$(RM) $(OBJS) $(BOBJS)

fclean:		clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:		all bonus clean fclean re bonus
