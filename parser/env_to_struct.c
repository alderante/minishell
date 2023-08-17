/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:31:35 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/17 09:14:26 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/* typedef struct s_env
{
	char			*str;
	int				declare;
	struct s_env	*next;
}				t_env01;
 */
/* t_env01	*create_env_node(char *str, int declare)
{
	t_env01	*node;

	node = (t_env01 *)malloc(sizeof(t_env01));
	if (node)
	{
		node->str = ft_strdup(str);
		node->declare = declare;
		node->next = NULL;
	}
	return (node);
}

void	add_env_node(t_env01 **env_list, char *str, int declare)
{
	t_env01	*node;

	node = create_env_node(str, declare);
	if (node)
	{
		node->next = *env_list;
		*env_list = node;
	}
}

t_env01	*convert_env_to_list(char **env)
{
	t_env01	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	if (env)
	{
		while (env[i] != NULL)
		{
			add_env_node(&env_list, env[i], 1);
			i++;
		}
	}
	return (env_list);
}

void	free_env_list(t_env01 *env_list)
{
	t_env01	*temp;

	temp = env_list;
	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->str);
		free(temp);
	}
} */

/* void	print_env01_list(t_env01 *env_list)
{
	while (env_list)
	{
		printf("str: %s, declare: %d\n", env_list->str, env_list->declare);
		env_list = env_list->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env01	*env_list = convert_env01_to_list(env);
	print_env01_list(env_list);
	free_env_list(env_list);
	return 0;
} */
