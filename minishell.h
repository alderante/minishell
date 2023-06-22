/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:50 by cpopolan          #+#    #+#             */
/*   Updated: 2023/06/22 15:26:13 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_lexer
{
	char    *token;
    char    *arg;
	int				pos;
	struct s_lexer	*next;
}	t_lexer;

void ft_lexer(char *lexer, t_lexer *first);
t_lexer	*ft_newnode(char *token, int pos);
t_lexer	*ft_initialize(char **matrix);
void	ft_final_stamper(t_lexer *first);
void    ft_node_deleter(t_lexer *first);
char	*get_current_dir_name(void);


#endif