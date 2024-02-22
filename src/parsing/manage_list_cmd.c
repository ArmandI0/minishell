/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:15:25 by aranger           #+#    #+#             */
/*   Updated: 2024/02/22 18:07:25 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list_cmd	*lst_cmd_last(t_list_cmd *lst);

void	*lst_cmd_new(size_t size)
{
	unsigned char *a;

	a = ft_calloc(1, sizeof(size));
	if (a == NULL)
		return (NULL);
	return ((void *)a);
}

void	lst_cmd_add_back(t_list_cmd **lst, t_list_cmd *new)
{
	t_list_cmd	*a;

	if (new)
	{
		a = lst_cmd_last(*lst);
		if (a != 0)
		{
			a->next = new;
			new->prev = a;
		}
		else
			*lst = new;
	}
}

static t_list_cmd	*lst_cmd_last(t_list_cmd *lst)
{
	t_list_cmd	*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		return (ptr);
	}
	return (NULL);
}

/* UNIT TEST */

int main(void)
{
	t_list_cmd	*a;

	a = lst_cmd_new(sizeof(t_list_cmd));
	if (a == NULL)
		return (0);
	a->id = 5;
	ft_printf("%d", a->id);
	return (0);
}
