/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check03.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:06:44 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 17:38:38 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

int	ft_check_pipe_error(void)
{
	g_exit_status = 2;
	return (1 + ft_putstr_fd
		("minishell: syntax error near unexpected token `|'\n", 2));
}

int	ft_check_maj_error(void)
{
	g_exit_status = 2;
	return (1 + ft_putstr_fd
		("minishell: syntax error near unexpected token `>'\n", 2));
}

int	ft_check_min_error(void)
{
	g_exit_status = 2;
	return (1 + ft_putstr_fd
		("minishell: syntax error near unexpected token `<'\n", 2));
}
