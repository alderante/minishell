/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enveloper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:55:56 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/06 17:20:01 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ft_strcmp(char *str1, char *str2)
{
	while(str1 && str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return(*str1 - *str2);
}
*/

t_env	*noder(char *str)
{
	t_env	*node;
	int		i;

	i = 0;
	while(str[i] != '=')
			i++;
	node = malloc(sizeof(t_env));
	node->name = ft_substr(str, 0, i);
	node->value = ft_substr(str, i + 1, ft_strlen(str));
	node->exp = 1;
	node->next = NULL;
	return(node);
}


void	ft_print_env(t_env *my_env)
{
	while(my_env)
	{
		printf("%s=%s\n", my_env->name, my_env->value);
		my_env = my_env->next;
	}
}

t_env	*ft_env_noder(char **envp)
{
	t_env	*node;
	t_env	*temp;
	int		j;

	temp = NULL;
	if(envp[0])
	{
		node = noder(envp[0]);
		j = 1;
		temp = node;
		while(envp[j])
		{
			node->next = noder(envp[j]);
			node = node->next;
			j++;
		}
		//ft_print_env(temp);
	}
	return(temp);
}