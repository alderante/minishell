/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:50 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/07 16:11:09 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum type
{
	NON,			// 1 BOOOOOOH
	ARG,			// 2 ls -l o wc -l
	BUILTIN,		// 3 echo, cd, pwd, export, unset, env, exit
	OPEN_FILE,		// 4 <
	HERE_DOC,		// 5 <<
	LIMITOR,		// 6 ???
	CREAT_FILE,		// 7 >
	WRITE_FILE,		// 8 >>
	FILE_IN,		// 9 ls -l < file.txt quindi il tipo del file.txt e' FILE_IN
	FILE_OUT,		// 10 ls -l > file.txt quindi il tipo del file.txt e' FILE_OUT
	FILE_OUT_OVER,	// 11 ls -l >> file.txt quindi il tipo del file.txt e' FILE_OUT_OVER
	ENDS 			// 12 ; ???
	//WRONG,			// 0 ERROR
}	t_e_type;

typedef struct s_token
{
	char *token;
	t_e_type type;
	int pos;
	struct s_token *next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				exp;	//0 = not exported, 1 = exported (both export and env) , 2 = exported but no value (only export)
	struct s_env	*next;
}	t_env;

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

int	ft_strcmp(char *str1, char *str2);

t_env			*ft_env_noder(char **envp);
char			**easy_split(char *str);
void			ft_lexer(char *input);
t_token			*ft_newnode(char *token, int pos);
t_token			*ft_initialize(t_command_line *first);
void			ft_final_stamper(t_command_line *cmd_line);
void			ft_node_deleter(t_token *first);
char			*get_current_dir_name(void);
t_command_line	*ft_new_matrix(char **matrix);
t_e_type		ft_node_builtin_typer(char	*token);
t_e_type		ft_node_redirect_typer(char *token);

#endif