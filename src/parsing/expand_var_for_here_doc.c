/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/12 19:23:30 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_token_heredoc(t_lexer *lx)
{
	int	i;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->entry[i] == '$' && check_var_char(lx->entry[i + 1]) == TRUE)
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
			lx->lexing[i] = CHAR;
		i++;
	}
	lx->lexing[i] = T_NULL;
}

char	*expand_heredoc(char *line, t_sh_data *data)
{
	t_lexer	*lx;
	char	*newline;

	lx = ft_calloc(1, sizeof(t_lexer));
	if (lx == NULL)
		return (NULL);
	lx->lexing = malloc(sizeof(t_token) * (ft_strlen(line) + 1));
	if (lx->lexing == NULL)
	{
		free_lexer(lx);
		return (NULL);
	}
	lx->entry = line;
	add_token_heredoc(lx);
	lx = replace_variable(data, lx);
	free(lx->lexing);
	newline = lx->entry;
	free(lx);
	return (newline);
}
