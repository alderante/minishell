/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:50 by cpopolan          #+#    #+#             */
/*   Updated: 2023/06/23 11:15:36 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef enum token
{
	NON,
	ARG,
	BUILTIN,
	OPEN_FILE,
	HERE_DOC,
	LIMITOR,
	CREAT_FILE,
	WRITE_FILE,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_OVER,
	ENDS
}	t_e_token;

typedef struct s_lexer
{
	char	*token;
	t_e_token	type;
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