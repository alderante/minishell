/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/03 16:30:04 by cpopolan         ###   ########.fr       */
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

void ft_final_stamper(t_token *first)
{
	int	i;
	i = 0;
    t_token *node;
    node = first;
	while (node)
    {
        printf("\n _____INIZIO NODO___________________\n");
        printf("|\n");
        printf("|\n");
        printf("|   Pos:   %d\n", node->pos);
        printf("|   Type:  %d\n", node->type);
        printf("|   Token: %s\n", node->token);
        printf("|\n");
        printf("|_____________________FINE NODO_____\n\n");
        node = node->next;
        i++;
    }
}

t_token	*ft_newnode(char *row, int pos)
{
	t_token		*node;

    
    node = malloc(sizeof(t_token) * 1);
    if (strcmp(row, "echo") == 0)
        node->type = BUILTIN;
    else if (strcmp(row, "cd") == 0)
        node->type = BUILTIN;
    else if (strcmp(row, "pwd") == 0)
        node->type = BUILTIN;
    else if (strcmp(row, "export") == 0)
        node->type = BUILTIN;
    else if (strcmp(row, "unset") == 0)
        node->type = BUILTIN;
    else if (strcmp(row, "env") == 0)
        node->type = BUILTIN;
    else
        node->type = NON;
    node->pos = pos;
    node->token = strdup(row);
   

    //node->token = ft_strjoin(node->token, ";");
        
    node->next = NULL;
	return (node);
}

t_token	*ft_initialize(char **new_matrix)
{
    int     i;
    t_token	*node;
    t_token	*first;
    t_command_line *cmd_line;

    while(new_matrix)
    {
        cmd_line->new_matrix_string = new_matrix[i];
        cmd_line = cmd_line->next;
        i++;
    }

    // ora devo passare le singole new_matrix_string ad uno split che poi a sua volta passi ogni singolo aromento alla struct token che lo paragoni a tuttu
    // i type possibili.




    i = 0;
	node = ft_newnode(new_matrix[0], i + 1);
    first = node;
    i++;
    while (new_matrix[i])
	{
		node->next = ft_newnode(new_matrix[i], i + 1);
		node = node->next;
        i++;
	}
    ft_final_stamper(first);
	return (first);
}