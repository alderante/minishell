/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:11:25 by rkhinchi          #+#    #+#             */
/*   Updated: 2022/10/26 12:10:49 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	i++;
	while (--i)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
	}
	if (s[0] == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
