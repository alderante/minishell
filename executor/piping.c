/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:52:44 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/08/18 11:21:01 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

//int	g_exit_status;

int	ft_using_pipe(int **nfd, int i, t_command_line *updated)
{
	nfd[i] = malloc(sizeof(int) * 2);
	if (nfd == NULL)
		return (50);
	if ((pipe(nfd[i])) == -1)
		return (40);
	if (i == 0)
		updated->fd_in = 0;
	else
		updated->fd_in = nfd[i - 1][0];
	if (updated->next == NULL)
	{
		close(nfd[i][0]);
		close(nfd[i][1]);
		updated->fd_out = 1;
	}
	else
		updated->fd_out = nfd[i][1];
	return (0);
}

// total nfd will be needed, depending on the process
// number of fd, nfd[0][0], *nfd[0][1]
int	ft_piping(t_command_line **cmd)
{
	int					i;
	int					rtrn;
	t_command_line		*updated;
	int					**nfd;

	i = 0;
	updated = *cmd;
	nfd = malloc(sizeof(int *) * (ft_command_len(updated) + 1));
	if (nfd == NULL)
		return (50);
	nfd[ft_command_len(updated)] = NULL;
	while (updated)
	{
		rtrn = ft_using_pipe(nfd, i, updated);
		if (rtrn != 0)
		{
			ft_freeing_matrix_nfd(nfd);
			return (rtrn);
		}
		updated = updated->next;
		i++;
	}
	ft_freeing_matrix_nfd(nfd);
	return (0);
}
