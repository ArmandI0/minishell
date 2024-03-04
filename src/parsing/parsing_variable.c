/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:24:34 by aranger           #+#    #+#             */
/*   Updated: 2024/03/04 15:35:17 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_var(char **envp, char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] && ft_strncmp(envp[i], var, ft_strlen(var)) != 0)
		i++;
	while (envp[i] && envp[i][j] && envp[i][j] != '=')
		j++;
	if (envp[i] != NULL)
		var = ft_strdup(&envp[i][j + 1]);
	return (var);
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
		if (ft_strncmp(node->content, "$", 2) == 0)
		{
			if (node->next != NULL)
			{
				tmp = find_var(data->envp, node->next->content);
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