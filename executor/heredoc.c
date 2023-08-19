/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:16:42 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/19 17:33:02 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_heredoc_loop(char *line, char *delimiter, int fd)
{
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
}

int	ft_create_heredoc_fd(t_command_line **cmd, t_token *token)
{
	char	*delimiter;
	char	*line;
	t_token	*next_token;

	line = NULL;
	delimiter = ft_strdup((*cmd)->heredoc_delimiter);
	free((*cmd)->heredoc_delimiter);
	(*cmd)->heredoc_delimiter = NULL;
	(*cmd)->fd_in = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if ((*cmd)->fd_in == -1)
	{
		free(delimiter);
		return (-1);
	}
	ft_heredoc_loop(line, delimiter, (*cmd)->fd_in);
	free(delimiter);
	close((*cmd)->fd_in);
	(*cmd)->fd_in = open(".heredoc_tmp", O_RDONLY);
	next_token = token->next;
	free(token->token);
	free(next_token->token);
	token->token = NULL;
	token->next->token = NULL;
	return ((*cmd)->fd_in);
}
