/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:53:50 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 18:45:24 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_split(t_lexer *lx, t_token sep)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] != sep && a == 0)
		{
			j++;
			a = 1;
		}
		else if (lx->lexing[i] == sep)
			a = 0;
		i++;
	}
	return (j);
}

static char	*ft_add_word(char const *src, t_token *tab, t_token sep)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[j] && (tab[j] != sep))
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (src[i] && (tab[i] != sep))
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free_all(char **tab, int size)
{
	while (size != 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab[size]);
	free(tab);
}

char	**split_token(t_lexer *lx, t_token sep)
{
	int		i;
	int		k;
	char	**tab;

	k = 0;
	i = 0;
	if (!lx)
		return (NULL);
	tab = ft_calloc((ft_count_split(lx, sep) + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (lx->entry[i])
	{
		if (lx->lexing[i] != sep && (i == 0 || (lx->lexing[i - 1] == sep)))
		{
			tab[k] = ft_add_word(&lx->entry[i], &lx->lexing[i], sep);
			if (tab[k] == NULL)
				ft_free_all(tab, k);
			if (tab[k] == NULL)
				return (NULL);
			k++;
		}
		i++;
	}
	return (tab);
}

