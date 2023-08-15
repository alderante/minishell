/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:36:53 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/15 16:44:39 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	change_directory(char *path)
{
	char	*error_message;

	if (chdir(path) == -1)
	{
		error_message = strerror(errno);
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, error_message, strlen(error_message));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}

char	*get_home_directory(void)
{
	char		*home_dir;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		write(STDERR_FILENO, "cd: failed to get home directory\n", 32);
		return (NULL);
	}
	return (home_dir);
}

int	builtin_cd(char **args)
{
	char		*path;

	if (args[1] == NULL)
		path = get_home_directory();
	else if (args[2])
	{
		write(STDERR_FILENO, "Minishell: cd: too many arguments\n",
			ft_strlen("Minishell: cd: too many arguments\n"));
		return (1);
	}
	else
		path = args[1];

	if (path != NULL)
	{
		if (change_directory(path) != 0)
			return (1);
	}
	return (0);
}
