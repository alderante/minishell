/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:35:23 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 15:36:52 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

t_env01	*ft_env_search(t_env01 *env_list, char *searchname)
{
	char	*temp;

	temp = ft_strjoin(searchname, "=");
	while (env_list != NULL)
	{
		if (!ft_strncmp(temp, env_list->str, ft_strlen(temp)))
			break ;
		env_list = env_list->next;
	}
	free(temp);
	if (env_list)
		return (env_list);
	return (NULL);
}

int	ft_env_list_equal_position(t_env01 *env_list)
{
	int	equal;

	equal = 0;
	while (env_list->str[equal] != '=')
	{
		equal++;
	}
	equal++;
	return (equal);
}

char	*ft_value_extractor(t_env01 *env_list)
{
	char	*value;
	int		equal;

	equal = ft_env_list_equal_position(env_list);
	value = ft_substr(env_list->str, equal, ft_strlen(env_list->str));
	return (value);
}

int	ft_dollar_checker(char *str, t_expander *exp)
{
	if (str[(*exp).i] == '$' && str[(*exp).i + 1] != '?'
		&& (ft_isalnum(str[(*exp).i + 1]) == 1
			|| str[(*exp).i + 1] == '_') && (*exp).check != 1)
		return (1);
	return (0);
}

void	ft_exit_expander(t_expander **exp)
{
	(*exp)->i += 2;
	(*exp)->value = ft_itoa_original(g_exit_status);
	(*exp)->new_str[(*exp)->new_len] = '\0';
	ft_strlcat(&(*exp)->new_str[(*exp)->new_len], (*exp)->value,
		ft_strlen((*exp)->value) + 1);
	(*exp)->new_len += ft_strlen((*exp)->value);
	free((*exp)->value);
}
