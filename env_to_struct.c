/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:31:35 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/07 18:51:59 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* typedef struct s_env
{
	char			*str;
	int				declare;
	struct s_env	*next;
}				t_env;
 */
t_env	*create_env_node(char *str, int declare)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node)
	{
		node->str = strdup(str);
		node->declare = declare;
		node->next = NULL;
	}
	return (node);
}

void	add_env_node(t_env **env_list, char *str, int declare)
{
	t_env	*node;

	node = create_env_node(str, declare);
	if (node)
	{
		node->next = *env_list;
		*env_list = node;
	}
}

t_env	*convert_env_to_list(char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	if (env)
	{
		while (env[i] != NULL)
		{
			add_env_node(&env_list, env[i], 1);
		}
		i++;
	}
	return (env_list);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->str);
		free(temp);
	}
}

void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("str: %s, declare: %d\n", env_list->str, env_list->declare);
		env_list = env_list->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list = convert_env_to_list(env);
	print_env_list(env_list);
	free_env_list(env_list);
	return 0;
}
