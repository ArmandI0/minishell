/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:57:20 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 21:11:26 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*suppression_fct(char *line)
{
	t_lexer	*lx;
	char	**tab;
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(line);
	lx = malloc(sizeof(t_lexer));
	lx->entry = line;
	lx->lexing = malloc(sizeof(t_token) * (size + 1));
	if (lx == NULL)
		return (NULL);
	add_token(lx);
	while (lx->entry[i])
	{
		if (lx->lexing[i] == DOUBLE_QUOTE || lx->lexing[i] == SINGLE_QUOTE)
			lx->lexing[i] = SPLIT;
		i++;
	}
	tab = split_token(lx, SPLIT);
	i = 0;
	free_lexer(lx);
	tmp = ft_calloc(1, sizeof(char));
	while (tab[i])
	{
		tmp = ft_fstrjoin(tmp, tab[i]);
		i++;
	}
	free(tab);
	return (tmp);
}

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