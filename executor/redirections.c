/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:50:36 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/18 16:34:58 by rkhinchi         ###   ########.fr       */
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
	int fd;
	char *line;
	size_t len;
	size_t heredoc_len;
	char *delimiter;

	line = NULL;
	len = 0;
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
	write(1, "> ", 2);

	while (1)
	{
		ssize_t bytes_read = read(0, line, len);
		if (bytes_read == -1)
		{
			free(line);
			free(delimiter);
			return (-1);
		}
		if (bytes_read == 0)
			break;

		line[bytes_read] = '\0';
		if (ft_strcmp01(line, delimiter) == 0 || ft_strncmp(line, delimiter, heredoc_len) == 0)
			break;

		write(fd, line, bytes_read);
		write(1, "> ", 2);
	}

	free(line);
	free(delimiter);
	close(fd);

	fd = open(".heredoc_tmp", O_RDONLY);
	(*token)->token = NULL;
	(*token)->next->token = NULL;
	return (fd);
}

int handle_input_redirection(t_command_line **cmd)
{
	t_token *token;
	t_token *prev_token;
	int 	fd;

	if ((*cmd)->fd_in != 0) 
		close((*cmd)->fd_in);

	token = (*cmd)->single_token;
	prev_token = NULL;
	while (token)
	{
		if (ft_strcmp01(token->token, "<") == 0) 
		{
			if (token->next && token->next->token)
			{
				fd = open(token->next->token, O_RDONLY);
				if (fd == -1)
					return -1;
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
				break;
			}
			else
				return -1;
		}
		else if (ft_strcmp01(token->token, "<<") == 0)
		{
            if (token->next && token->next->token)
			{
				(*cmd)->heredoc_delimiter = ft_strdup(token->next->token);
				(*cmd)->fd_in = create_heredoc_fd(cmd, &token);
				if ((*cmd)->fd_in == -1)
					return -1;
                break;
			}
			else
				return -1;
		}
		prev_token = token;
		token = token->next;
	}
	return 0;
}


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int handle_output_redirection(t_command_line **cmd)
{
	t_token *token;
	int		fd;
	t_token *next_token;

	if ((*cmd)->fd_out != 1)
		close((*cmd)->fd_out);

	token = (*cmd)->single_token;
	while (token)
	{
		if (strcmp(token->token, ">") == 0)
		{
			if (token->next && token->next->token)
			{
				fd = open(token->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (fd == -1)
				    return (-1);
				(*cmd)->fd_out = fd;
				next_token = token->next;
				token->token = NULL;
				token->next = next_token->next;
				free(next_token->token);
				free(next_token);
				break;
			}
			else
				return (-1);
		}
		else if (strcmp(token->token, ">>") == 0)
		{
			if (token->next && token->next->token)
			{
				fd = open(token->next->token, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (fd == -1)
				    return (-1);
				(*cmd)->fd_out = fd;
				next_token = token->next;
				token->token = NULL;
				token->next = next_token->next;
				free(next_token->token);
				free(next_token);
				break;
			}
			else
				return (-1);
		}
		token = token->next;
    }
	return (0);
}

int redirections_fd(t_command_line **cmd)
{
    t_command_line *tmp;
    tmp = *cmd;

    handle_output_redirection(&tmp);

    /* tmp = *cmd;
    handle_input_redirection(&tmp); */

    return (0);
}
