/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpopolan <cpopolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:54:09 by cpopolan          #+#    #+#             */
/*   Updated: 2023/07/31 17:18:57 by cpopolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"



int expander(char*str, t_env *env)
{
	int	check;
	char *searchname;
	int	i;
	int	n;
	int res;

	i = 0;
	while(str)
	{
		check = ft_check_quote (str[i]);
		if (check == 2 && check != 1)
		{
			if(str[i] == '$')
			{
				n = 0;
				i++;
				while(str[i] > 32)
				{
					n++;
					i++;
				}
				searchname = calloc((sizeof(char) * n) + 1, 1);
				i -= n;
				searchname[n++] = '\0';
			}
			//qui metto funzione che compari name a tutti i name in env e se lo trova, mi restituisce il relativo value
			res = 0;
			while(env->next != NULL)
			{
				if(strcmp(searchname, env->name) == 0)
				{
					res = 1;
					break;
				}
				env = env->next;
			}
		}
		else
			i++;
	}
	return(res);
}

char	**quote_cleaner_split(char *str, t_env01 *env_list)
{
	int		i;
	int		y;
	int		x;
	char	**tab;

	i = 0;
	y = 0;
	tab = ft_calloc((ft_strlen(str) + 1), sizeof(char *));
	
	(void)(env_list);
	// printf("expander result is %d", expander(str, env_list));
	while (str[i] != '\0')
	{
		if (str[i] > 32)
		{
			x = 0;
			tab[y] = ft_calloc((ft_strlen(str) + 1), sizeof(char));
			while (str[i] > 32)
			{
				if (str[i] == 34 && str[i + 1] != '\0')
				{
					i++;
					while (str[i] != 34)
					{
						tab[y][x] = str[i];
						i++;
						x++;
					}
					i++;
				}
				else if (str[i] == 39 && str[i + 1] != '\0')
				{
					i++;
					while (str[i] != 39)
					{
						tab[y][x] = str[i];
						i++;
						x++;
					}
					i++;
				}
				else
				{
					tab[y][x] = str[i];
					i++;
					x++;
				}
			}
			tab[y][x] = '\0';
			y++;
		}
		else
			i++;
	}
	tab[y] = NULL;
	return (tab);
}

void	ft_node_deleter(t_token *first)
{
	t_token	*node;

	node = first;
	while (first)
	{
		free(first->token);
		first = first->next;
		free(node);
		node = first;
	}
}

void	ft_final_stamper(t_command_line *cmd_line)
{
	t_token	*node;

	node = cmd_line->single_token;
	while (cmd_line)
	{
		printf("\n ___+++___+++ NEW MATRIX STRING +++___+++___+++___+++___\n");
		printf("|\n");
		printf("|   New Matrix String: %s\n", cmd_line->new_matrix_string);
		printf("|\n\n");
		while (node)
		{
			printf("\n __INIZIO NODO TOKEN_______________\n");
			printf("|\n");
			printf("|\n");
			printf("|   Pos:   %d\n", node->pos);
			printf("|   Type:  %d\n", node->type);
			printf("|   Token: %s\n", node->token);
			printf("|\n");
			printf("|________________FINE NODO TOKEN___\n\n");
			node = node->next;
		}
		if (cmd_line->next)
		{
			cmd_line = cmd_line->next;
			node = cmd_line->single_token;
		}
		else
			break ;
	}
}

t_token	*ft_newnode(char *token, int pos)
{
	t_token		*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (ft_node_builtin_typer(token) != 1)
	{
		node->type = ft_node_builtin_typer(token);
	}
	else if (ft_node_redirect_typer(token) != 1)
	{
		node->type = ft_node_redirect_typer(token);
	}
	else
		node->type = ARG;
	node->pos = pos;
	node->token = strdup(token);
	node->next = NULL;
	return (node);
}

t_token	*ft_initialize(t_command_line *first_cmd, t_env01 *env_list)
{
	int				i;
	t_token			*node;
	t_token			*first_token;
	t_command_line	*temp;
	char			**current_line;

	i = 0;
	temp = first_cmd;
	node = NULL;
	first_token = NULL;
	current_line = NULL;
	while (first_cmd)
	{
		i = 0;
		current_line = quote_cleaner_split(first_cmd->new_matrix_string, env_list);
		//printf("%p\n", node);
		//printf("current_line: %s\n", current_line[i]);
		node = ft_newnode(current_line[i], i + 1);
		first_token = NULL;
		first_cmd->env_list = env_list;
		first_cmd->single_token = node;
		i++;
		while (current_line[i])
		{
			//printf("current_line: %s\n", current_line[i]);
			node->next = ft_newnode(current_line[i], i + 1);
			first_cmd->env_list = env_list;
			node = node->next;
			i++;
		}
		first_cmd = first_cmd->next;
		i++;
	}
	first_cmd = temp;
	node = first_token;
	i = 0;
	while (current_line[i])
	{
		free(current_line[i]);
		i++;
	}
	free(current_line);
	
	ft_final_stamper(first_cmd);
	return (first_token);
}