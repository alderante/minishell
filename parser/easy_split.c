/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:29 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/17 09:14:26 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
