/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:43:50 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 11:18:58 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	ft_init_arg(t_command_line *cmd)
{
	t_token	*updated_t;
	int		i;

	i = 0;
	updated_t = cmd->single_token;
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

static int	ft_nbr_arg_cmd(t_command_line *cmd)
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

int	ft_organise_arg(t_command_line **cmd)
{
	t_command_line	*updated_b;
	int				len_arg;
	char			**new;

	updated_b = *cmd;
	while (updated_b)
	{
		len_arg = ft_nbr_arg_cmd(updated_b);
		new = malloc(sizeof(char *) * (len_arg + 1));
		if (new == NULL)
			return (50);
		updated_b->argv = new;
		ft_init_arg(updated_b);
		updated_b = updated_b->next;
	}
	return (0);
}
