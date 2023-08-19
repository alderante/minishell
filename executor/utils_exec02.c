/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:51:23 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/19 17:35:00 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str)
{
	ft_free_all(cmd);
	free(pid);
	free(str);
	exit(1);
}
