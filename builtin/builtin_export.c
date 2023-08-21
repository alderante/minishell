/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:40:39 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 14:21:13 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_input_equal_position(char *tab)
{
	int	equal;
	int	i;

	i = 0;
	equal = 0;
	if (!tab)
		return (equal);
	while (tab[i])
	{
		if (tab[i] == '=')
			return (i);
		i++;
	}
	return (equal);
}

void	ft_env_printer(t_env01 *tmp)
{
	while (tmp)
	{
		printf("declare -x %s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	ft_built_in_export02(char **tab, t_env01 **first, t_env01 *env_list)
{
	env_list = *first;
	if (env_list == NULL)
	{
		env_list = malloc(sizeof(t_env01));
		env_list->str = ft_strdup(*tab);
		env_list->next = NULL;
	}
	else
	{
		while (env_list->next)
			env_list = env_list->next;
		env_list->next = noder(*tab);
	}
}

void	ft_built_in_export01(char **tab, t_env01 **first)
{
	char	*value;
	char	*name;
	int		equal;
	t_env01	*env_list;

	env_list = *first;
	while (*tab)
	{
		equal = ft_input_equal_position(*tab);
		if (ft_export_checker(*tab, equal) == 0)
		{
			name = ft_substr(*tab, 0, equal);
			value = ft_substr(*tab, equal + 1, ft_strlen(*tab));
			env_list = ft_env_search(env_list, name);
			if (env_list != NULL)
			{
				free(env_list->str);
				env_list->str = ft_strdup(*tab);
			}
			else
				ft_built_in_export02(tab, first, env_list);
			ft_free_built_in_export01(name, value);
		}
		tab++;
	}
}

void	ft_built_in_export(char **tab, t_env01 **first)
{
	tab++;
	if (*tab == NULL)
		ft_env_printer(*first);
	else
		ft_built_in_export01(tab, first);
}
