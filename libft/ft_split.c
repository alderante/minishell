/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:14:16 by rkhinchi          #+#    #+#             */
/*   Updated: 2022/10/26 12:08:52 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	check_split(const char *s, char c);

void	fill(char const *s, char c, char **ptrstr)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	x = 0;
	while (s[i] != '\0' && k < check_split(s, c))
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			ptrstr[k][x] = s[i];
			i++;
			x++;
		}
		if (x != 0)
			ptrstr[k][x] = '\0';
		k++;
		x = 0;
	}
}

void	mem(char const *s, char c, char **ptrstr)
{
	int	i;
	int	savei;
	int	k;

	savei = 0;
	k = 0;
	i = 0;
	while (s[i] != '\0' && k < check_split(s, c))
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			savei = savei + 1;
		}
		ptrstr[k] = (char *)malloc(sizeof (char) * (savei + 1));
		savei = 0;
		k++;
	}
	ptrstr[k] = 0;
}

int	check_split(char const *s, char c)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 1)
		{
			j++;
			flag = 0;
		}
		else if (s[i] == c)
			flag = 1;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**ptrstr;
	int		j;

	j = check_split((char *)s, c);
	ptrstr = (char **)malloc(sizeof(char *) * (j + 1));
	if (ptrstr == 0)
		return (0);
	mem(s, c, ptrstr);
	fill(s, c, ptrstr);
	return (ptrstr);
}
