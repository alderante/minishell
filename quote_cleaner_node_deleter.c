/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner_node_deleter.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/15 16:42:02 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

typedef struct s_quote_cleaner
{
	int		i;
	int		y;
	int		x;
	char	**tab;
}	t_quote_cleaner;

void	quote_cleaner_split_continue02(t_quote_cleaner **pluto, char *str)
{
	(*pluto)->i++;
	while (str[(*pluto)->i] != 34)
	{
		(*pluto)->tab[(*pluto)->y][(*pluto)->x] = str[(*pluto)->i];
		(*pluto)->i++;
		(*pluto)->x++;
	}
	(*pluto)->i++;
}

void	quote_cleaner_split_continue03(t_quote_cleaner **pluto,
		char *str)
{
	(*pluto)->i++;
	while (str[(*pluto)->i] != 39)
	{
		(*pluto)->tab[(*pluto)->y][(*pluto)->x] = str[(*pluto)->i];
		(*pluto)->i++;
		(*pluto)->x++;
	}
	(*pluto)->i++;
}

void	quote_cleaner_split_continue01(t_quote_cleaner *pluto,
		char *str)
{
	while (str[pluto->i] > 32)
	{
		if (str[pluto->i] == 34 && str[pluto->i + 1] != '\0')
			quote_cleaner_split_continue02(&pluto, str);
		else if (str[pluto->i] == 39 && str[pluto->i + 1] != '\0')
			quote_cleaner_split_continue03(&pluto, str);
		else
		{
			pluto->tab[pluto->y][pluto->x] = str[pluto->i];
			pluto->i++;
			pluto->x++;
		}
	}
}

char	**quote_cleaner_split(char *str, t_env01 *env_list)
{
	t_quote_cleaner	pluto;

	pluto.i = 0;
	pluto.y = 0;
	pluto.tab = ft_calloc((ft_easy_split_rows_counter(str) + 1),
			sizeof(char *));
	str = expander(str, env_list);
	while (str[pluto.i] != '\0')
	{
		if (str[pluto.i] > 32)
		{
			pluto.x = 0;
			pluto.tab[pluto.y] = ft_calloc((ft_strlen(str) + 1), sizeof(char));
			quote_cleaner_split_continue01(&pluto, str);
			pluto.tab[pluto.y][pluto.x] = '\0';
			pluto.y++;
		}
		else
			pluto.i++;
	}
	pluto.tab[pluto.y] = NULL;
	free(str);
	return (pluto.tab);
}

void	ft_node_deleter(t_token *first)
{
	if (first->next)
		ft_node_deleter(first->next);
	free(first->token);
	free(first);
}
