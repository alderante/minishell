/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 10:28:50 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

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

int	ft_check_pipe_after(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = ft_symbol_quote_checker(input, i);
		i = ft_saltaspazi(input, i);
		if (input[i] == '|')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (input[i] == '|' || input[i] == '>'
				|| input[i] == '<' || input[i] == '\0')
			{
				g_exit_status = 2;
				return (1 + ft_putstr_fd
					("minishell: syntax error near unexpected token `|'\n", 2));
			}
		}
		else if (input[i])
			i++;
	}
	return (0);
}

int	ft_check_maj(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = ft_symbol_quote_checker(input, i);
		i = ft_saltaspazi(input, i);
		if (input[i] == '>' && input[i + 1] == '>')
		{
			if (ft_symbol_double_check(input, &i))
				return (1);
		}
		else if (input[i] == '>')
		{
			i++;
			i = ft_saltaspazi(input, i);
			if (input[i] == '|' || input[i] == '>'
				|| input[i] == '<' || input[i] == '\0')
				return (ft_check_maj_error());
		}
		else if (input[i])
			i++;
	}
	return (0);
}

int	ft_check_min(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = ft_symbol_quote_checker(input, i);
		i = ft_saltaspazi(input, i);
		if (input[i] == '<' && input[i + 1] == '<')
		{
			if (ft_symbol_double_check(input, &i))
				return (1);
		}
		else if (input[i] == '<')
		{
			i++;
			i = ft_saltaspazi(input, i);
			if (input[i] == '|' || input[i] == '>'
				|| input[i] == '<' || input[i] == '\0')
				return (ft_check_min_error());
		}
		else if (input[i])
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
