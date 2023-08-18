/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:06:51 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 10:59:54 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

char	*ft_get_value_of_env(t_env01 **env, char *str, char *file_name);

int	check_equal_or_null(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	return (i);
}

char	*ft_get_str_of_env(t_env01 **env, char *str)
{
	t_env01	*cpy;
	int		len;

	len = check_equal_or_null(str);
	cpy = *env;
	while (cpy)
	{
		if (len == check_equal_or_null(cpy->str)
			&& !ft_strncmp(cpy->str, str, len))
			return (cpy->str);
		cpy = cpy->next;
	}
	return (NULL);
}

char	*ft_get_str(char *str)
{
	t_env01		**env_list;

	env_list = ft_address_of_env();
	return (ft_get_str_of_env(env_list, str));
}

/* char	*ft_get_env(char *str)
{
	t_env01	**env_list;

	env_list = ft_address_of_env();
	return (ft_get_value_of_env(env_list, str, ));
} */

char	*ft_get_value_of_env(t_env01 **env, char *str, char *file_name)
{
	t_env01	*cpy;
	int		len;

	len = check_equal_or_null(str);
	cpy = *env;
	while (cpy)
	{
		if (len == check_equal_or_null(cpy->str)
			&& !ft_strncmp(cpy->str, str, len))
			return (cpy->str + len + 1);
		cpy = cpy->next;
	}
	if (cpy == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		return (NULL);
	}
	return (NULL);
}

/* t_env	**ft_address_of_env(void)
{
	static t_env	*new = NULL;

	return (&new);
} */

/* ft_matrix_from_env convert a linked list of 
environment variables to a two-dimensional array of strings*/

// char	**ft_matrix_from_env(t_env01 **envp)
// {
// 	char	**new;
// 	t_env01	*updated;
// 	int		i;

// 	i = 0;
// 	updated = *envp;
// 	while (updated)
// 	{
// 		updated = updated->next;
// 		i++;
// 	}
// 	new = malloc(sizeof(char *) * (i + 1));
// 	new[i] = NULL;
// 	updated = *envp;
// 	i = 0;
// 	while (updated)
// 	{
// 		new[i] = updated->str;
// 		i++;
// 		updated = updated->next;
// 	}
// 	return (new);
// }

/* int	free_delete_add(char *str, int mode)
{
	t_env	**env_list;
	(void)(str);

	env_list = ft_address_of_env();
	if (mode == DELETE)
	{
		requested_env_delete(env_list, str);
		return (0);
	}
	if (mode == FREE)
		ft_free_all_env(env_list);
	 if (mode == ADD)
	{
		if (requested_env_ADD(env_list, str, 0) == 50)
		{
			ft_free_all_env(env_list);
			return (50);
		}
	}
	return (0);
} */