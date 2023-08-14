/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:42:15 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/14 23:56:25 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int ft_check_unset_name(char *unset)
{
	int i;

	if (ft_isalpha(unset[0]) == 0 && unset[0] != '_')
		return (1);
	else
	{
		i = 1;
		while (unset[i])
		{	
			if (ft_isalnum(unset[i]) == 0 && unset[i] != '_')
				return (1);
			i++;
		}
	}
	return (0);
}

int ft_env_search_unset(t_env01 *env_list, char *searchname)
{
	char	*temp;
	int		row_position;

	row_position = 0;
	temp = ft_strjoin(searchname, "=");
	while (env_list != NULL)
	{
		if (!ft_strncmp(temp, env_list->str, ft_strlen(temp)))
			break ;
		env_list = env_list->next;
		row_position++;
	}
	free(temp);
	if(env_list == NULL)
		return(-1);
	return (row_position);
}

void ft_built_in_unset(char **tab, t_env01 **first)
{
	t_env01	*env_list;
	t_env01	*tmp;
	int		position;
	
	tab++;
	while(*tab)
	{
		if (ft_check_unset_name(*tab) == 1)
			ft_printf("bash: unset: `%s': not a valid identifier\n", *tab);
		else
		{
			position = ft_env_search_unset(*first, *tab) - 1;
			env_list = ft_env_search(*first, *tab);
			if (env_list != NULL)
			{	
				tmp = *first;
				while(position > 0)
				{
					tmp = tmp->next;
					position--;
				}
				if (position == -1)
					*first = tmp->next;
				else
					tmp->next = tmp->next->next;
				free(env_list->str);
				free(env_list);
			}
		}
		tab++;
	}
}
