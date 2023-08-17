/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/17 10:42:24 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_final_stamper(t_command_line *cmd_line)
{
	t_token	*node;

	node = cmd_line->single_token;
	while (cmd_line)
	{
		printf("\n ___+++___+++ NEW MATRIX STRING +++___+++___+++___+++___\n");
		printf("|\n");
		printf("|   New Matrix String: %s\n", cmd_line->new_matrix_string);
		printf("|\n\n");
		while (node)
		{
			printf("\n __INIZIO NODO TOKEN_______________\n");
			printf("|\n");
			printf("|\n");
			printf("|   Pos:   %d\n", node->pos);
			printf("|   Type:  %d\n", node->type);
			printf("|   Token: %s\n", node->token);
			printf("|\n");
			printf("|________________FINE NODO TOKEN___\n\n");
			node = node->next;
		}
		if (cmd_line->next)
		{
			cmd_line = cmd_line->next;
			node = cmd_line->single_token;
		}
		else
			break ;
	}
}

t_token	*ft_newnode(char *token, int pos)
{
	t_token		*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (ft_node_builtin_typer(token) != 1)
	{
		node->type = ft_node_builtin_typer(token);
	}
	else if (ft_node_redirect_typer(token) != 1)
	{
		node->type = ft_node_redirect_typer(token);
	}
	else
		node->type = ARG;
	node->pos = pos;
	node->token = ft_strdup(token);
	node->next = NULL;
	return (node);
}

void	ft_initialize01(t_init *ciccio, t_command_line *first_cmd,
		t_env01 *env_list)
{
	while (ciccio->current_line[ciccio->i])
	{
		ciccio->node->next = ft_newnode
			(ciccio->current_line[ciccio->i], ciccio->i + 1);
		first_cmd->env_list = env_list;
		ciccio->node = ciccio->node->next;
		ciccio->i++;
	}
}

void	ft_free_initialize(t_init *ciccio)
{
	ciccio->j = 0;
	while (ciccio->current_line[ciccio->j])
	{
		free(ciccio->current_line[ciccio->j]);
		ciccio->j++;
	}
	free(ciccio->current_line);
}

t_token	*ft_initialize(t_command_line *first_cmd, t_env01 *env_list)
{
	t_init	ciccio;

	ciccio.i = 0;
	ciccio.temp = first_cmd;
	ciccio.node = NULL;
	ciccio.first_token = NULL;
	ciccio.current_line = NULL;
	while (first_cmd)
	{
		ciccio.i = 0;
		ciccio.current_line = quote_cleaner_split(first_cmd->new_matrix_string,
				env_list);
		ciccio.node = ft_newnode(ciccio.current_line[ciccio.i], ciccio.i + 1);
		ciccio.first_token = NULL;
		first_cmd->env_list = env_list;
		first_cmd->single_token = ciccio.node;
		ciccio.i++;
		ft_initialize01(&ciccio, first_cmd, env_list);
		first_cmd = first_cmd->next;
		ft_free_initialize(&ciccio);
		ciccio.i++;
	}
	first_cmd = ciccio.temp;
	ciccio.node = ciccio.first_token;
	return (ciccio.first_token);
}
