/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:50:57 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/06 16:36:52 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_exit_status;

//stat function is to check if file exists, if it does not exist, it will return -1

int	execution_execve(t_command_line **cmd, t_command_line **original,
	char **str, pid_t *pid)
{
	struct stat	buff;

	execve((*cmd)->argv[0], (*cmd)->argv, str);
	if (stat((*cmd)->argv[0], &buff) == -1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*cmd)->argv[0], ft_strlen((*cmd)->argv[0]));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		exit(126);
	}
	free_all(original);
	free(str);
	free(pid);
	func_2_free_all_env();
	g_exit_status = 127;
	exit(g_exit_status);
	return (0);
}

int	big_executor(t_command_line **cmd, t_command_line **original, pid_t *pid)
{
	char		**str;

	dup2((*cmd)->fd_in, STDIN_FILENO);
	dup2((*cmd)->fd_out, STDOUT_FILENO);
	all_fd_close(original);
	str = matrix_from_env(get_adress_env());
	if (str == NULL)
		all_fd_close_n_exit(original);
	if (cmd_is_builtin((*cmd)->argv[0]) == 0)
	{
		if ((*cmd)->argv[0] == NULL)
			all_free_n_exit(original, pid, str);
		(*cmd)->argv[0] = find_if_executable((*cmd)->argv[0],
				ft_get_env("PATH"), 0);
	}
	if ((*cmd)->argv[0] == NULL)
		str_n_fd_free_n_exit(str, original);
	//name_of_file_free((*cmd)->name_file);
	if ((*cmd)->fd_in < 0 || (*cmd)->fd_out < 0)
		all_free_n_exit(original, pid, str);
	if (cmd_is_builtin((*cmd)->argv[0]))
		execute_builtin(str, cmd, original, pid);
	else
		execution_execve(cmd, original, str, pid);
	return (0);
}

// function to set up pipes for inter-process communication
//for each command in the commad line

void	execution(t_command_line **cmd_line)
{
	t_command_line	*updated;
	pid_t			*pid;
	int				rtrn;

	updated = *cmd_line;
	rtrn = piping(cmd_line);
	if (rtrn != 0)
		return (rtrn);
	pid = malloc(sizeof(pid_t) * command_len(updated)); 
	if (pid == NULL)
		return (50);
	func_fork(cmd_line, pid);
}
