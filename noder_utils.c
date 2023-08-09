/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:21:38 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/09 11:35:12 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

t_e_type	ft_node_redirect_typer(char *token)
{
	t_e_type	type;

	if (ft_strcmp(token, "<") == 0)
		type = OPEN_FILE;
	else if (ft_strcmp(token, "<<") == 0)
		type = HERE_DOC;
	else if (ft_strcmp(token, "|") == 0)
		type = LIMITOR;
	else if (ft_strcmp(token, ">") == 0)
		type = CREAT_FILE;
	else if (ft_strcmp(token, ">>") == 0)
		type = WRITE_FILE;
	else
		return (1);
	return (type);
}