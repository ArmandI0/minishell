/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 17:13:06 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*supp_extra_spaces(t_lexer *lx);
static void		set_quotes(t_lexer *lx);

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
	lexing->entry = supp_extra_spaces(lexing);
	if (lexing->entry == NULL)
	{
		free_lexer(lexing);
		return (NULL);
	}
	free(lexing->lexing);
	size = ft_strlen(lexing->entry);
	lexing->lexing = malloc(sizeof(t_token) * (size + 1));
	add_token(lexing);
	if(lexer_checking(lexing) == 0)
		return (NULL);
	return (lexing);
}

void add_token(t_lexer *lx)
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

	(void)lx;
	i = 0;
	tmp = split_lexer(lx, SPACES, 32);
	if (tmp == NULL)
		return (NULL);
	newline = ft_calloc(1, sizeof(char));
	if (newline == NULL)
	{
		free_split(tmp);
		return (NULL);
	}
	while (tmp[i])
	{
		newline = ft_fstrjoin(newline, tmp[i]);
		newline = ft_strjoin(newline, " ", TRUE);
		i++;
	}
	free(tmp);
	return (newline);
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
