/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:14:40 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 13:10:45 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_input_redir(t_command_line **cmd, t_token *token, t_token *prev_token)
{
	int			fd;

	fd = open(token->next->token, O_RDONLY);
	if (fd == -1)
		return (-1);
	(*cmd)->fd_in = fd;
	if (prev_token)
	{
		prev_token->next = token->next->next;
		free(token->token);
		free(token->next->token);
		free(token->next);
		token = prev_token;
	}
	else
	{
		(*cmd)->single_token = token->next->next;
		free(token->token);
		free(token->next->token);
		free(token->next);
		token = (*cmd)->single_token;
	}
	return (0);
}

int	ft_input_redir_over(t_command_line **cmd, t_token *token)
{
	//token = token->next;
	if (token->next && token->next->token)
	{
		(*cmd)->heredoc_delimiter = ft_strdup(token->next->token);
		(*cmd)->fd_in = ft_create_heredoc_fd(cmd, token);
		if ((*cmd)->fd_in == -1)
			return (-1);
		return (1);
	}
	else
		return (-1);
}

int	ft_compare(t_command_line **cmd, t_token *token,
		t_token *prev_token, t_e_type type)
{
	int			rtrn;

	rtrn = 0;
	if (type == FILE_IN)
	{
		if (token->next && token->next->token)
		{
			if (ft_input_redir(cmd, token, prev_token) == -1)
				return (-1);
			return (1);
		}
		else
			return (-1);
	}
	else if (ft_strcmp01(token->token, (char [3]){-2, -2, '\0'}) == 1)
	{
		rtrn = ft_input_redir_over(cmd, token);
		if (rtrn == -1)
			return (-1);
		else if (rtrn == 1)
			return (1);
	}
	return (0);
}

int	ft_handle_input_redirection(t_command_line **cmd,
		t_token *updated, t_e_type type)
{
	t_token		*token;
	t_token		*prev_token;
	int			rtrn;

	(void)updated;
	rtrn = 0;
	if ((*cmd)->fd_in != 0) 
		close((*cmd)->fd_in);
	token = (*cmd)->single_token;
	prev_token = NULL;
	while (token)
	{
		rtrn = ft_compare(cmd, token, prev_token, type);
		if (rtrn == -1)
			return (-1);
		else if (rtrn == 1)
			break ;
		prev_token = token;
		token = token->next;
	}
	return (0);
}
