/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:39:27 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/19 17:27:28 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

static int	ft_llong_limit_ret(char *str)
{
	int			i;
	long long	res;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && i < 18)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_llong_limit_check(char *str)
{
	long long	res;
	int			sign;
	int			i;

	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(&str[i]) < 19)
		return (0);
	else if (ft_strlen(&str[i]) > 19)
		return (1);
	res = ft_llong_limit_ret(&str[i]);
	if (res > LLONG_MAX / 10)
		return (1);
	else if ((sign == 1 && str[i + 18] - '0' < 8) \
		|| (sign == -1 && str[i + 18] - '0' <= 8))
		return (0);
	return (1);
}

int	ft_digit_check(char *str)
{
	int	i;
	int	check;

	check = 0;
	if (str)
	{
		i = 0;
		if (str[i] == '-' || str[i] == '+' || ft_isdigit(str[i]))
			i++;
		else
			return (1);
		while (!check && str[i])
		{
			if (!ft_isdigit(str[i]))
				check = 1;
			i++;
		}
	}
	return (check);
}

void	ft_if_ex(t_command_line **cmd)
{
	free((*cmd)->input);
	free((*cmd)->pid);
	ft_env_deleter((*cmd)->env_list);
	ft_free_all(cmd);
	exit(g_exit_status);
}

int	ft_built_in_exit(char **args, t_command_line **cmd)
{
	int	ex;

	args++;
	ex = 0;
	if (!(*cmd)->next)
		ex = 1;
	if (args[0] && (ft_digit_check(*args) || ft_llong_limit_check(*args)))
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(*args, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
	}
	else if (args[0] && args[1])
	{
		ex = 0;
		g_exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else if (args[0])
		g_exit_status = ft_atoi(*args) % 256;
	if (ex)
		ft_if_ex(cmd);
	return (0);
}
