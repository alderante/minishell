/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:25:04 by rkhinchi          #+#    #+#             */
/*   Updated: 2022/10/20 12:48:15 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	valor(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

int	l(int n)
{
	int	ln;

	ln = 0;
	if (n <= 0)
	{
		++ln;
	}
	while (n != 0)
	{
		++ln;
		n = n / 10;
	}
	return (ln);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		ln;

	ln = l(n);
	r = malloc(ln + 1);
	r[ln] = '\0';
	if (n < 0)
	{
		r[0] = '-';
	}
	else if (n == 0)
	{
		r[0] = '0';
	}
	while (n != 0)
	{
		--ln;
		r[ln] = valor(n % 10) + '0';
		n = n / 10;
	}
	return (r);
}
