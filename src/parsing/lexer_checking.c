/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:27 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 17:09:05 by aranger          ###   ########.fr       */
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

static t_bool	check_redir_operator(t_lexer *lx, int i)
{
	int	j;

	j = 1;
	while (lx->entry[i + j] && lx->lexing[i + j] == REDIRECTION_OPERATOR)
	{
		if (j >= 2 || (lx->entry[i] != lx->entry[i + j]))
			return (FALSE);
		j++;
	}
	while (lx->entry[i + j] && (lx->lexing[i + j] != REDIRECTION_OPERATOR && lx->lexing[i + j] != PIPE))
	{
		if (lx->lexing[i + j] == CHAR || lx->lexing[i + j] == SINGLE_QUOTE || lx->lexing[i + j] == DOUBLE_QUOTE)
			return (TRUE);
		j++;
	}
	return (FALSE);
}

static t_bool	redirection_checking(t_lexer *lx)
{
	int	i;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == REDIRECTION_OPERATOR)
		{
			if (check_redir_operator(lx, i) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
