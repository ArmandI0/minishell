/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:57:20 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 15:20:35 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*suppression_fct(char *line);
static void	replace_quote_by_split(t_lexer *lx);
static char	*suppression_fct(char *line);
static char	*split_and_join(t_lexer *lx);

void	suppr_quotes(t_list **args)
{
	t_list	*tmp;

	tmp = *args;
	while (tmp != NULL)
	{
		tmp->content = suppression_fct(tmp->content);
		tmp = tmp->next;
	}
}

static char	*suppression_fct(char *line)
{
	t_lexer	*lx;
	char	*tmp;
	int		size;

	size = ft_strlen(line);
	lx = malloc(sizeof(t_lexer));
	if (lx == NULL)
		return (NULL);
	lx->entry = line;
	lx->lexing = malloc(sizeof(t_token) * (size + 1));
	if (lx->lexing == NULL)
		return (free_lexer(lx));
	add_token(lx);
	replace_quote_by_split(lx);
	tmp = split_and_join(lx);
	return (tmp);
}

static char	*split_and_join(t_lexer *lx)
{
	char	**tab;
	char	*newline;
	int		i;

	i = 0;
	tab = split_token(lx, SPLIT);
	if (tab == NULL)
		return (NULL);
	free_lexer(lx);
	newline = ft_calloc(1, sizeof(char));
	while (tab[i])
	{
		newline = ft_fstrjoin(newline, tab[i]);
		i++;
	}
	free(tab);
	return (newline);
}

static void	replace_quote_by_split(t_lexer *lx)
{
	int	i;

	i = 0;
	if (lx != NULL)
	{
		while (lx->entry[i])
		{
			if (lx->lexing[i] == DOUBLE_QUOTE || lx->lexing[i] == SINGLE_QUOTE)
				lx->lexing[i] = SPLIT;
			i++;
		}
	}
}
