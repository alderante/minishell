/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:50:36 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/06 16:34:07 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

int	redirect_file_out(t_command_line **cmd, t_token *updated, t_e_token type)
{
	if (type == FILE_OUT)
	{
		if ((*cmd)->fd_out != 1)
			close((*cmd)->fd_out);
		(*cmd)->fd_out = open(updated->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cmd)->fd_out == -1)
			return (-1);
	}
	else if (type == FILE_OUT_OVER)
	{
		if ((*cmd)->fd_out != 1)
			close((*cmd)->fd_out);
		(*cmd)->fd_out = open(updated->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cmd)->fd_out == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_in(t_command_line **cmd, t_token *updated, t_e_token type)
{
	if (type == FILE_IN)
	{
		if ((*cmd)->fd_in != 0)
			close((*cmd)->fd_in);
		(*cmd)->fd_in = open(updated->str, O_RDONLY);
		if ((*cmd)->fd_in == -1)
		{
			write(1, "minishell: ", 11);
			perror(updated->str);
			return (-1);
		}
	}
	//Xcreate_heredoc_fdX
	return (0);
}

int redirections_fd(t_command_line **cmd)
{
    t_token	*updated;

	updated = (*cmd)->original_token;
	while (updated)
	{
		if (updated->type == FILE_IN || updated->type == LIMITOR)
			if (redirect_file_in(cmd, updated, updated->type) == -1)
				return (-1);
		if (updated->type == FILE_OUT || updated->type == FILE_OUT_OVER)
			if (redirect_file_out(cmd, updated, updated->type) == -1)
				return (-1);
		updated = updated->next;
	}
	return (0);
}