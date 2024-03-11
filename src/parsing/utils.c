/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:58:08 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 15:32:34 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*replace_lexer(char *new_entry, t_lexer *lx)
{
	int	size;

	size = ft_strlen(new_entry);
	if (lx != NULL)
	{
		free(lx->lexing);
		free(lx->entry);
		lx->lexing = malloc(sizeof(t_token) * (size + 1));
		if (lx->lexing == NULL)
			return (NULL);
		lx->entry = new_entry;
		add_token(lx);
		return (lx);
	}
	return (NULL);
}

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

t_bool	check_var_char(char c)
{
	if (c == '_')
		return (TRUE);
	else if (c >= 'A' && c <= 'Z') 
		return (TRUE);
	else if (c >= 'a' && c <= 'z')
		return (TRUE);
	else if (c >= '0' && c <= '9')
		return (TRUE);
	else if (c == '?')
		return (TRUE);
	return (FALSE);
}