/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/06/22 15:18:27 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_node_deleter(t_lexer *first)
{
    t_lexer *node;
     
    node = first;
    while(first)
    {
        free(first->arg);
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
        printf("Pos: %d\n", node->pos);
        printf("Token: %s\n", node->token);
        printf("Arg: %s\n", node->arg);
        node = node->next;
        i++;
    }
}

t_lexer	*ft_newnode(char *row, int pos)
{
	t_lexer		*node;

    node = malloc(sizeof(t_lexer) * 1);
    if (strcmp(row, "echo") == 0)
    {
        printf("ECHO\n");
        node->token = "ECHO";
    }
    else if (strcmp(row, "|") == 0)
    {   
        printf("|\n");
        node->token = row;
    }
    else if (strcmp(row, "<") == 0)
    {   
        printf("<\n");
        node->token = row;
    }
    else if (strcmp(row, ">") == 0)
    {   
        printf(">\n");
        node->token = row;
    }
    else if (strcmp(row, ">>") == 0)
    {   
        printf(">>\n");
        node->token = row;
    }
    else if (strcmp(row, "<<") == 0)
    {   
        printf("<<\n");
        node->token = row;
    }
    else if (strcmp(row, "cd") == 0)
    {   
        printf("CD\n");
        node->token = row;
    }
    else if (strcmp(row, "pwd") == 0)
    {   
        printf("PWD\n");
        node->token = row;
    }
    else if (strcmp(row, "export") == 0)
    {   
        printf("EXPORT\n");
        node->token = row;
    }
    else if (strcmp(row, "unset") == 0)
    {   
        printf("UNSET\n");
        node->token = row;
    }
    else if (strcmp(row, "env") == 0)
    {   
        printf("ENV\n");
        node->token = row;
    }
    else if (strcmp(row, "exit") == 0)
    {   
        printf("EXIT\n");
        node->token = row;
    }
    else
    {
        printf("ERROR\n");
        node->token = row;
    }
    node->pos = pos;
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