/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_symbol_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 17:23:59 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;
/* 
int	ft_symbol_check_if(char *input, int i)
{
	if (input[i] == '|' || input[i] == '>'
		|| input[i] == '<' || input[i] == '\0')
		return (1);
	return (0);
}

int	ft_check_pipe_before(char *input)
{
	int	i;

	i = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (input[i] == '|')
	{
		g_exit_status = 2;
		return (1 + ft_putstr_fd
			("minishell: syntax error near unexpected token `|'\n", 2));
	}
	return (0);
}

// int ft_symbol_checker_stamper()
// {
// 	int	j;

// 	j = 0;
// 	if (ft_symbol_check_if == 1)
// 	{
// 		g_exit_status = 2;
// 		j = (1 + ft_putstr_fd
// 			("minishell: syntax error near unexpected token `|'\n", 2));
// 	}
// 	return (j);
// }

int	*ft_check_quote002(char c, int **check)
{
	if (c == '\"' && (*check) != 1)
		check = 2 - **check;
	else if (c == '\'' && (*check) != 2)
		check = 1 - **check;
	return ((*check));
}

void	ft_check_quote01(char *input, int *i, int *check)
{
	if (*check == 1 || *check == 2)
	{
		while (*check == 1 || *check == 2)
		{
			check = ft_check_quote002(input[*i], &check);
			if (*check == 0)
				*i += 1;
		}
	}
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
		ft_check_quote01(input, &i, &check);
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (input[i] == '|')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (ft_symbol_check_if(input, i) == 1)
				return (ft_check_pipe_error());
		}
		else
			i++;
	}
	return (0);
}

int	ft_check_maj_continue(char *input, int *i)
{
	int	j;

	j = 0;
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
			*i += 1;
		if (ft_symbol_check_if(input, i) == 1)
			j = ft_check_maj_error();
	}
	return (j);
}

int	ft_check_min_continue(char *input, int *i)
{
	int	j;

	j = 0;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
			*i += 1;
		if (ft_symbol_check_if(input, i) == 1)
			j = ft_check_min_error();
	}
	return (j);
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
		ft_check_quote01(input, &i, &check);
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (ft_check_maj_continue(input, i) == 1)
			return (1);
		else if (input[i] == '>')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (ft_symbol_check_if(input, i) == 1)
				return (ft_check_maj_error());
		}
		else
			i++;
	}
	return (0);
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
		ft_check_quote01(input, &i, &check);
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		if (ft_check_min_continue == 1)
			return (1);
		else if (input[i] == '<')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (ft_symbol_check_if(input, i) == 1)
				return (ft_check_min_error());
		}
		else
			i++;
	}
	return (0);
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
 */