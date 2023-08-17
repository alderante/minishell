/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:16:42 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/17 15:38:10 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	heredoc_loop(char *line, char *delimiter, int fd)
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

int	create_heredoc_fd(t_command_line **cmd, t_token *token)
{
	int		fd;
	char	*delimiter;
	char	*line;
	t_token	*next_token;

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
	heredoc_loop(line, delimiter, fd);
	free(delimiter);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	next_token = token->next;
	free(token->token);
	free(next_token->token);
	token->token = NULL;
	token->next->token = NULL;
	return (fd);
}
