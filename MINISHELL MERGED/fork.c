/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:10:14 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/12 18:25:50 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

static void	init_arg(t_command_line *cmd)
{
	t_token	*updated_t;
	int		i;

	updated_t = cmd->single_token;
	i = 0;
	while (updated_t)
	{
		if (updated_t->type == ARG || updated_t->type == BUILTIN)
		{
			cmd->argv[i] = updated_t->token;
			i++;
		}
		updated_t = updated_t->next;
	}
	cmd->argv[i] = NULL;
}

static int	nbr_arg_cmd(t_command_line *cmd)
{
	t_token	*updated_t;
	int		len;

	len = 0;
	updated_t = cmd->single_token;
	while (updated_t)
	{
		if (updated_t->type == ARG || updated_t->type == BUILTIN)
			len++;
		updated_t = updated_t->next;
	}
	return (len);
}

int	organise_arg(t_command_line **cmd)
{
	t_command_line	*updated_b;
	int				len_arg;
	char			**new;

	updated_b = *cmd;
	while (updated_b)
	{
		len_arg = nbr_arg_cmd(updated_b);
		new = malloc(sizeof(char *) * (len_arg + 1));
		if (new == NULL)
			return (50);
		updated_b->argv = new;
		init_arg(updated_b);
		updated_b = updated_b->next;
	}
	return (0);
}

int	ft_strcmp01(char *str, char *in)
{
	int	len_str;
	int	len_in;
	int	i;

	i = 0;
	len_str = 0;
	len_in = 0;
	len_str = ft_strlen(str);
	len_in = ft_strlen(in);
	if (len_str != len_in)
		return (0);
	while (i < len_in)
	{
		if (str[i] != in[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_built_in_pwd_fd(char **str, int fd)
{
	char	*pwd;

	if (*str == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	g_exit_status = 0;
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
	return (0);
}

extern int	g_exit_status;

int	ft_check_n(char **str)
{
	int	i;
	int	y;
	int	cpt;

	cpt = 0;
	y = 0;
	i = 0;
	while (str[i] && ft_strlen(str[i]) >= 2)
	{
		if (str[i][y] == '-' && str[i][y + 1] == 'n')
		{
			y++;
			while (str[i][y] == 'n')
				y++;
			if (y == (int)ft_strlen(str[i]))
				cpt++;
		}
		else
			return (cpt);
		i++;
		y = 0;
	}
	return (cpt);
}

int	ft_built_in_echo_fd(char **str, int fd)
{
	int	i;
	int	y;

	str++;
	y = 0;
	i = ft_check_n(str);
	if (i > 0)
		y++;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (y == 0)
		ft_putchar_fd('\n', fd);
	g_exit_status = 0;
	return (0);
}

int	execution_bd_fd(char *str, char **args,
		t_command_line **original, pid_t *pid)
{
	(void)(pid);
	if (str == NULL)
		return (0);
	/* if (ft_strcmp("exit", str))
	{
		exit_bltin(args, original, pid);
		return (1);
	}
	if (ft_strcmp("cd", str))
		ft_built_in_cd(args);*/
	else if (ft_strcmp01("echo", str))
		ft_built_in_echo_fd(args, (*original)->fd_out);
	/* else if (ft_strcmp("env", str))
		ft_built_in_env_fd(args, (*original)->fd_out); */
	else if (ft_strcmp01("pwd", str))
		ft_built_in_pwd_fd(args, (*original)->fd_out);
	/* else if (ft_strcmp("export", str))
		ft_built_in_export_fd(args, (*original)->fd_out);
	else if (ft_strcmp("unset", str))
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

int	av_to_struct(t_command_line **cmd, char **av)
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
}
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
