/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/07 16:08:54 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_node_deleter(t_token *first)
{
	t_token	*node;

	node = first;
	while (first)
	{
		free(first->token);
		first = first->next;
		free(node);
		node = first;
	}
}

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

	node = malloc(sizeof(t_token) * 1);
	if (ft_node_builtin_typer(token) != 1)
		node->type = ft_node_builtin_typer(token);
	else if (ft_node_redirect_typer(token) != 1)
		node->type = ft_node_redirect_typer(token);
	else
		node->type = NON;
	node->pos = pos;
	node->token = ft_strdup(token);
	//node->token = ft_strjoin(node->token, ";");
	node->next = NULL;
	return (node);
}

t_token	*ft_initialize(t_command_line *first_cmd)
{
	int				i;
	t_token			*node;
	t_token			*first_token;
	t_command_line	*temp;
	char			**current_line;

	i = 0;
	temp = first_cmd;
	while (first_cmd)
	{
		i = 0;
		current_line = easy_split(first_cmd->new_matrix_string);
		node = ft_newnode(current_line[i], i + 1);
		first_token = node;
		first_cmd->single_token = node;
		i++;
		while (current_line[i])
		{
			node->next = ft_newnode(current_line[i], i + 1);
			node = node->next;
			i++;
		}
		first_cmd = first_cmd->next;
		i++;
	}
	first_cmd = temp;
	node = first_token;
	ft_final_stamper(first_cmd);
	return (first_token);
}