/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/06 17:04:11 by cpopolan         ###   ########.fr       */
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

int pipe_counter(char **matrix)
{
    int i;
    int j;
    int counter;

    i = 0;
    counter = 0;
    while(matrix[i])
    {
        j = 0;
        while(matrix[i][j])
        {
            if(matrix[i][j] == '|')
                counter++;
            j++;
        }
        i++;
    }
    printf("Counter: %d\n", counter);
    return(counter);
}

//  This fills new matrix_string in command line with the pipes as separators
t_command_line    *ft_new_matrix(char **matrix)
{
    int     i;
    //int     pipe_count;
    char    *temp;
    t_command_line    *first_line;
    t_command_line    *cmd_line;

    //questo va allocato in base al numero di pipe + 2 (3 pipe = 4 + la quinta NULL)
    //pipe_count = pipe_counter(matrix) + 2;
    //cmd_line = malloc(sizeof(char *) * pipe_count);
    cmd_line = ft_calloc(1, 1);
    first_line = cmd_line;
    i = 0;
    while(matrix[i])
    {
        cmd_line->new_matrix_string = malloc(sizeof(char *) * 1000);
        temp = ft_calloc(1, 1);
        while (matrix[i] && matrix[i][0] != '|')
        {
            cmd_line->new_matrix_string = ft_strjoin(temp, matrix[i]);
            if(matrix[i + 1] != NULL && matrix[i + 1][0] != '|')
                cmd_line->new_matrix_string = ft_strjoin(cmd_line->new_matrix_string, " ");
            temp = cmd_line->new_matrix_string;
            i++;
            //printf("Passaggio %d: %s\n", i, cmd_line->new_matrix_string);

        }
        if (matrix[i] && matrix[i][0] == '|')
        {
            i++;
            cmd_line->next = calloc(sizeof(t_command_line *), 1);
            cmd_line = cmd_line->next;
        }
    }
	cmd_line->next = NULL;
    cmd_line = first_line;
    while(cmd_line)
    {
        printf("cmd_line->new_matrix_string: %s\n", cmd_line->new_matrix_string);
        cmd_line = cmd_line->next;
    }
    //free(temp);
    return(first_line);
}

void ft_lexer(char *input)
{
    char *input_clone;
    char **matrix;
    t_command_line *first;
    int i;
  
    //printf("Lexer ORIGINALE: %s\n", lexer);
    input_clone = strdup(input);
    //printf("Lexer CLONATO:   %s\n", lexer);
    matrix = easy_split(input_clone);

    //questo is to print the matrix
    i = 0;
    while (matrix[i])
    {
        printf("Easy split line %i: %s\n", i, matrix[i]);
        i++;
    }
    first = malloc(sizeof(t_command_line));
    first = ft_new_matrix(matrix);
    //questo is to initialize i nodi
    ft_initialize(first);
    //ft_node_deleter(first);

    //questo is to free the matrix
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
   // free(input_clone);
}

int main(int ac, char **av, char **envp)
{
	char *input;
    (void)(ac);
    (void)(av);
    
	// questa gestisce le variabili ambientali
	ft_env_noder(envp);
	
    while (1)
    {
        //this is to print the prompt
        input = readline(ft_strjoin(getenv("PWD"), "%>"));
        add_history(input);
        //printf("%s\n", getenv("PWD"));    
        if(input == NULL || *input == '\0')
        {
            printf("\n");
            free(input);
        }
        else
        {
            if (strcmp(input, "exit") == 0)
            {
                printf("exit\n");
                exit(0);
            }
            
            //printf("You entered: %s\n", input);
            ft_lexer(input);
            free(input);
        }
    }
    return (0);
}

//gcc minishell.c noder.c libft/libft.a -lreadline