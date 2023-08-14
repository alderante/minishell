/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:03:05 by rkhinchi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/14 23:05:51 by rkhinchi         ###   ########.fr       */
=======
/*   Updated: 2023/08/14 16:41:50 by cpopolan         ###   ########.fr       */
>>>>>>> 057bf85573f489041f9fec97e37cd615d067cab6
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

<<<<<<< HEAD
int	ft_export_checker(char *tab, int equal)
{
	int	i;

	i = 0;
	if (equal < 3)
		return (1);
	if (ft_isalpha(tab[i]) != 1)
		return (1);
	while (tab[i] != '=')
	{
		if (ft_isalnum(tab[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

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

void	ft_built_in_export(char **tab, t_env01 **first)
{
	char		*value;
	char		*name;
	int			equal;
	t_env01		*env_list;

	env_list = *first;
	tab++;
	equal = ft_input_equal_position(*tab);
	if (ft_export_checker(*tab, equal) == 0)
	{
		name = ft_substr(*tab, 0, equal);
		value = ft_substr(*tab, equal + 1, ft_strlen(*tab));
		while (*tab)
		{
			env_list = ft_env_search(env_list, name);
			if (env_list != NULL)
			{
				free(env_list->str);
				env_list->str = ft_strdup(*tab);
			}
			else
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
			free(name);
			free(value);
			tab++;
		}
	}
}

=======
>>>>>>> 057bf85573f489041f9fec97e37cd615d067cab6
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
	else if (ft_strcmp01("env", str))
		ft_built_in_env((*original)->env_list);
	else if (ft_strcmp01("pwd", str))
		ft_built_in_pwd(args);
	else if (ft_strcmp01("export", str))
		ft_built_in_export(args, &((*original)->env_list));
	else if (ft_strcmp01("unset", str))
		ft_built_in_unset(args, &((*original)->env_list));
	free(pid);
	free_delete_add(NULL, FREE);
	free_all(original);
	return (0);
}

int	execute_builtin(t_command_line **cmd,
	t_command_line **original, pid_t *pid)
{
<<<<<<< HEAD
	execution_builtin((*cmd)->argv[0], (*cmd)->argv, original, pid);
=======
	//free(str);
	if (execution_builtin((*cmd)->argv[0], (*cmd)->argv, original, pid) == 2)
		exit(1);
	exit(0);
>>>>>>> 057bf85573f489041f9fec97e37cd615d067cab6
	return (0);
}