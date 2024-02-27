/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:18:31 by aranger           #+#    #+#             */
/*   Updated: 2024/02/23 09:22:59 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstnew(size_t size)
{
	unsigned char *a;

	a = ft_calloc(1, sizeof(size));
	if (a == NULL)
		return (NULL);
	return ((void *)a);
}
