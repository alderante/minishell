/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:43:50 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/11 20:16:12 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
