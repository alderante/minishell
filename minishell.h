/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:50 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/04 11:26:07 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef enum type
{
	NON,
	ARG, 			// ls -l o wc -l
	BUILTIN,		// echo, cd, pwd, export, unset, env, exit
	OPEN_FILE,		// <
	HERE_DOC,		// <<
	LIMITOR,		// |
	CREAT_FILE,		// >
	WRITE_FILE,		// >>
	FILE_IN,		// ls -l < file.txt quindi il tipo del file.txt e' FILE_IN
	FILE_OUT,		// ls -l > file.txt quindi il tipo del file.txt e' FILE_OUT
	FILE_OUT_OVER,	// ls -l >> file.txt quindi il tipo del file.txt e' FILE_OUT_OVER
	ENDS 			// ;
}	t_e_type;

typedef struct s_token
{
	char			*token;
	t_e_type		type;
	int				pos;
	struct s_token	*next;
}	t_token;




typedef struct s_command_line
{
	char					*new_matrix_string;
	t_token					*single_token;
	char					**envp;
	char					**argv;
	int						fd_in;
	int						fd_out;
	char					*name_file;
	struct s_command_line	*next;
}	t_command_line;






void ft_lexer(char *input);
t_token	*ft_newnode(char *token, int pos);
t_token	*ft_initialize(char **new_matrix);
void	ft_final_stamper(t_token *first);
void    ft_node_deleter(t_token *first);
char	*get_current_dir_name(void);
void    ft_new_matrix(char **matrix);


#endif