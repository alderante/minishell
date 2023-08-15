/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:50 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/15 12:14:30 by cpopolan         ###   ########.fr       */
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
	NON,			// 0 BOOOOOOH
	ARG,			// 1 ls -l o wc -l cat
	BUILTIN,		// 2 echo, cd, pwd, export, unset, env, exit
	OPEN_FILE,		// 3 <
	HERE_DOC,		// 4 <<
	LIMITOR,		// 5 ???
	CREAT_FILE,		// 6 >
	WRITE_FILE,		// 7 >>
	FILE_IN,		// 8 ls -l < file.txt quindi il tipo del file.txt e' FILE_IN
	FILE_OUT,		// 9 ls -l > file.txt quindi il tipo del file.txt e' FILE_OUT
	FILE_OUT_OVER,	// 10 ls -l >> file.txt quindi il tipo del file.txt e' FILE_OUT_OVER
	ENDS 			// 11 ; ???
	//WRONG,		// 0 ERROR
}	t_e_type;

typedef struct s_token
{
	char *token;
	t_e_type type;
	int pos;
	struct s_token *next;
}	t_token;

// typedef struct s_env
// {
// 	char			*name;
// 	char			*value;
// 	//int				exp;	//0 = not exported, 1 = exported (both export and env) , 2 = exported but no value (only export)
// 	struct s_env	*next;
// }	t_env;

typedef struct s_env01
{
	char			*str;
	int				declare;
	struct s_env01	*next;
}				t_env01;

typedef struct s_command_line
{
	char					*new_matrix_string;
	t_token					*single_token;
	//t_env					*env;
	t_env01					*env_list;
	//char					**envp;
	char					**argv;
	int						fd_in;
	int						fd_out;
	char					*name_file;
	char					*heredoc_delimiter;
	struct s_command_line	*next;
}	t_command_line;

int	ft_strcmp(char *str1, char *str2);

int				ft_easy_split_rows_counter(char *input);
t_env01			*ft_env_noder(char **envp);
void			ft_env_deleter(t_env01 *first);
int				ft_check_quote (char c, int check);
void			ft_lexer(char *input, t_env01 **env_list);
t_token			*ft_newnode(char *token, int pos);
t_token			*ft_initialize(t_command_line *first, t_env01 *env_list);
void			ft_final_stamper(t_command_line *cmd_line);
void			ft_node_deleter(t_token *first);
char			*get_current_dir_name(void);
t_command_line	*ft_new_matrix(char **matrix);
t_e_type		ft_node_builtin_typer(char	*token);
t_e_type		ft_node_redirect_typer(char *token);
char			*expander(char*str, t_env01 *env_list);
t_env01			*ft_env_search(t_env01 *env_list, char *searchname);
void			ft_built_in_env(char **args, t_env01 *my_env);
char			*ft_value_extractor(t_env01 *env_list);
int				ft_env_list_equal_position(t_env01 *env_list);
char			*ft_value_extractor(t_env01 *env_list);

#endif