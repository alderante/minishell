/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv_uns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:44:49 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/19 17:37:45 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	support(unsigned int n)
{
	if (n > 9)
		support(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	ft_print_conv_uns(unsigned int n)
{
	long unsigned int	t;
	unsigned int		l;

	t = n;
	l = 1;
	support(n);
	while (t >= 10)
	{
		t = t / 10;
		l++;
	}
	return (l);
}
