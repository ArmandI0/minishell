/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:25:20 by aranger           #+#    #+#             */
/*   Updated: 2024/03/25 20:34:25 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_var	*duplicate_env(t_env_var *list)
{
	t_env_var	*tmp;
	t_env_var	*start;

	start = NULL;
	if (list != NULL)
	{
		tmp = ft_calloc(1, sizeof(t_env_var));
		if (tmp == NULL)
			return (NULL);
		start = tmp;
		while (list != NULL && tmp != NULL)
		{
			tmp->name = list->name;
			tmp->value = list->value;
			if (list->next != NULL)
				tmp->next = ft_calloc(1, sizeof(t_env_var));
			else
				tmp->next = NULL;
			tmp = tmp->next;
			list = list->next;
		}
	}
	return (start);
}

static void	switch_list(t_env_var *var1, t_env_var *var2)
{
	char	*name;
	char	*value;
	int		exported;

	name = var1->name;
	value = var1->value;
	exported = var1->exported;
	var1->name = var2->name;
	var1->value = var2->value;
	var1->exported = var2->exported;
	var2->name = name;
	var2->value = value;
	var2->exported = exported;
}

static t_env_var	*sort_list(t_env_var *list)
{
	t_env_var	*head;
	t_env_var	*tmp;

	tmp = list;
	head = list;
	while (head)
	{
		while (tmp && tmp->next != NULL)
		{
			if (ft_strcmp(head->name, tmp->name) > 0)
				switch_list(head, tmp);
			tmp = tmp->next;
		}
		head = head->next;
		tmp = head;
	}
	return (list);
}

void	print_env_export(t_sh_data *sh_data)
{
	t_env_var	*head;
	t_env_var	*tmp;

	tmp = duplicate_env(sh_data->env_var1);
	sort_list(tmp);
	head = tmp;
	while (tmp)
	{
		ft_printf_fd(1, "declare -x %s", tmp->name);
		if (tmp->value != NULL)
			ft_printf_fd(1, "=\"%s\"\n", tmp->value);
		else
			ft_printf_fd(1, "\n");
		tmp = tmp->next;
	}
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
