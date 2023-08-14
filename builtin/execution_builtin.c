/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:03:05 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/15 00:07:30 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
	//free_delete_add(NULL, FREE);
	free_all(original);
	return (0);
}

int	execute_builtin(t_command_line **cmd,
	t_command_line **original, pid_t *pid)
{
	execution_builtin((*cmd)->argv[0], (*cmd)->argv, original, pid);
	return (0);
}
