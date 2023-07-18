/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:10:14 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/18 17:44:56 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

//pwd | grep o > cazzo.txt
// p (*cmd_line)->argv[0]
/* (gdb) p (*cmd_line)->next->argv[0]
$6 = 0x5555555983b0 "grep"
(gdb) p (*cmd_line)->next->argv[1]
$7 = 0x555555598370 "o" */

/* minishell$> ls -l > cazzo.txt
(gdb) p (*cmd_line)->argv[0]
$1 = 0x5555555983a0 "ls"
(gdb) p (*cmd_line)->argv[1]
$2 = 0x555555598260 "-l"
(gdb) p (*cmd_line)->argv[2]
$3 = 0x0
(gdb) p (*cmd_line)->next->argv[0]
Cannot access memory at address 0x18 */

int	execution_bd_fd(char *str, char **args,
		t_command_line **original, pid_t *pid)
{
	(void)(pid);
	if (str == NULL)
		return (0);
	/* if (ft_strcmp01("exit", str))
	{
		exit_bltin(args, original, pid);
		return (1);
	} */
	if (ft_strcmp01("cd", str))
		builtin_cd(args);
	else if (ft_strcmp01("echo", str))
		ft_built_in_echo_fd(args, (*original)->fd_out);
	/* else if (ft_strcmp01("env", str))
		ft_built_in_env_fd(args, (*original)->fd_out); */
	else if (ft_strcmp01("pwd", str))
		ft_built_in_pwd_fd(args, (*original)->fd_out);
	/* else if (ft_strcmp01("export", str))
		ft_built_in_export_fd(args, (*original)->fd_out);
	else if (ft_strcmp01("unset", str))
		ft_built_in_unset(args); */
	return (0);
}

int	no_func_fork(t_command_line **cmd, pid_t *pid)
{
	if ((*cmd)->argv == NULL)
		return (0);
	else if (execution_bd_fd((*cmd)->argv[0],
			(*cmd)->argv, cmd, pid) != 0)
	{
		return (0);
	}
	return (0);
}

int	process_forking(pid_t *pid, int i, t_command_line **cmd, 
			t_command_line **updated)
{
	/* signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); */
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		/* signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL); */
		big_executor(updated, cmd, pid);
	}
	/* else	
	{	
		big_executor(updated, cmd, pid);
		//exit(0);
	} */
	if ((*updated)->fd_in != 0)
		close((*updated)->fd_in);
	if ((*updated)->fd_out != 1)
		close((*updated)->fd_out);
	return (0);
}

/* int	av_to_struct(t_command_line **cmd, char **av)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (av[size] != NULL)
	{
		size++;
	}
	(*cmd)->argv = malloc(sizeof(char *) * (size + 1));
	if ((*cmd)->argv == NULL)
		return (-1);
	while (i < size) 
	{
		(*cmd)->argv[i] = strdup(av[i]);
		if ((*cmd)->argv[i] == NULL)
			return (-1);
		i++;
	}
	(*cmd)->argv[size] = NULL;
	return (0);
} */

//open fd for redirections
// Command_len how many commands are there

int	func_fork(t_command_line **cmd, pid_t *pid, char **av)
{
	int				len;
	int				i;
	t_command_line	*updated;

	(void)(av);
	i = 0;
	updated = *cmd;
	len = command_len(updated);
	while (updated)
	{
		redirections_fd(&updated);
		updated = updated->next;
	}
	//av_to_struct(cmd, av);
	organise_arg(cmd);
	updated = *cmd;
	if (len == 1 && cmd_is_builtin(updated->argv[0]))
	{
		return (no_func_fork(cmd, pid));
	}
	while (i < len)
	{
		process_forking(pid, i, cmd, &updated);
		updated = updated->next;
		i++;
	}
	return (0);
}
