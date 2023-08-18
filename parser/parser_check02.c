/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/18 09:55:15 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

int	ft_symbol_quote_checker(char *input, int i)
{
	int	check;

	check = 0;
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
	return (i);
}

int	ft_symbol_double_check(char *input, int *i)
{
	*i += 2;
	while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
		*i += 1;
	if (input[*i] == '|' || input[*i] == '>'
		|| input[*i] == '<' || input[*i] == '\0')
		return (1 + ft_putstr_fd
			("bash: syntax error near unexpected token `>'\n", 2));
	return (0);
}

int	ft_saltaspazi(char *input, int i)
{
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	return (i);
}
