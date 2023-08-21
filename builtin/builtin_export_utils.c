/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:18:48 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 15:36:42 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_free_built_in_export01(char *name, char *value)
{
	free(name);
	free(value);
}

int	ft_export_checker(char *tab, int equal)
{
	int	i;

	if (equal < 1)
		return (1);
	if (ft_isalpha(tab[0]) == 0 && tab[0] != '_')
		return (1);
	i = 1;
	while (tab[i] != '=')
	{
		if (ft_isalnum(tab[i]) == 0 && tab[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
