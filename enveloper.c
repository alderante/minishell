/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enveloper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:55:56 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/04 15:57:57 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_env01	*noder(char *str)
{
	t_env01	*node;
	int		i;

	i = 0;
	while(str[i])
			i++;
	node = malloc(sizeof(t_env01));
	node->str = ft_substr(str, 0, i);
	//node->value = ft_substr(str, i + 1, ft_strlen(str));
	//node->exp = 1;
	node->next = NULL;
	return(node);
}


void	ft_print_env(t_env01 *my_env)
{
	while(my_env)
	{
		printf("%s\n", my_env->str);
		my_env = my_env->next;
	}
}

t_env01	*ft_env_noder(char **envp)
{
	t_env01	*node;
	t_env01	*temp;
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

// void ft_export(char *env, t_env01 *env_list)
// {
	
// }

// void ft_unset(char *env, t_env01 *env_list)
// {

// }