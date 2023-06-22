/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/06/22 16:11:54 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **easy_split(char *str)
{
    int i;
    int y;
    int x;
    char **tab;

    i = 0;
    y = 0;
    tab = malloc(sizeof(char *) * (strlen(str) + 1));
    while (str[i] != '\0')
    {
        if (str[i] > 32)
        {
            x = 0;
            tab[y] = malloc(sizeof(char) * (x + 1));
            while (str[i] > 32)
            {
                if(str[i] == 34 || str[i] == 39)
                {
                    i++;
                    while(str[i] != 34 && str[i] != 39)
                    {
                        tab[y][x] = str[i];
                        i++;
                        x++;
                    }
                    i++;
                }
                else if(str[i] == 124)
                {
                    //i++;
                    while(str[i] > 32)
                    {
                        tab[y][x] = str[i];
                        i++;
                        x++;
                    }
                    i++;
                }
                else
                {
                    tab[y][x] = str[i];
                    i++;
                    x++;
                }
            }
            tab[y][x] = '\0';
            y++;
        }
        else
            i++;
    }
    tab[y] = 0;
    return (tab);
}

void ft_lexer(char *lexer, t_lexer *first)
{
    char *input_clone;
    char **matrix;
    int i;
    t_lexer *node;

    //printf("Lexer ORIGINALE: %s\n", lexer);
    input_clone = strdup(lexer);
    //printf("Lexer CLONATO:   %s\n", lexer);
    matrix = easy_split(input_clone);

    //questo is to print the matrix
    i = 0;
    while (matrix[i])
    {
        printf("Easy split line %i: %s\n", i, matrix[i]);
        i++;
    }
    //questo is to initialize i nodi
    ft_initialize(matrix);
    //questo is to delete the nodes
    ft_node_deleter(first);

    //questo is to free the matrix
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
    free(input_clone);
}

int main(void)
{
    char *input;

    while (1)
    {
        //this is to print the prompt
        printf("%s$ ", get_current_dir_name());
        input = readline("");
        if(input == NULL || *input == '\0')
            free(input);
        else
        {
            if (strcmp(input, "exit") == 0)
            {
                printf("exit\n");
                exit(0);
            }
            add_history(input);
            printf("You entered: %s\n", input);
            ft_lexer(input, NULL);
            free(input);
        }
    }
    return (0);
}

//gcc minishell.c noder.c -lreadline