/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:14:08 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/04 16:16:23 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static int	ft_count_words(const char *s, char c)
{
	int		number;
	int		i;

	i = 0;
	number = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			number++;
		}
		s++;
	}
	return (number);
}

void	spliting(int words, char const *s, char c, char **tab)
{
	int	j;
	int	i;
	int	start;

	j = -1;
	i = 0;
	while (++j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_strsub(s, start, i - start);
		i++;
	}
	tab[j] = NULL;
}

char	**ft_strsplit(char const *s, char c)
{
	int		words;
	char	**tab;

	if (!s || !c)
		return (NULL);
	words = ft_count_words(s, c);
	tab = malloc((sizeof(char *) * (words + 1)));
	if (tab == NULL)
		return (NULL);
	spliting(words, s, c, tab);
	return (tab);
}