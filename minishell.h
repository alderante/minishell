/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:09:52 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/06 16:38:55 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
// # include "parsing.h"
// # include "exec.h"
// # include "builtin.h"
# include "libft/libft.h"
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_token			t_token;
typedef struct s_commande_line	t_command_line;

typedef enum mod
{
	GET,
	DELETE,
	FREE,
	ADD
}			t_mod;

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
}				t_e_token;

// cat file.txt
// file.txt this should be str
struct			s_token
{
	char		*str; //the file name for open function, in redirect file-in
	t_e_token	type;
	bool		expanded;
	t_token		*next;
};

struct				s_commande_line
{
	char			*string; //everything which is passed but till pipe
	t_token			*original_token;
	char			**envp;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	t_command_line	*next;
};

// str: a pointer to a string that represents the name and value of the environment variable, in the format name=value.
// declare: an integer that indicates whether the environment variable is declared or not. 
// 	If declare is set to 1, the variable is declared; if it is set to 0, the variable is not declared.
// next: a pointer to the next s_env struct in a linked list of environment variables.
typedef struct s_env
{
	char			*str;
	int				declare;
	struct s_env	*next;
}				t_env;

//executor.c
int		big_executor(t_command_line **cmd, t_command_line **original, pid_t *pid);
void	execution(t_command_line **cmd_line);

//utils_exec.c
void	all_fd_close(t_command_line **cmd);
int		command_len(t_command_line *cmd);
void	freeing_matrix_nfd(int **nfd);
void	all_fd_close_n_exit(t_command_line **original);
int		cmd_is_builtin(char *str);
void	free_token(t_command_line **cmd_line);
int		free_all(t_command_line **cmd_line);
void	all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str);
void	free_split(char **split);
char	*free_split_ret_null(char **split_path);
void	all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str);

//piping
int		using_pipe(int **nfd, int i, t_command_line **updated);
int 	piping(t_command_line **cmd);

//fork.c
int		process_forking(pid_t *pid, int i, t_command_line **cmd, t_command_line **updated);
int 	func_fork(t_command_line **cmd, pid_t *pid);

//redirection.c
int		redirections_fd(t_command_line **cmd);

//env.c e env_utils.c
char	**matrix_from_env(t_env **envp);
t_env	**get_adress_env(void);
int		free_delete_add(char *str, int mode);
void	func_2_free_all_env(void);
void	free_all_env(t_env **env);
void	particular_env_free(t_env *env);

//find_exec_file.c
char	*find_if_executable(char *str, char *path, int i);

//execute_builtin.c
int	execute_builtin(char **str, t_command_line **cmd,
	t_command_line **original, pid_t *pid);

//BUILTIN
int	ft_built_in_pwd(char **str);
#endif