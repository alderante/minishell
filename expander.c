/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:01:31 by cpopolan          #+#    #+#             */
/*   Updated: 2023/08/14 16:54:50 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

char *ft_value_extractor(t_env01 *env_list)
{
	char	*value;
	int		equal;

	equal = ft_env_list_equal_position(env_list);
	value = ft_substr(env_list->str, equal, ft_strlen(env_list->str));
	return (value);
}

char	*expander(char *str, t_env01 *env_list)
{
	char	*value;
	int		check;
	int		i;
	int		n;
	int		new_len;
	int		initial;
	char	*searchname;
	char	*new_str;

	i = 0;
	new_len = 0;
	check = 0;
	while (str[i])
	{
		check = ft_check_quote(str[i], check);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '_') && check != 1 )
		{
			i++;
			n = 0;
			initial = i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '_')
			{
				n++;
				i++;
			}
			printf("n is %d\n", n);
			searchname = ft_substr(str, initial, n);
			printf("questo is searchname: %s\n", searchname);
			if (ft_env_search(env_list, searchname) != NULL)
			{
				value = ft_value_extractor(ft_env_search(env_list, searchname));
				printf("Value is %s\n", value);
				new_len = new_len + ft_strlen(value);
				free(value);
			}
			else
				printf("env non trovato\n");
			free(searchname);
		}
		else
		{
			i++;
			new_len++;
		}
	}
	printf("new_len is %d\n", new_len);

	new_str = malloc(sizeof(char) * new_len + 1);
	new_str[new_len] = '\0';
	new_len = 0;
	check = 0;
	i = 0;
	while (str[i])
	{
		check = ft_check_quote(str[i], check);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '_') && check != 1)
		{
			n = 0;
			i++;
			initial = i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '_')
			{
				n++;
				i++;
			}
			printf("n is %d\n", n);
			searchname = ft_substr(str, initial, n);
			printf("questo is searchname: %s\n", searchname);
			if (ft_env_search(env_list, searchname) != NULL)
			{
				value = ft_value_extractor(ft_env_search(env_list, searchname));
				printf("Value is %s\n", value);
				ft_strlcat(&new_str[new_len], value, ft_strlen(value) + 1);
				new_len += ft_strlen(value);
				printf("ESPANSIONE la stringa che ora is %s\n", new_str);
				free(value);
			}
			else
				printf("env non trovato\n");
			free(searchname);
		}
		else
		{
			new_str[new_len] = str[i];
			i++;
			new_len++;
		}
	}
	printf("ALLA FINE is %s\n", new_str);
	return (new_str);
}