/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:47:35 by rkhinchi          #+#    #+#             */
/*   Updated: 2022/10/24 12:20:05 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s2 < s1)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
			i++;
		}
	}
	return (s1);
}
