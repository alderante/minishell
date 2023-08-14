/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:50:36 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/14 13:43:39 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int g_exit_status;

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int create_heredoc_fd(t_command_line **cmd, t_token **token)
{
	int		fd;
	size_t	heredoc_len;
	char	*delimiter;
	char	*line;

	line = NULL;
	fd = 0;
	if (!(*cmd)->heredoc_delimiter)
		return (-1);

	delimiter = ft_strdup((*cmd)->heredoc_delimiter);
	fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		free(delimiter);
		return (-1);
	}

	heredoc_len = ft_strlen(delimiter);

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}

		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}

	free(delimiter);
	close(fd);

	fd = open(".heredoc_tmp", O_RDONLY);
	(*token)->token = NULL;
	(*token)->next->token = NULL;
	return (fd);
}

int handle_input_redirection(t_command_line **cmd)
{
	t_token		*token;
	t_token		*prev_token;
	int			fd;

	if ((*cmd)->fd_in != 0) 
		close((*cmd)->fd_in);

	token = (*cmd)->single_token;
	prev_token = NULL;
	while (token)
	{
		if (ft_strcmp01(token->token, "<") == 1) 
		{
			printf("TOKEN01 << : %s\n", token->token);
			if (token->next && token->next->token)
			{
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
				break ;
			}
			else
				return (-1);
		}
		else if (ft_strcmp01(token->token, "<<") == 1)
		{
			if (token->next && token->next->token)
			{
				printf("TOKEN02 << : %s\n", token->token);
				(*cmd)->heredoc_delimiter = ft_strdup(token->next->token);
				printf("heredoc_delimiter %s\n", (*cmd)->heredoc_delimiter);
				(*cmd)->fd_in = create_heredoc_fd(cmd, &token);
				if ((*cmd)->fd_in == -1)
					return (-1);
				break ;
			}
			else
				return (-1);
		}
		prev_token = token;
		token = token->next;
	}
	return (0);
}

int handle_output_redirection(t_command_line **cmd)
{
	t_token		*token;
	int			fd;
	t_token		*next_token;

	if ((*cmd)->fd_out != 1)
		close((*cmd)->fd_out);

	token = (*cmd)->single_token;
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
	return (0);
}

int	redirections_fd(t_command_line **cmd)
{
	t_token			*updated;
	t_command_line	**tmp;


	tmp = cmd;
	updated = (*cmd)->single_token;
	while (updated)
	{
		if (updated->type == FILE_IN || updated->type == HERE_DOC)
			handle_input_redirection(tmp);
		if (updated->type == FILE_OUT || updated->type == FILE_OUT_OVER)
			handle_output_redirection(tmp);
		updated = updated->next;
	}
	return (0);
}
