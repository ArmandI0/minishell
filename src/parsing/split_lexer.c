/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:53:50 by aranger           #+#    #+#             */
/*   Updated: 2024/02/23 11:18:47 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_split(t_lexer *lx, t_token sep, char c)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = 0;
	while (lx->entry[i])
	{
		if (lx->entry[i] != c && lx->lexing[i] != sep && a == 0)
		{
			j++;
			a = 1;
		}
		else if (lx->entry[i] == c && lx->lexing[i] == sep)
			a = 0;
		i++;
	}
	return (j);
}

static char	*ft_add_word(char const *src, t_token *tab, t_token sep, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[j] && (src[j] != c || tab[j] != sep))
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (src[i] && (src[i] != c || tab[i] != sep))
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	*ft_free_all(char **tab, int size)
{
	while (size != 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab[size]);
	free(tab);
	return (NULL);
}

char	**split_lexer(t_lexer *lx, t_token sep, char c)
{
	int		i;
	int		k;
	char	**tab;

	k = 0;
	i = 0;
	if (!lx)
		return (NULL);
	tab = ft_calloc((ft_count_split(lx, sep, c) + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (lx->entry[i])
	{
		if (lx->entry[i] != c && lx->lexing[i] != sep
			&& (i == 0 || (lx->entry[i - 1] == c && lx->lexing[i - 1] == sep)))
		{
			tab[k] = ft_add_word(&lx->entry[i], &lx->lexing[i], sep, c);
			if (tab[k] == NULL)
				return (ft_free_all(tab, k));
			k++;
		}
		i++;
	}
	return (tab);
}
