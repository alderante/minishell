/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:03:05 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/09 14:17:10 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_offset(char *str)
{
	int		x;
	int		offset;
	int		eq_offset;

	x = 0;
	offset = 0;
	eq_offset = 0;
	while (str[x])
	{
		if (str[x] == 34 || str[x] == 39)
			offset++;
		else if (str[x] == '=' && !eq_offset)
			eq_offset++;
		x++;
	}
	return (offset + eq_offset);
}

char	*ft_givename(int x, char *str)
{
	char	*name;
	int		i;

	i = 0;
	name = malloc(sizeof(char) * x + 1);
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[x] = '\0';
	return (name);
}

char	*ft_givecontent(int x, char *str)
{
	char	*content;
	int		i;
	int		z;

	i = 0;
	z = 0;
	content = malloc(sizeof(char) * x + 1);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	if (str[i] == 34 || str[i] == 39)
		i++;
	while (str[i] != '\0' && (str[i] != 34 && str[i] != 39))
	{
		content[z] = str[i];
		z++;
		i++;
	}
	content[x] = '\0';
	return (content);
}

void ft_built_in_export(char **tab, t_env01 **first)
{
	char *value;
	char *name;
	int	offset;
	t_env01	*env_list;
	
	env_list = *first;
	tab++;
	printf("/1\n");
	offset = ft_offset(*tab);
	printf("/after offset\n");
	name = ft_givename(offset, *tab);
	printf("/after gn\n");
	value = ft_givecontent(offset, *tab);
	printf("/after gc\n");
	while(*tab)
	{
		env_list = ft_env_search(env_list, name);
		if(env_list != NULL)
		{	
			free(env_list->str);
			env_list->str = ft_strdup(*tab);
		}
		else
		{
			env_list = *first;
			if(env_list == NULL)
			{	
				env_list = malloc(sizeof(t_env01));
				env_list->str = ft_strdup(*tab);
				env_list->next = NULL;
			}	
			else
			{
				while(env_list->next)
				{
					env_list = env_list->next;
					env_list->next = malloc(sizeof(t_env01));
					env_list = env_list->next;
					env_list->str = ft_strdup(*tab);
					env_list->next = NULL;
				}
			}
		}
		tab++;
	}
	free(name);
	free(value);
}

int	execution_builtin(char *str, char **args,
		t_command_line **original, pid_t *pid)
{
	if (str == NULL)
		return (0);
	/* if (ft_strcmp("exit", str))
	{
		exit_bltin(args, original, pid);
		return (free_in_builin(original, pid, 1));
	} */
	if (ft_strcmp01("cd", str))
		builtin_cd(args);
	else if (ft_strcmp01("echo", str))
		ft_built_in_echo(args);
	/* else if (ft_strcmp01("env", str))
	 	ft_built_in_env(args); */
	else if (ft_strcmp01("pwd", str))
		ft_built_in_pwd(args);
	
	else if (ft_strcmp01("export", str))
		ft_built_in_export(args, &(*original)->env_list);
	
	// else if (ft_strcmp01("unset", str))
	// 	ft_built_in_unset(args);
	free(pid);
	free_delete_add(NULL, FREE);
	free_all(original);
	return (0);
}


int	execute_builtin(t_command_line **cmd,
	t_command_line **original, pid_t *pid)
{
	//free(str);
	if (execution_builtin((*cmd)->argv[0], (*cmd)->argv, original, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}
