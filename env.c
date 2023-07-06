/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:06:51 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/06 16:34:07 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_adress_env(void)
{
	static t_env	*new = NULL;

	return (&new);
}

//matrix_from_env convert a linked list of environment variables to a two-dimensional array of strings

char	**matrix_from_env(t_env **envp)
{
	char	**new;
	t_env	*updated;
	int		i;

	i = 0;
	updated = *envp;
	while (updated)
	{
		updated = updated->next;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	updated = *envp;
	i = 0;
	while (updated)
	{
		new[i] = updated->str;
		i++;
		updated = updated->next;
	}
	return (new);
}

int	free_delete_add(char *str, int mode)
{
	t_env	**env_list;

	env_list = address_of_env();
	if (mode == DELETE)
	{
		requested_env_delete(env_list, str);
		return (0);
	}
	if (mode == FREE)
		free_all_env(env_list);
	if (mode == ADD)
	{
		if (requested_env_ADD(env_list, str, 0) == 50)
		{
			free_all_env(env_list);
			return (50);
		}
	}
	return (0);
}

