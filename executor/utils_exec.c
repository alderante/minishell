/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:53:37 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 11:21:03 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_all_fd_close(t_command_line **cmd)
{
	t_command_line	*updated;

	updated = *cmd;
	while (updated)
	{
		if (updated->fd_in != 0)
			close(updated->fd_in);
		if (updated->fd_out != 1)
			close(updated->fd_out);
		updated = updated->next;
	}
}

int	ft_command_len(t_command_line *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	ft_freeing_matrix_nfd(int **nfd)
{
	int		i;

	i = 0;
	while (nfd[i])
	{
		free(nfd[i]);
		i++;
	}
	free(nfd);
}

void	ft_all_fd_close_n_exit(t_command_line **original)
{
	ft_all_fd_close(original);
	exit (50);
}

int	ft_cmd_is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp01("exit", str))
		return (1);
	if (ft_strcmp01("cd", str))
		return (1);
	else if (ft_strcmp01("echo", str))
		return (1);
	else if (ft_strcmp01("env", str))
		return (1);
	else if (ft_strcmp01("pwd", str))
		return (1);
	else if (ft_strcmp01("export", str))
		return (1);
	else if (ft_strcmp01("unset", str))
		return (1);
	return (0);
}
