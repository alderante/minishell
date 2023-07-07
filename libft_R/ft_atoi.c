/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:20:29 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/03/16 19:54:51 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	long long	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str [i] == 32 || (str [i] >= 9 && str [i] <= 13))
	{
		i++;
	}
	if (str [i] == '-' || str[i] == '+')
	{
		if (str [i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str [i] >= '0' && str [i] <= '9')
	{
		result = result * 10 + str [i] - '0';
		i++;
	}
	return (result * sign);
}
