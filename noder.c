/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/06 17:19:23 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_node_deleter(t_token *first)
{
    t_token *node;

    node = first;
    while(first)
    {
        free(first->token);
        first = first->next;
        free(node);
        node = first;
    }
}

void ft_final_stamper(t_command_line *cmd_line)
{
	int	i;
	i = 0;
    t_token *node;
    node = cmd_line->single_token;
	while (cmd_line)
    {
        while(node)
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
			i++;
		}
    }
}

t_token	*ft_newnode(char *token, int pos)
{
	t_token		*node;
    
    node = malloc(sizeof(t_token) * 1);
    if (strcmp(token, "echo") == 0)
        node->type = BUILTIN;
    else if (strcmp(token, "cd") == 0)
        node->type = BUILTIN;
    else if (strcmp(token, "pwd") == 0)
        node->type = BUILTIN;
    else if (strcmp(token, "export") == 0)
        node->type = BUILTIN;
    else if (strcmp(token, "unset") == 0)
        node->type = BUILTIN;
    else if (strcmp(token, "env") == 0)
        node->type = BUILTIN;
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
    int     i;
    t_token	*node;
    t_token	*first_token;
	t_command_line	*temp;
	char    **current_line;

    // printf("check actual line %s\n", first->new_matrix_string);
    // printf("check next line   %s\n", first->next->new_matrix_string);
	i = 0;
	temp = first_cmd;
	while(first_cmd)
	{
		printf("\n __NEW MATRIX STRING %d_____________\n", i);
		printf("|\n");
		printf("|   New Matrix String: %s\n", first_cmd->new_matrix_string);
		printf("|__________________________________\n\n");
        
		i = 0;
		
		current_line = easy_split(first_cmd->new_matrix_string);
        node = ft_newnode(current_line[i], i + 1);
		first_token = node;
	    //ft_final_stamper(first_token);
		first_cmd->single_token = node;
		i++;
		printf("node is %s\n", node->token);
		while(current_line[i])
        {
			node->next = ft_newnode(current_line[i], i + 1);
			printf("node is %s\n", node->next->token);
		//	ft_final_stamper(node);
			node = node->next;
			i++;
        }
        first_cmd = first_cmd->next;
		i++;
	}
    
	first_cmd = temp;
    node = first_token;

	printf("1: %s\n", first_cmd->single_token->token);
	printf("1: %u\n", first_cmd->single_token->type);
	printf("2: %s\n", first_cmd->single_token->next->token);
	printf("3: %s\n", first_cmd->next->single_token->token);
	printf("4: %s\n", first_cmd->next->single_token->next->token);


    //ft_final_stamper(first_cmd);
	return (first_token);
}