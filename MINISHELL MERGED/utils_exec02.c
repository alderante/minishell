/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:51:23 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/07 18:06:14 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	all_free_n_exit(t_command_line **cmd,
	pid_t *pid, char **str)
{
	free_all(cmd);
	free_delete_add(NULL, FREE);
	free(pid);
	free(str);
	exit(1);
}
