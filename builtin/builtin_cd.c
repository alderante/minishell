/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:36:53 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/19 17:25:52 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

int	ft_change_directory(char *path)
{
	char	*error_message;

	if (chdir(path) == -1)
	{
		error_message = strerror(errno);
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, error_message, strlen(error_message));
		write(STDERR_FILENO, "\n", 1);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

char	*ft_get_home_directory(void)
{
	char		*home_dir;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		write(STDERR_FILENO, "cd: failed to get home directory\n", 32);
		g_exit_status = 1;
		return (NULL);
	}
	return (home_dir);
}

int	ft_builtin_cd(char **args)
{
	char		*path;

	if (args[1] == NULL)
		path = ft_get_home_directory();
	else if (args[2])
	{
		write(STDERR_FILENO, "Minishell: cd: too many arguments\n",
			ft_strlen("Minishell: cd: too many arguments\n"));
		g_exit_status = 1;
		return (1);
	}
	else
		path = args[1];
	if (path != NULL)
	{
		if (ft_change_directory(path) != 0)
			return (1);
	}
	return (0);
}
