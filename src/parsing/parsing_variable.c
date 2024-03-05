/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:24:34 by aranger           #+#    #+#             */
/*   Updated: 2024/03/05 18:45:10 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_var(t_env_var *env, char *var)
{
	t_env_var	*tmp;
	char		*value;

	value = NULL;
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, var, ft_strlen(var) + 1) == 0)
		{
			value = ft_strdup(tmp->value);
			break;
		}
		tmp = tmp->next;
	}
	if (value == NULL)
		value = ft_strdup(" ");
	return (value);
}

void	replace_var(t_list **args, t_sh_data *data)
{
	int	i;
	char	*tmp;
	t_list	*node;
	t_list	*new_node;

	i = 0;
	node = *args;
	while (node != NULL)
	{
		if (node->content != NULL && ft_strncmp(node->content, "$", 2) == 0)
		{
			if (node->next != NULL)
			{
				tmp = find_var(data->env_var1, node->next->content);
				new_node = node->next;
				free(new_node->content);
				new_node->content = tmp;
				if (node->prev == NULL)
				{
					free_node(node);
					*args = new_node;
				}
				else
				{
					node = node->prev;
					free_node(node->next);
					node->next = new_node;
				}
			}		
		}
		node = node->next;
	}
}