/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:15:25 by aranger           #+#    #+#             */
/*   Updated: 2024/02/23 10:22:30 by aranger          ###   ########.fr       */
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

// void *lst_cmd_last(void *lst) 
// {
//     t_list	*ptr;

//     if (lst)
// 	{
//         ptr = lst;
//         while (ptr->next != NULL)
// 		{
//             ptr = ptr->next;
//         }
//         return ptr;
//     }
//     return NULL;
// }

/* UNIT TEST */

// void print_list(t_list_cmd *lst)
// {
//     t_list_cmd *current = lst;

//     while (current != NULL) {
//         // Affichage des champs de la structure t_list_cmd
// //		printf("PREV: %p\n", current->prev);
// //		printf("ADR: %p\n", &current);
// //        printf("ID: %d\n", current->id);
// //        printf("Limiter: %s\n", current->limiter);
// //        printf("Hdoc: %s\n", current->hdoc);
//         // Affichage des champs de la structure t_redir (s'il y a des redirections)
// //		printf("NEXT: %p\n", current->next);

//         printf("\n");

//         current = current->next;
//     }
// }

// int main(void)
// {
// 	t_list_cmd	*tmp;
// 	t_list_cmd	**list = NULL;
// 	int			i = 0;

// 	list = ft_calloc(1, sizeof(t_list *));
// 	while (i < 3)
// 	{
// 		tmp = (t_list_cmd *)lst_cmd_new(sizeof(t_list_cmd));
// 		lst_cmd_add_back(list, tmp);
// 		i++;
// 	}
// 	print_list(*list);
// 	return (0);
// }
