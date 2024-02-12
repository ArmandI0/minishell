/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:28:15 by aranger           #+#    #+#             */
/*   Updated: 2024/01/11 15:38:49 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	struct s_list	*tmp;
	struct s_list	*tmp1;

	if (lst)
	{
		tmp = *lst;
		while (tmp)
		{
			tmp1 = tmp->next;
			free(tmp);
			tmp = tmp1;
		}
		*lst = NULL;
	}
}
