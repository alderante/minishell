/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/06/27 11:29:54 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_node_deleter(t_lexer *first)
{
    t_lexer *node;

    node = first;
    while(first)
    {
        free(first->token);
        first = first->next;
        free(node);
        node = first;
    }
}

void ft_final_stamper(t_lexer *first)
{
	int	i;
	i = 0;
    t_lexer *node;
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

t_lexer	*ft_newnode(char *row, int pos)
{
	t_lexer		*node;

    node = malloc(sizeof(t_lexer) * 1);
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
    if(node->type == NON)
        node->token = strdup(row);
    else if(node->type == BUILTIN)
        node->token = strdup(row);
    node->next = NULL;
	return (node);
}

t_lexer	*ft_initialize(char **matrix)
{
    int i;
    t_lexer	*node;
    t_lexer	*first;

    i = 0;
	node = ft_newnode(matrix[0], i + 1);
    first = node;
    i++;
    while (matrix[i])
	{
		node->next = ft_newnode(matrix[i], i + 1);
		node = node->next;
        i++;
	}
    ft_final_stamper(first);
	return (first);
}


/*
int     fd[2];

pipe(fd);
fork();
fd[0] -> reading end;
fd[1] -> writing end;



fd = open(file2);

old_stdout = dup(1);
if(fd == -1)
    error;
else
    dup2(fd, 1);
    fd == 3 -> file2;
    fd2 == 4 -> file2;
    close(fd);
    dup2(old_stdout, 1);
*/