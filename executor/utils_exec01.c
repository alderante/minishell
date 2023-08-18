/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:14:56 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 11:24:35 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

void	ft_free_token(t_command_line **cmd_line)
{
	t_token	*tok;

	while ((*cmd_line)->single_token)
	{
		tok = (*cmd_line)->single_token->next;
		if ((*cmd_line)->single_token->token)
			free((*cmd_line)->single_token->token);
		free((*cmd_line)->single_token);
		(*cmd_line)->single_token = tok;
	}
}

int	ft_free_all(t_command_line **cmd_line)
{
	t_command_line	*tmp;

	if (cmd_line)
	{
		while (*cmd_line)
		{
			tmp = (*cmd_line)->next;
			if ((*cmd_line)->new_matrix_string)
				free((*cmd_line)->new_matrix_string);
			if ((*cmd_line)->argv)
				free((*cmd_line)->argv);
			if ((*cmd_line)->single_token)
				ft_free_token(cmd_line);
			if ((*cmd_line)->name_file)
				free((*cmd_line)->name_file);
			if ((*cmd_line)->heredoc_delimiter)
				free((*cmd_line)->heredoc_delimiter);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}

void	ft_free_end(t_command_line **cmd, char *str)
{
	if (str)
		free(str);
	ft_free_all(cmd);
}

/* void	ft_all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str)
{
	ft_free_all(cmd);
	free_delete_add(NULL, FREE);
	func_2_ft_free_all_env();
	free(pid);
	free(str);
	exit(1);
} */

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	if (split)
		free(split);
}

char	*free_split_ret_null(char **split_path)
{
	free_split(split_path);
	return (NULL);
}
