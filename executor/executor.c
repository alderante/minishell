/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:50:57 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/14 23:14:54 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../executor.h"

extern int	g_exit_status;

/* The wait_pid function takes the pid array and the cmd argument as arguments. 
The function waits for each child process to 
finish executing and then checks its exit status. 
If the exit status indicates an error, the function returns that error code. */

char	*ft_get_value_of_env(t_env01 **env, char *str);

int	wait_pid(t_command_line **cmd, pid_t *pid)
{
	t_command_line	*updated;
	int				len;
	int				i;

	i = 0;
	updated = *cmd;
	len = command_len(updated);
	if (len == 1 && cmd_is_builtin((*cmd)->argv[0]))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		i++;
	}
	return (0);
}

/* stat function is to check if file exists, 
if it does not exist, it will return -1 */

int	execution_execve(t_command_line **cmd, t_command_line **original,
	char **str, pid_t *pid)
{
	struct stat	buff;

	execve((*cmd)->argv[0], (*cmd)->argv, str);
	if (stat((*cmd)->argv[0], &buff) == -1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*cmd)->argv[0], ft_strlen((*cmd)->argv[0]));
		write(2, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		//exit(126);
	}
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

int	big_executor(t_command_line **cmd, t_command_line **original, pid_t *pid)
{
	char		**str;

	(void)(pid);
	dup2((*cmd)->fd_in, STDIN_FILENO);
	dup2((*cmd)->fd_out, STDOUT_FILENO);
	all_fd_close(original);
	str = matrix_from_env(&(*cmd)->env_list);

	if (str == NULL)
		all_fd_close_n_exit(original);

	if (cmd_is_builtin((*cmd)->argv[0]) == 0)
	{
		printf("this is argv[0] %s\n", (*cmd)->argv[0]);
		if ((*cmd)->argv[0] == NULL)
		{
			free(str);
			free(pid);
			ft_env_deleter((*original)->env_list);
			free_all(original);
			exit(1);
		}
		(*cmd)->argv[0] = find_if_executable((*cmd)->argv[0],
				ft_get_value_of_env(&(*cmd)->env_list, "PATH"), 0);
	}
	if ((*cmd)->argv[0] == NULL)
	{
		free(str);
		free(pid);
		ft_env_deleter((*original)->env_list);
		free_all(original);
		exit(50);
	}
	if ((*cmd)->fd_in < 0 || (*cmd)->fd_out < 0)
	{
		free(str);
		free(pid);
		ft_env_deleter((*original)->env_list);
		free_all(original);
		exit(1);
	}
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
