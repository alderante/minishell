/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:29 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/16 11:40:51 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

void	ft_easy_split_continue02_pipe(t_split **pippo)
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

void	ft_easy_split_continue02_maj(t_split **pippo, char *str)
{
	if ((*pippo)->tab[(*pippo)->y][0] == 0)
		(*pippo)->y--;
	(*pippo)->y++;
	if ((*pippo)->tab[(*pippo)->y])
		free((*pippo)->tab[(*pippo)->y]);
	if (str[(*pippo)->i + 1] == '>')
	{
		(*pippo)->tab[(*pippo)->y] = ft_calloc(3, 1);
		(*pippo)->tab[(*pippo)->y][0] = '>';
		(*pippo)->tab[(*pippo)->y][1] = '>';
		(*pippo)->i++;
	}
	else
	{
		(*pippo)->tab[(*pippo)->y] = ft_calloc(2, 1);
		(*pippo)->tab[(*pippo)->y][0] = '>';
	}
	(*pippo)->x = 0;
	(*pippo)->i++;
}

void	ft_easy_split_continue02_min(t_split **pippo, char *str)
{
	if ((*pippo)->tab[(*pippo)->y][0] == 0)
		(*pippo)->y--;
	(*pippo)->y++;
	if ((*pippo)->tab[(*pippo)->y])
		free((*pippo)->tab[(*pippo)->y]);
	if (str[(*pippo)->i + 1] == '<')
	{
		(*pippo)->tab[(*pippo)->y] = ft_calloc(3, 1);
		(*pippo)->tab[(*pippo)->y][0] = '<';
		(*pippo)->tab[(*pippo)->y][1] = '<';
		(*pippo)->i++;
	}
	else
	{
		(*pippo)->tab[(*pippo)->y] = ft_calloc(2, 1);
		(*pippo)->tab[(*pippo)->y][0] = '<';
	}
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
		else if (str[pippo->i] == '|' || str[pippo->i] == '>'
			|| str[pippo->i] == '<')
		{
			if (str[pippo->i] == '|')
				ft_easy_split_continue02_pipe(&pippo);
			else if (str[pippo->i] == '>')
				ft_easy_split_continue02_maj(&pippo, str);
			else if (str[pippo->i] == '<')
				ft_easy_split_continue02_min(&pippo, str);
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
