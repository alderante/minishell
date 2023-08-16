/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_split_rows_counter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:29 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/16 12:31:06 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_check_quote(char c, int check)
{
	if (c == '\"' && check != 1)
		check = 2 - check;
	else if (c == '\'' && check != 2)
		check = 1 - check;
	return (check);
}

void	ft_easy_split_rows_counter_continue(char *input,
		int *i, int *rows, int check)
{
	while (input[*i] > 32)
	{
		check = ft_check_quote (input[*i], check);
		if (check == 1 || check == 2)
		{
			while (check == 1 || check == 2)
			{
				*rows += 1;
				check = ft_check_quote(input[*i], check);
				if (check == 0)
					*i += 1;
			}
		}
		else if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		{
			if (input[*i - 1] == 32)
				*rows -= 1;
			*rows += 1;
			*i += 1;
			break ;
		}
		else
			*i += 1;
	}
}

int	ft_easy_split_rows_counter(char *input)
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
			ft_easy_split_rows_counter_continue(input, &i, &rows, check);
			rows++;
		}
		else
			i++;
	}
	rows++;
	return (rows);
}
