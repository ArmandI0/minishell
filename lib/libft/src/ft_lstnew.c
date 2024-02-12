/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:18:31 by aranger           #+#    #+#             */
/*   Updated: 2023/12/27 09:57:35 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	struct s_list	*a;

	a = malloc(sizeof(t_list));
	if (a == NULL)
		return (NULL);
	a->prev = NULL;
	a->content = content;
	a->next = NULL;
	return (a);
}
