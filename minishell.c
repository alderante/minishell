/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/17 19:52:05 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <string.h>

extern int	g_exit_status;

int	ft_check_pipe_before(char *input)
{
	int	i;

	i = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (input[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	ft_check_pipe_after(char *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (input[i])
	{
		check = ft_check_quote (input[i], check);
		if (check == 1 || check == 2)
		{
			while (check == 1 || check == 2)
			{
				check = ft_check_quote(input[i], check);
				if (check == 0)
					i++;
			}
		}
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (input[i] == '|')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		else
			i++;
	}
	return(0);
}

int	ft_check_maj(char *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (input[i])
	{
		check = ft_check_quote (input[i], check);
		if (check == 1 || check == 2)
		{
			while (check == 1 || check == 2)
			{
				check = ft_check_quote(input[i], check);
				if (check == 0)
					i++;
			}
		}
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (input[i] == '>' && input[i + 1] == '>')
		{
			i++;
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `>'\n");
				return (1);
			}
		}
		else if (input[i] == '>')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `>'\n");
				return (1);
			}
		}
		else
			i++;
	}
	return(0);
}

int	ft_check_min(char *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (input[i])
	{
		check = ft_check_quote (input[i], check);
		if (check == 1 || check == 2)
		{
			while (check == 1 || check == 2)
			{
				check = ft_check_quote(input[i], check);
				if (check == 0)
					i++;
			}
		}
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i++;
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `<'\n");
				return (1);
			}
		}
		else if (input[i] == '<')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `<'\n");
				return (1);
			}
		}
		else
			i++;
	}
	return(0);
}

int	ft_symbol_checker(char *input)
{
	if (ft_check_pipe_before(input) == 1)
		return (1);
	else if (ft_check_pipe_after(input) == 1)
		return (1);
	else if (ft_check_maj(input) == 1)
		return (1);
	else if (ft_check_min(input) == 1)
		return (1);
	return (0);
}

int	ft_only_spaces_checker(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	while (len > 0)
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
		len--;
	}
	return (0);
}

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
		free(matrix[i]);
		i++;
	}
	free(matrix);
	ft_initialize(first, *env_list);
	ft_final_stamper(first);
	execution(&first);
	*env_list = first->env_list;
	free_all(&first);
}

void	ft_input(char *input, t_env01 *env_list)
{
	while (1)
	{
		free(input);
		input = readline("%>");
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		else if (*input && ft_only_spaces_checker(input))
		{
			add_history(input);
			if (ft_symbol_checker(input) == 0)
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
