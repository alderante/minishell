/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:21:38 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/18 11:12:27 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

t_e_type	ft_node_builtin_typer(char	*token)
{
	t_e_type	type;

	if (ft_strcmp(token, "echo") == 0)
		type = BUILTIN;
	else if (ft_strcmp(token, "cd") == 0)
		type = BUILTIN;
	else if (ft_strcmp(token, "pwd") == 0)
		type = BUILTIN;
	else if (ft_strcmp(token, "export") == 0)
		type = BUILTIN;
	else if (ft_strcmp(token, "unset") == 0)
		type = BUILTIN;
	else if (ft_strcmp(token, "env") == 0)
		type = BUILTIN;
	else
		return (1);
	return (type);
}

// else if (ft_strcmp(token, "|") == 0)
// 	type = LIMITOR;

t_e_type	ft_node_redirect_typer(char *token)
{
	t_e_type	type;

	if (ft_strcmp(token, (char [3]){-2, -2, '\0'}) == 0)
		type = HERE_DOC;
	else if (ft_strcmp(token, (char [2]){-2, '\0'}) == 0)
		type = FILE_IN;
	else if (ft_strcmp(token, (char [3]){-1, -1, '\0'}) == 0)
		type = FILE_OUT_OVER;
	else if (ft_strcmp(token, (char [2]){-1, '\0'}) == 0)
		type = FILE_OUT;
	else
		return (1);
	return (type);
}
