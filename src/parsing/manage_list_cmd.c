/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:15:25 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 12:23:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//static t_bloc_cmd	*lst_cmd_last(t_bloc_cmd *lst);

void	lst_cmd_add_new(t_bloc_cmd **list)
{
	t_bloc_cmd	*new;
	t_bloc_cmd	*tmp;

	new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (new == NULL)
		return ;
	tmp = *list;
	if (tmp == NULL)
		*list = new;
	else
	{
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}


// void	lst_cmd_add_back(t_bloc_cmd **lst, t_bloc_cmd *new)
// {
// 	t_bloc_cmd	*a;

// 	if (new)
// 	{
// 		a = lst_cmd_last(*lst);
// 		if (a != 0)
// 		{
// 			a->next = new;
// 			new->prev = a;
// 		}
// 		else
// 			*lst = new;
// 	}
// }

// static t_bloc_cmd	*lst_cmd_last(t_bloc_cmd *lst)
// {
// 	t_bloc_cmd	*ptr;

// 	if (lst)
// 	{
// 		ptr = lst;
// 		while (ptr->next != NULL)
// 		{
// 			ptr = ptr->next;
// 		}
// 		return (ptr);
// 	}
// 	return (NULL);
// }

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

// void print_list(t_bloc_cmd *lst)
// {
//     t_bloc_cmd *current = lst;

//     while (current != NULL)
// 	{
// 		printf("PREV: %p\n", current->prev);
// 		printf("ADR: %p\n", current);
//     	printf("ID: %d\n", current->id);
//     	printf("Limiter: %s\n", current->limiter);
//     	printf("Hdoc: %s\n", current->hdoc);
// 		printf("NEXT: %p\n", current->next);
//         printf("\n");
//         current = current->next;
//     }
// }

// int main(void)
// {
// 	t_bloc_cmd	**list = NULL;
// 	int			i = 0;

// 	list = ft_calloc(1, sizeof(t_list *));
// 	while (i < 3)
// 	{
// 		lst_cmd_add_new(list);
// 		i++;
// 	}
// 	print_list(*list);
// 	return (0);
// }
