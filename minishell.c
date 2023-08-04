/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/04 09:38:15 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <string.h>

extern int	g_exit_status;

int	ft_check_quote (char c, int check)
{
	if (c == '\"' && check != 1)
		check = 2 - check;
	else if (c == '\'' && check != 2)
		check = 1 - check;
	return (check);
}

int	easy_split_rows_counter(char *input)
{
	int		i;
	int		check;
	int		rows;

	i = 0;
	rows = 0;
	check = 0;
	while (input[i] != '\0')
	{
		if (input[i] > 32)
		{
			while (input[i] > 32)
			{
				check = ft_check_quote (input[i], check);
				if (check == 1 || check == 2)
				{	
					while(check == 1 || check == 2)
					{
						rows++;
						check = ft_check_quote (input[i], check);
						if(check == 0)
							i++;
					}
				}
				else if (input[i] == 124)
				{
					if(input[i - 1] == 32)
						rows--;
					rows++;
					i++;
					break;
				}
				else
					i++;
			}
			rows++;
		}
		else
			i++;
	}
	rows++;
	//printf("le rows per l'easy split sono all'incirca cio[ piu o meno eh nissenso %d\n", rows);
	return (rows);
}

char	**easy_split(char *str) //AHAHAHAHAHAHAHAHAHAHAHAHAH
{
	int		i;
	int		y;
	int		x;
	int		check;
	char	**tab;

	i = 0;
	y = 0;
	tab = ft_calloc((easy_split_rows_counter(str)), sizeof(char *));
	//printf("this is counter %d\n", easy_split_rows_counter(str));
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] > 32)
		{
			x = 0;
			tab[y] = ft_calloc((strlen(str) + 1), sizeof(char));
			while (str[i] != '\0' && str[i] > 32)
			{
				check = ft_check_quote (str[i], check);
				if (check == 1 || check == 2)
				{	
					while(str[i] != '\0' && (check == 1 || check == 2))
					{
						tab[y][x] = str[i];
						i++;
						x++;
						check = ft_check_quote (str[i], check);
						if(check == 0)
						{
							tab[y][x] = str[i];
							i++;
							x++;
						}
					}
				}
				else if (str[i] == 124)
				{
					if(tab[y][0] == 0)
						y--;
					y++;
					tab[y] = ft_calloc(2, 1);
					tab[y][0] = '|';
					x = 0;
					i++;
					break;
				}
				else
				{
					tab[y][x] = str[i];
					i++;
					x++;
				}
			}
			y++;
		}
		else
			i++;
	}
	tab[y] = NULL;
	return (tab);
}

int	pipe_counter(char **matrix)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '|')
				counter++;
			j++;
		}
		i++;
	}
	//printf("Counter: %d\n", counter);
	return (counter);
}

//  This fills new matrix_string in command line with the pipes as separators
t_command_line    *ft_new_matrix(char **matrix)
{
	int				i;
	int				pipe_count;
	char			*temp;
	t_command_line	*first_line;
	t_command_line	*cmd_line;

	//questo va allocato in base al numero di pipe + 2 (3 pipe = 4 + la quinta NULL)
	pipe_count = pipe_counter(matrix) + 2;
	cmd_line = malloc(sizeof(char *) * pipe_count);
	//cmd_line = ft_calloc(1, 1);
	first_line = cmd_line;
	i = 0;
	while (matrix[i])
	{
		cmd_line->new_matrix_string = malloc(sizeof(char *) * ft_strlen(matrix[i]));
		temp = ft_calloc(1, 1);
		while (matrix[i] && matrix[i][0] != '|')
		{
			cmd_line->new_matrix_string = ft_strjoin(temp, matrix[i]);
			if (matrix[i + 1] != NULL && matrix[i + 1][0] != '|')
				cmd_line->new_matrix_string = ft_strjoin(cmd_line->new_matrix_string, " ");
			temp = cmd_line->new_matrix_string;
			i++;
		}
		if (matrix[i] && matrix[i][0] == '|')
		{
			i++;
			cmd_line->next = ft_calloc(sizeof(t_command_line *), 1);
			cmd_line = cmd_line->next;
		}
	}
	cmd_line->next = NULL;
	cmd_line = first_line;
	 while (cmd_line)
	{
		printf("cmd_line->new_matrix_string: %s\n", cmd_line->new_matrix_string);
		cmd_line = cmd_line->next;
	}
	//free(temp);
	return (first_line);
}

void	ft_lexer(char *input, t_env01 *env_list)
{
	int				i;
	char			*input_clone;
	char			**matrix;
	t_command_line	*first;
	

	input_clone = strdup(input);
	matrix = easy_split(input_clone);

	i = 0;
	while (matrix[i])
	{
		printf("Easy split line %i: %s\n", i, matrix[i]);
		i++;
	}
	first = malloc(sizeof(t_command_line));
	first = ft_new_matrix(matrix);
	ft_initialize(first, env_list);
	execution(&first);
	//ft_node_deleter(first);
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	//free(input_clone);
	//free(first);
}

int	main(int ac, char **av, char **envp)
{
	//t_env01	*env;
	char	*input;
	t_env01		*env_list;

	(void)(ac);
	(void)(av);
	g_exit_status = 0;
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	//env = ft_env_noder(envp);
	env_list = ft_env_noder(envp);
	//env_list = convert_env_to_list(envp);
	while (1)
	{
		input = readline("%>"); //ft_strjoin(getenv("PWD"), "%>")
		add_history(input);
		if (input == NULL || *input == '\0')
		{
			printf("\n");
			free(input);
			break;
		}
		else if(ft_strcmp(input, "env") == 0)
		{
			while(env_list)
			{
				printf("%s\n", env_list->str);
				env_list = env_list->next;
			}
		}
		else
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				printf("exit\n");
				exit(0);
			}
			ft_lexer(input, env_list);

			//free(input);
		}
	}
	return (0);
}
