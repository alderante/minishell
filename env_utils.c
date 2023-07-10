/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <rkhinchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:14:47 by rkhinchi          #+#    #+#             */
/*   Updated: 2023/07/10 14:17:07 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* void	func_2_free_all_env(void)
{
	free_delete_add(NULL, FREE);
} */

void	free_all_env(t_env01 **env)
{
	t_env01	*cpy;
	t_env01	*tmp;

	cpy = *env;
	tmp = cpy;
	while (cpy)
	{
		tmp = cpy;
		cpy = cpy->next;
		free(tmp->str);
		free(tmp);
	}
}

void	particular_env_free(t_env01 *env)
{
	free(env->str);
	free(env);
}
