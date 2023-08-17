/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:03:11 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/17 15:38:18 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

char	*cmd_not_found_free_split(char *str, char **split_path)
{
	free_split(split_path);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n",
		ft_strlen(": command not found\n"));
	return (NULL);
}

char	*cmd_not_found_free(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n",
		ft_strlen(": command not found\n"));
	free(str);
	return (NULL);
}

char	*get_acces(char *str, char *path)
{
	char	*back_slash;
	char	*new;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	new = ft_strjoin(back_slash, str);
	free(back_slash);
	if (new == NULL)
		return (NULL);
	return (new);
}
/* If the file can be executed by the calling process, 
the access() function will return 0. */

int	try_acces(char *str, char *path)
{
	char	*try;

	try = get_acces(str, path);
	if (try == NULL)
		return (50);
	if (access(try, X_OK) == 0)
	{
		free(try);
		return (1);
	}
	free(try);
	return (0);
}

char	*find_if_executable(char *str, char *path, int i)
{
	int		ret;
	char	**split_path;
	char	*try;

	if (str && (str[0] == '.' || str[0] == '/'))
		return (str);
	if (path == NULL)
	{
		//free(str);
		return (NULL);
	}
	split_path = ft_strsplit(path);
	if (split_path == NULL)
		return (cmd_not_found_free(str));
	while (split_path[i] && str[0] != '\0')
	{
		ret = try_acces(str, split_path[i]);
		if (ret == 1)
		{
			try = get_acces(str, split_path[i]);
			free_split(split_path);
			return (try);
		}
		if (ret == 50)
			return (free_split_ret_null(split_path));
		i++;
	}
	cmd_not_found_free_split(str, split_path);
	g_exit_status = 127;
	return (str);
}

/* This function is used to search for an executable file in the 
directories listed in the PATH environment variable.
The function original checks if the name of the command to 
execute contains a forward slash character (/). 
If it does, the function assumes that the name is 
a path to an executable file and returns it. */