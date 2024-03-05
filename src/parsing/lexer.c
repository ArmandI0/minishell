/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/03/05 10:06:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		add_token(t_lexer *lx);
static char		*supp_extra_spaces(t_lexer *lx);
static t_bool	check_quotes(t_lexer *lx);
static void		set_quotes(t_lexer *lx);

int		check_redir_lexer(t_lexer *lx)
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

t_lexer	*lexing(char *line)
{
	t_lexer	*lexing;
	int		size;

	if (!line)
		return (NULL);
	lexing = malloc(sizeof(t_lexer));
	if (lexing == NULL)
		return (NULL);
	size = ft_strlen(line);
	lexing->lexing = malloc(sizeof(t_token) * (size + 1));
	if (lexing->lexing == NULL)
	{
		free(lexing);
		return (NULL);
	}
	lexing->entry = line;
	add_token(lexing);
	if (check_redir_lexer(lexing) == 0)
	{
		free(lexing->lexing);
		free(lexing);
		ft_printf_fd(1, "PB de  <<>>");
		return (NULL);
	}
	if (check_quotes(lexing) == FALSE)
	{
		quote_error(lexing);
		return (NULL);
	}
	lexing->entry = supp_extra_spaces(lexing);
	free(lexing->lexing);
	size = ft_strlen(lexing->entry);
	lexing->lexing = malloc(sizeof(t_token) * (size + 1));
	add_token(lexing);
	return (lexing);
}

static void add_token(t_lexer *lx)
{
	int i;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->entry[i] == '$')
			lx->lexing[i] = DOLLAR;
		else if (lx->entry[i] == '<' || lx->entry[i] == '>')
			lx->lexing[i] = REDIRECTION_OPERATOR;
		else if (lx->entry[i] == '|')
			lx->lexing[i] = PIPE;
		else if (lx->entry[i] == 39)
			lx->lexing[i] = SINGLE_QUOTE;
		else if (lx->entry[i] == 34)
			lx->lexing[i] = DOUBLE_QUOTE;
		else if (lx->entry[i] == 32)
			lx->lexing[i] = SPACES;
		else
			lx->lexing[i] = CHARACTER;
		i++;
	}
	lx->lexing[i] = T_NULL;
	set_quotes(lx);

}

static char *supp_extra_spaces(t_lexer *lx)
{
	char **tmp;
	char *newline;
	int i;

	i = 0;
	tmp = split_lexer(lx, SPACES, 32);
	if (tmp == NULL)
		return (NULL);
	newline = ft_calloc(1, sizeof(char));
	while (tmp[i])
	{
		newline = ft_fstrjoin(newline, tmp[i]);
		newline = ft_strjoin(newline, " ", TRUE);
		i++;
	}
	free(tmp);
	return (newline);
}

static t_bool	check_quotes(t_lexer *lx)
{
	int i;
	t_bool quote;
	t_token a;

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

static void	set_quotes(t_lexer *lx)
{
	int i;
	t_token a;

	i = 0;
	a = CHARACTER;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == SINGLE_QUOTE || lx->lexing[i] == DOUBLE_QUOTE)
		{
			a = lx->lexing[i];
			while (lx->entry[i])
			{
				i++;
				if (lx->entry[i] == '\0' || lx->lexing[i] == a)
					break;
				else if (lx->entry[i] == '$' && a == DOUBLE_QUOTE)
					lx->lexing[i] = DOLLAR;
				else
					lx->lexing[i] = CHARACTER;
			}					
		}
		if (lx->entry[i] != '\0')
			i++;
	}
}
