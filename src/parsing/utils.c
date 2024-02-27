/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:58:08 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 17:07:53 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_path_acces(char *path)
{
	int	a;

	a = access(path, F_OK | R_OK);
	if (a == -1)
		return (FALSE);
	return (TRUE);
}

char	*strdup_size(const char *src, size_t size)
{
	size_t		i;
	char	*dest;

	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}