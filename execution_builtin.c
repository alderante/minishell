/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:03:05 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/06 14:30:45 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execution_builtin(char *str, char **args, t_command_line **original, pid_t *pid)
{
	if (str == NULL)
		return (0);
	/* if (ft_strcmp("exit", str))
	{
		exit_bltin(args, original, pid);
		return (free_in_builin(original, pid, 1));
	} */
	if (ft_strcmp("cd", str))
		ft_built_in_cd(args);
	else if (ft_strcmp("echo", str))
		ft_built_in_echo(args);
	else if (ft_strcmp("env", str))
		ft_built_in_env(args);
	else if (ft_strcmp("pwd", str))
		ft_built_in_pwd(args);
	else if (ft_strcmp("export", str))
		ft_built_in_export(args);
	else if (ft_strcmp("unset", str))
		ft_built_in_unset(args);
	free(pid);
	func_2_free_all_env();
	free_all(original);
	return (0);
}


int	execute_builtin(char **str, t_command_line **cmd,
	t_command_line **original, pid_t *pid)
{
	free(str);
	if (execution_builtin((*cmd)->argv[0], (*cmd)->argv, original, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}