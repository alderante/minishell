/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enveloper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:55:56 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/15 12:29:17 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_env_deleter(t_env01 *first)
{
	if (first->next)
		ft_env_deleter(first->next);
	free(first->str);
	free(first);
}

t_env01	*noder(char *str)
{
	t_env01	*node;

	node = malloc(sizeof(t_env01));
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

void	ft_built_in_env(char **args, t_env01 *my_env)
{
	if (args[1])
	{
		(void)(my_env);
		printf("env: ‘%s’: No such file or directory", args[1]);
	}
	else
	{
		while (my_env)
		{
			printf("%s\n", my_env->str);
			my_env = my_env->next;
		}
	}
}

void	ft_built_in_env_fd(char **args, t_env01 *my_env, int fd)
{
	(void)(fd);
	if (args[1])
	{
		(void)(my_env);
		printf("env: ‘%s’: No such file or directory\n", args[1]);
	}
	else
	{
		while (my_env)
		{
			printf("%s\n", my_env->str);
			my_env = my_env->next;
		}
	}
}

t_env01	*ft_env_noder(char **envp)
{
	t_env01	*node;
	t_env01	*temp;
	int		j;

	temp = NULL;
	if (envp[0])
	{
		node = noder(envp[0]);
		j = 1;
		temp = node;
		while (envp[j])
		{
			node->next = noder(envp[j]);
			node = node->next;
			j++;
		}
	}
	return (temp);
}
