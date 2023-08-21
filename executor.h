/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:09:52 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/21 14:20:22 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>

//typedef struct s_token			t_token;
//typedef struct s_commande_line	t_command_line;

typedef enum mod
{
	GET,
	DELETE,
	FREE,
	ADD
}			t_mod;

typedef struct s_init
{
	int				i;
	int				j;
	t_token			*node;
	t_token			*first_token;
	t_command_line	*temp;
	char			**current_line;	
}	t_init;

/*
typedef enum type
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
}				t_e_type;

// cat file.txt
// file.txt this should be str
//token, sthe file name for open function, in redirect file-in
struct			s_token
{
	char		*token;
	t_e_type	type;
	//bool		expanded;
	t_token		*next;
};

struct				s_commande_line
{
	char			*new_matrix_string; //everything which is passed but till pipe
	t_token			*single_token;
	char			**envp;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	t_command_line	*next;
};

*/

/* str: a pointer to a string that represents the name and 
value of the environment variable, in the format name=value.
declare: an integer that indicates 
whether the environment variable is declared or not. 
If declare is set to 1, the variable is declared; 
if it is set to 0, the variable is not declared.
next: a pointer to the next s_env struct in a linked list of 
environment variables. */
/* typedef struct s_env01
{
	char			*str;
	int				declare;
	struct s_env01	*next;
}				t_env01; */

//executor.c
int		ft_big_executor(t_command_line **cmd,
			t_command_line **original, pid_t *pid);
int		ft_execution(t_command_line **cmd_line);

//utils_exec.c
void	ft_all_fd_close(t_command_line **cmd);
int		ft_command_len(t_command_line *cmd);
void	ft_freeing_matrix_nfd(int **nfd);
void	ft_all_fd_close_n_exit(t_command_line **original);
int		ft_cmd_is_builtin(char *str);
void	ft_free_token(t_command_line **cmd_line);
int		ft_free_all(t_command_line **cmd_line);
void	ft_all_free_n_exit(t_command_line **cmd,
			pid_t *pid, char **str);
void	free_split(char **split);
char	*free_split_ret_null(char **split_path);
void	ft_all_free_n_exit(t_command_line **cmd,
			pid_t *pid, char **str);

//ft_piping
int		ft_using_pipe(int **nfd, int i, t_command_line *updated);
int		ft_piping(t_command_line **cmd);

//fork.c
int		ft_process_forking(pid_t *pid, int i, t_command_line **cmd, 
			t_command_line **updated);
int		ft_func_fork(t_command_line **cmd, pid_t *pid);

//redirection.c //01redirection.c //heredoc.c
int		ft_redirections_fd(t_command_line **cmd);
int		ft_handle_input_redirection(t_command_line **cmd,
			t_token *updated, t_e_type type);
int		ft_create_heredoc_fd(t_command_line **cmd, t_token *token);

//env.c e env_utils.c
char	**ft_matrix_from_env(t_env01 **envp);
t_env01	**ft_address_of_env(void);
int		free_delete_add(char *str, int mode);
void	func_2_ft_free_all_env(void);
void	ft_free_all_env(t_env01 **env);
void	particular_env_free(t_env01 *env);
t_env01	*ft_convert_env_to_list(char **env);
t_env01	*noder(char *str);
char	*ft_get_value_of_env(t_env01 **env, char *str, char *file_name);
char	*ft_get_str_of_env(t_env01 **env, char *str);

//unset.c
void	ft_built_in_unset(char **tab, t_env01 **first);

//find_exec_file.c
char	*ft_find_if_executable(char *str, char *path, int i);

//ft_execute_builtin.c
int		ft_execute_builtin(t_command_line **cmd,
			t_command_line **original, pid_t *pid);

//BUILTIN
int		ft_built_in_pwd(char **str);
int		ft_built_in_pwd_fd(char **str, int fd);
int		ft_built_in_echo(char **str);
int		ft_built_in_echo_fd(char **str, int fd);
int		ft_builtin_cd(char **args);
int		ft_built_in_exit(char **args, t_command_line **cmd);

//signal.c
void	ft_signal_cmd(int sig);
void	signal_cmd_2(int sig);
int		ft_wait_pid(t_command_line **cmd, pid_t *pid);

//ft_organise_arg.c
int		ft_organise_arg(t_command_line **cmd);

//builtin_env
void	ft_built_in_env_fd(char **args, t_env01 *my_env, int fd);
void	ft_built_in_show_env_fd(t_env01 **env, int fd);
void	ft_built_in_export(char **tab, t_env01 **first);

//free
void	free_command_line(t_command_line *cmd);
void	ft_free_end(t_command_line **cmd, char *str);

//BUILTIN export utils
int		ft_export_checker(char *tab, int equal);
void	ft_free_built_in_export01(char *name, char *value);

#endif