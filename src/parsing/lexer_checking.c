/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:27 by aranger           #+#    #+#             */
/*   Updated: 2024/03/05 12:25:42 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	pipe_checking(t_lexer *lx);
static t_bool	quotes_checking(t_lexer *lx);
static t_bool	redirection_checking(t_lexer *lx);

t_bool	lexer_checking(t_lexer *lx)
{
	if (redirection_checking(lx) == FALSE)
	{
		ft_printf_fd(2, "redirection syntax error \n");
		free_lexer(lx);
		return (FALSE);
	}
	if (pipe_checking(lx) == FALSE)
	{
		ft_printf_fd(2, "syntax error near unexpected token `|\n");
		free_lexer(lx);
		return (FALSE);
	}
	if (quotes_checking(lx) == FALSE)
	{
		ft_printf_fd(2, "quotes syntax error \n");
		free_lexer(lx);		
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	pipe_checking(t_lexer *lx)
{
	int	i;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == PIPE && lx->lexing[i + 1] == PIPE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	quotes_checking(t_lexer *lx)
{
	int		i;
	t_bool	quote;
	t_token	a;

	i = 0;
	quote = TRUE;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == SINGLE_QUOTE || lx->lexing[i] == DOUBLE_QUOTE)
		{
			a = lx->lexing[i];
			quote = FALSE;
			while (lx->entry[i])
			{
				i++;
				if (lx->lexing[i] == a)
					quote = TRUE;
				if (lx->lexing[i] == a)
					break ;
			}					
		}
		if (lx->entry[i] != '\0')
			i++;
	}
	return (quote);
}

static t_bool	redirection_checking(t_lexer *lx)
{
	int	i;
	int	j;
	int	a;

	a = 0;
	i = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == REDIRECTION_OPERATOR)
		{
			j = 1;
			while (lx->entry[i + j] && lx->lexing[i + j] == REDIRECTION_OPERATOR)
			{
				if (j >= 2)
					return (0);
				if (lx->entry[i] != lx->entry[i + j])
					return (0);
				j++;
			}
			while (lx->entry[i + j] && (lx->lexing[i + j] != REDIRECTION_OPERATOR && lx->lexing[i + j] != PIPE))
			{
				if (lx->lexing[i + j] == CHARACTER || lx->lexing[i + j] == SINGLE_QUOTE || lx->lexing[i + j] == DOUBLE_QUOTE)
				{
					a = 1;
					break;
				}
				j++;
			}
			if (a == 0)
				return (0);
		}
		i++;
	}
	return (1);
}