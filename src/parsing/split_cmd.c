/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:37:07 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 17:09:05 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void remove_dollar_and_quote(t_lexer *lx);
static int add_new_list(t_lexer *lx, t_list **args, int i, char *start);

void	split_cmd(t_lexer *lx, t_list **args)
{
	size_t		i;

	i = 0;
	remove_dollar_and_quote(lx);
	while (i < ft_strlen(lx->entry))
	{
		if (lx->lexing[i] != SPACES)
			i += add_new_list(lx, args, i, &lx->entry[i]);
		else
			i++;
	}
}
static int add_new_list(t_lexer *lx, t_list **args, int i, char *start)
{
	t_list	*new_arg;
	t_token	tmp;
	int		size;

	size = 0;
	tmp = lx->lexing[i];
	if (lx->lexing[i] == PIPE)
		size = 1;
	else
	{
		while (lx->lexing[i] == tmp)
		{
			size++;
			i++;
		}
	}
	new_arg = ft_lstnew(strdup_size(start, size));
	ft_lstadd_back(args, new_arg);
	return (size);
}

static void	remove_dollar_and_quote(t_lexer *lx)
{
	int	i;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == DOUBLE_QUOTE || lx->lexing[i] == DOLLAR || lx->lexing[i] == SINGLE_QUOTE)
			lx->lexing[i] = CHAR;
		i++;
	}
}