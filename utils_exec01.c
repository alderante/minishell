/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:14:56 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/07 15:55:48 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

extern int	g_exit_status;

void	free_token(t_command_line **cmd_line)
{
	t_token	*tok;

	while ((*cmd_line)->single_token)
	{
		tok = (*cmd_line)->single_token->next;
		if ((*cmd_line)->single_token->str)
			free((*cmd_line)->single_token->str);
		free((*cmd_line)->single_token);
		(*cmd_line)->single_token = tok;
	}
}

int	free_all(t_command_line **cmd_line)
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
				free_token(cmd_line);
			if ((*cmd_line)->name_file)
				free((*cmd_line)->name_file);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}

void	all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str)
{
	free_all(cmd);
	func_2_free_all_env();
	free(pid);
	free(str);
	exit(1);
}

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
