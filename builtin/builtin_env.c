/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:54:21 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/15 12:26:16 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/* int	ft_built_in_env_fd(char **str, int fd)
{
	t_env01 **env;

	if (*str == NULL)
		return (0);
	env = address_of_env();
	ft_built_in_show_env_fd(env, fd);
	return (0);
} */

void	ft_built_in_show_env_fd(t_env01 **env, int fd)
{
	t_env01	*updated;

	updated = *env;
	while (updated)
	{
		if (ft_is_equal(updated->str))
		{
			ft_putstr_fd(updated->str, fd);
			ft_putchar_fd('\n', fd);
		}
		updated = updated->next;
	}
}
