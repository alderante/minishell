/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/18 09:06:32 by cpopolan         ###   ########.fr       */
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
