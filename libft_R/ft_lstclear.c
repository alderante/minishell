/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhinchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:15:12 by rkhinchi          #+#    #+#             */
/*   Updated: 2022/10/22 20:15:15 by rkhinchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*p;

	if (!lst || !del)
		return ;
	t = NULL;
	p = *lst;
	while (p != NULL)
	{
		t = p -> next;
		del(p -> content);
		free(p);
		p = t;
	}
	*lst = NULL;
}
