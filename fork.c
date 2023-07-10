/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:10:14 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/10 13:32:21 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	process_forking(pid_t *pid, int i, t_command_line **cmd, 
			t_command_line **updated)
{
	/* signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); */
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		/* signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL); */
		big_executor(updated, cmd, pid);
	}
	if ((*updated)->fd_in != 0)
		close((*updated)->fd_in);
	if ((*updated)->fd_out != 1)
		close((*updated)->fd_out);
	return (0);
}

//open fd for redirections
// Command_len how many commands are there

int	func_fork(t_command_line **cmd, pid_t *pid)
{
	int				len;
	int				i;
	t_command_line	*updated;

	i = 0;
	updated = *cmd;
	len = command_len(updated);
	while (updated)
	{
		redirections_fd(&updated);
		updated = updated->next;
	}
	updated = *cmd;
	//Xno_fX
	while (i < len)
	{
		process_forking(pid, i, cmd, &updated);
		updated = updated->next;
		i++;
	}
	return (0);
}
