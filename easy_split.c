/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:29 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/15 15:47:44 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

typedef struct s_split
{
	int		i;
	int		y;
	int		x;
	int		check;
	char	**tab;
}		t_split;

void	ft_easy_split_continue01(t_split **pippo, char *str)
{
	while (str[(*pippo)->i] != '\0'
		&& ((*pippo)->check == 1 || (*pippo)->check == 2))
	{
		(*pippo)->tab[(*pippo)->y][(*pippo)->x] = str[(*pippo)->i];
		(*pippo)->i++;
		(*pippo)->x++;
		(*pippo)->check = ft_check_quote(str[(*pippo)->i], (*pippo)->check);
		if ((*pippo)->check == 0)
		{
			(*pippo)->tab[(*pippo)->y][(*pippo)->x] = str[(*pippo)->i];
			(*pippo)->i++;
			(*pippo)->x++;
		}
	}
}

void	ft_easy_split_continue02(t_split **pippo)
{
	if ((*pippo)->tab[(*pippo)->y][0] == 0)
		(*pippo)->y--;
	(*pippo)->y++;
	free((*pippo)->tab[(*pippo)->y]);
	(*pippo)->tab[(*pippo)->y] = ft_calloc(2, 1);
	(*pippo)->tab[(*pippo)->y][0] = '|';
	(*pippo)->x = 0;
	(*pippo)->i++;
}

void	ft_easy_split_continue03(t_split *pippo, char *str)
{
	while (str[pippo->i] != '\0' && str[pippo->i] > 32)
	{
		pippo->check = ft_check_quote(str[pippo->i], pippo->check);
		if (pippo->check == 1 || pippo->check == 2)
			ft_easy_split_continue01(&pippo, str);
		else if (str[pippo->i] == '|')
		{
			ft_easy_split_continue02(&pippo);
			break ;
		}
		else
		{
			pippo->tab[pippo->y][pippo->x] = str[pippo->i];
			pippo->i++;
			pippo->x++;
		}
	}
}

char	**easy_split(char *str)
{
	t_split	pippo;

	pippo.i = 0;
	pippo.y = 0;
	pippo.check = 0;
	pippo.tab = ft_calloc((ft_easy_split_rows_counter(str) + 1),
			sizeof(char *));
	while (str[pippo.i] != '\0')
	{
		if (str[pippo.i] != '\0' && str[pippo.i] > 32)
		{
			pippo.x = 0;
			pippo.tab[pippo.y] = ft_calloc((strlen(str) + 1), sizeof(char));
			ft_easy_split_continue03(&pippo, str);
			pippo.y++;
		}
		else
			pippo.i++;
	}
	pippo.tab[pippo.y] = NULL;
	return (pippo.tab);
}
