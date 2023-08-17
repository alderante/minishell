/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:50:57 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/17 15:38:08 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../executor.h"

extern int	g_exit_status;

/* The wait_pid function takes the pid array and the cmd argument as arguments. 
The function waits for each child process to 
finish executing and then checks its exit status. 
If the exit status indicates an error, the function returns that error code. */

char	*ft_get_value_of_env(t_env01 **env, char *str, char *file_name);

/* stat function is to check if file exists, 
if it does not exist, it will return -1 */

int	execution_execve(t_command_line **cmd, t_command_line **original,
	char **str, pid_t *pid)
{
	execve((*cmd)->argv[0], (*cmd)->argv, str);
	(void)(original);
	(void)(pid);
	free(str);
	free(pid);
	ft_env_deleter((*original)->env_list);
	free_all(original);
	g_exit_status = 127;
	exit(g_exit_status);
	return (0);
}

//t_env01			*env_list;

void	ft_big_executor01_continue(t_command_line **cmd,
		t_command_line **original, pid_t *pid, char **str)
{
	if (cmd_is_builtin((*cmd)->argv[0]) == 0)
	{
		if ((*cmd)->argv[0] == NULL)
		{
			free(str);
			free(pid);
			ft_env_deleter((*original)->env_list);
			free_all(original);
			exit(1);
		}
		(*cmd)->argv[0] = find_if_executable((*cmd)->argv[0],
				ft_get_value_of_env(&(*cmd)->env_list, "PATH",
					(*cmd)->argv[0]), 0);
	}
}

void	ft_big_executor02_continue(t_command_line **cmd,
		t_command_line **original, pid_t *pid, char **str)
{
	if ((*cmd)->fd_in < 0 || (*cmd)->fd_out < 0)
	{
		free(str);
		free(pid);
		ft_env_deleter((*original)->env_list);
		free_all(original);
		exit(1);
	}
}

int	ft_big_executor(t_command_line **cmd, t_command_line **original, pid_t *pid)
{
	char		**str;

	(void)(pid);
	dup2((*cmd)->fd_in, STDIN_FILENO);
	dup2((*cmd)->fd_out, STDOUT_FILENO);
	all_fd_close(original);
	str = matrix_from_env(&(*cmd)->env_list);

	if (str == NULL)
		all_fd_close_n_exit(original);
	ft_big_executor01_continue(cmd, original, pid, str);
	ft_big_executor02_continue(cmd, original, pid, str);
	if (cmd_is_builtin((*cmd)->argv[0]))
		execute_builtin(cmd, original, pid);
	else
		execution_execve(cmd, original, str, pid);
	free(str);
	free(pid);
	ft_env_deleter((*original)->env_list);
	free_all(original);
	exit(0);
	return (0);
}


// function to set up pipes for inter-process communication
//for each command in the commad line

int	execution(t_command_line **cmd_line)
{
	t_command_line	*updated;
	pid_t			*pid;
	int				rtrn;

	updated = *cmd_line;
	rtrn = piping(cmd_line);
	if (rtrn == 0)
		pid = malloc(sizeof(pid_t) * command_len(updated)); 
	else
		return (rtrn);
	if (pid == NULL)
		return (50);
	func_fork(cmd_line, pid);
	wait_pid(cmd_line, pid);
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	free(pid);
	return (0);
}
