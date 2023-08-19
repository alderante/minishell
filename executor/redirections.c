/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:50:36 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/19 17:34:17 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	g_exit_status;

int	ft_file_out(t_command_line **cmd,
		t_token *updated, t_token *token)
{
	int			fd;
	t_token		*next_token;

	if (updated->next && updated->next->token)
	{
		fd = open(updated->next->token, O_WRONLY
				| O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return (-1);
		(*cmd)->fd_out = fd;
		next_token = token->next;
		free(token->token);
		token->token = NULL;
		token->next = next_token->next;
		free(next_token->token);
		free(next_token);
		return (0);
	}
	else
		return (-1);
}

int	ft_file_out_over(t_command_line **cmd, t_token *token)
{
	int			fd;
	t_token		*next_token;

	if (token->next && token->next->token)
	{
		fd = open(token->next->token, O_WRONLY
				| O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			return (-1);
		(*cmd)->fd_out = fd;
		next_token = token->next;
		free(token->token);
		token->token = NULL;
		token->next = next_token->next;
		free(next_token->token);
		free(next_token);
		return (0);
	}
	else
		return (-1);
}

int	ft_handle_output_redirection(t_command_line **cmd,
		t_token *updated, t_e_type type)
{
	t_token		*token;

	if ((*cmd)->fd_out != 1)
		close((*cmd)->fd_out);
	token = updated;
	if (type == FILE_OUT)
	{
		if (ft_file_out(cmd, updated, token) == -1)
			return (-1);
	}
	else if (type == FILE_OUT_OVER)
	{
		if (ft_file_out_over(cmd, token) == -1)
			return (-1);
	}
	return (0);
}

int	ft_redirections_fd(t_command_line **cmd)
{
	t_token			*updated;

	updated = (*cmd)->single_token;
	while (updated)
	{
		if (updated->type == FILE_IN || updated->type == HERE_DOC)
			ft_handle_input_redirection(cmd, updated, updated->type);
		if (updated->type == FILE_OUT || updated->type == FILE_OUT_OVER)
			ft_handle_output_redirection(cmd, updated, updated->type);
		updated = updated->next;
	}
	return (0);
}

/* t_token		*token;
	int			fd;
	t_token		*next_token;

	if ((*cmd)->fd_out != 1)
		close((*cmd)->fd_out);

	token = (*cmd)->single_token;
	printf("token->token %s\n",token->token);
	printf("token->next->token %s\n",token->next->token);
	while (token)
	{
		if (ft_strcmp(token->token, ">") == 0)
		{
			printf("token->next->token %s\n",token->next->token);
			if (token->next && token->next->token)
			{
				fd = open(token->next->token, O_WRONLY
						| O_CREAT | O_TRUNC, 0666);
				if (fd == -1)
					return (-1);
				(*cmd)->fd_out = fd;
				next_token = token->next;
				free(token->token);
				token->token = NULL;
				token->next = next_token->next;
				free(next_token->token);
				free(next_token);
				break ;
			}
			else
				return (-1);
		}
		else if (ft_strcmp(token->token, ">>") == 0)
		{
			if (token->next && token->next->token)
			{
				fd = open(token->next->token, O_WRONLY
						| O_CREAT | O_APPEND, 0666);
				if (fd == -1)
					return (-1);
				(*cmd)->fd_out = fd;
				next_token = token->next;
				free(token->token);
				token->token = NULL;
				token->next = next_token->next;
				free(next_token->token);
				free(next_token);
				break ;
			}
			else
				return (-1);
		}
		token = token->next;
	}
	return (0); */
