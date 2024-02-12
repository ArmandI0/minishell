/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:31:07 by aranger           #+#    #+#             */
/*   Updated: 2023/11/02 15:54:17 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[j]) != NULL && j != 0)
		j--;
	if (j == 0 && s1)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (j - i + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[i], j - i + 2);
	return (str);
}
