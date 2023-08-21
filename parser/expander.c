/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:01:31 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/21 17:36:56 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

extern int	g_exit_status;

void	ft_expander_new_string(t_expander **exp, char *str, t_env01 *env_list)
{
	(*exp)->n = 0;
	(*exp)->i++;
	(*exp)->initial = (*exp)->i;
	while (ft_isalnum(str[(*exp)->i]) == 1 || str[(*exp)->i] == '_')
	{
		(*exp)->n++;
		(*exp)->i++;
	}
	(*exp)->searchname = ft_substr(str, (*exp)->initial, (*exp)->n);
	if (ft_env_search(env_list, (*exp)->searchname) != NULL)
	{
		(*exp)->value = ft_value_extractor
			(ft_env_search(env_list, (*exp)->searchname));
		(*exp)->new_str[(*exp)->new_len] = '\0';
		ft_strlcat(&(*exp)->new_str[(*exp)->new_len], (*exp)->value,
			ft_strlen((*exp)->value) + 1);
		(*exp)->new_len += ft_strlen((*exp)->value);
		free((*exp)->value);
	}
	free((*exp)->searchname);
}

char	*ft_expander01(t_expander *exp, char *str, t_env01 *env_list)
{
	(*exp).new_str = malloc(sizeof(char) * (*exp).new_len + 1);
	(*exp).new_str[(*exp).new_len] = '\0';
	(*exp).new_len = 0;
	(*exp).check = 0;
	(*exp).i = 0;
	while (str[(*exp).i])
	{
		(*exp).check = ft_check_quote(str[(*exp).i], (*exp).check);
		if (str[(*exp).i] == '$' && str[(*exp).i + 1] == '?'
			&& (*exp).check != 1)
			ft_exit_expander(&exp);
		else if (ft_dollar_checker(str, exp) == 1)
			ft_expander_new_string(&exp, str, env_list);
		else
		{
			(*exp).new_str[(*exp).new_len] = str[(*exp).i];
			(*exp).i++;
			(*exp).new_len++;
		}
	}
	return ((*exp).new_str);
}

void	ft_expander02(char *str, t_expander *exp, t_env01 *env_list)
{
	(*exp).i++;
	(*exp).n = 0;
	(*exp).initial = (*exp).i;
	while (ft_isalnum(str[(*exp).i]) == 1 || str[(*exp).i] == '_')
	{
		(*exp).n++;
		(*exp).i++;
	}
	(*exp).searchname = ft_substr(str, (*exp).initial, (*exp).n);
	if (ft_env_search(env_list, (*exp).searchname) != NULL)
	{
		(*exp).value = ft_value_extractor
			(ft_env_search(env_list, (*exp).searchname));
		(*exp).new_len = (*exp).new_len + ft_strlen((*exp).value);
		free((*exp).value);
	}
	free((*exp).searchname);
}

char	*expander(char *str, t_env01 *env_list)
{
	t_expander	exp;

	exp.i = 0;
	exp.new_len = 0;
	exp.check = 0;
	while (str[exp.i])
	{
		exp.check = ft_check_quote(str[exp.i], exp.check);
		if (str[exp.i] == '$' && str[exp.i + 1] == '?'
			&& exp.check != 1)
		{
			exp.i += 2;
			exp.value = ft_itoa_original(g_exit_status);
			exp.new_len = exp.new_len + ft_strlen(exp.value);
			free(exp.value);
		}
		else if (ft_dollar_checker(str, &exp) == 1)
			ft_expander02(str, &exp, env_list);
		else
		{
			exp.i++;
			exp.new_len++;
		}
	}
	return (ft_expander01(&exp, str, env_list));
}
