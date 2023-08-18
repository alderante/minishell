/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   majia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:54:25 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/18 11:14:03 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_majia(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
	{
		if (ft_strcmp(matrix[y], ">>") == 0)
		{
			matrix[y][0] = -1;
			matrix[y][1] = -1;
		}
		else if (ft_strcmp(matrix[y], "<<") == 0)
		{
			matrix[y][0] = -2;
			matrix[y][1] = -2;
		}
		else if (ft_strcmp(matrix[y], ">") == 0)
			matrix[y][0] = -1;
		else if (ft_strcmp(matrix[y], "<") == 0)
			matrix[y][0] = -2;
		y++;
	}
}
