/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/16 13:59:22 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <string.h>

extern int	g_exit_status;

/* int ft_only_spaces_checker (char *input)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	while(len > 0)
	{
		if(input[i] != ' ')
			return(1);
		i++;
		len--;
	}
	return(0);
} */

t_command_line	*ft_new_matrix_continue(char **matrix, t_command_line *cmd_line,
	t_command_line *first_line)
{
	int				i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i])
	{
		while (matrix[i] && matrix[i][0] != '|')
		{
			cmd_line->new_matrix_string
				= ft_strjoin01(cmd_line->new_matrix_string, matrix[i]);

			if (matrix[i + 1] != NULL && matrix[i + 1][0] != '|')
				cmd_line->new_matrix_string
					= ft_strjoin01(cmd_line->new_matrix_string, " ");
			i++;
		}
		printf("esco dal ciclo\n");
		if (matrix[i] && matrix[i][0] == '|')
		{
			i++;
			cmd_line->next = ft_calloc(sizeof(t_command_line), 1);
			cmd_line = cmd_line->next;
		}
	}
	cmd_line->next = NULL;
	cmd_line = first_line;
	return (first_line);
}

//  This fills new matrix_string in command line with the pipes as separators
t_command_line	*ft_new_matrix(char **matrix)
{
	t_command_line	*first_line;
	t_command_line	*cmd_line;

	cmd_line = ft_calloc(sizeof(t_command_line), 1);
	first_line = cmd_line;
	cmd_line->new_matrix_string = NULL;
	return (ft_new_matrix_continue(matrix, cmd_line, first_line));
}

void	ft_lexer(char *input, t_env01 **env_list)
{
	int				i;
	char			**matrix;
	t_command_line	*first;

	matrix = easy_split(input);
	first = ft_new_matrix(matrix);
	i = 0;
	while (matrix[i])
	{
		printf("This is %d row of Matrix: %s \n", i, matrix[i]);
		i++;
	}
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	ft_initialize(first, *env_list);
	ft_final_stamper(first);
	execution(&first);
	*env_list = first->env_list;
	free_all(&first);
	// free_end(&first, NULL);
	//free(input_clone);
	//free(first);
}

void	ft_input(char *input, t_env01 *env_list)
{
	while (1)
	{
		free(input);
		input = readline("%>");
		// if (ft_only_spaces_checker(input) == 0)
		// 	add_history(input);
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		else if (*input)
		{
			add_history(input);
			ft_lexer(input, &env_list);
		}
	}
	ft_env_deleter(env_list);
	free(input);
}


int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env01	*env_list;

	(void)(ac);
	(void)(av);
	g_exit_status = 0;
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	env_list = ft_env_noder(envp);
	input = NULL;
	ft_input(input, env_list);
	return (0);
}
