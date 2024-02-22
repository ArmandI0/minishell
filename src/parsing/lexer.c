/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/02/22 17:38:59 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void add_token(char *entry, t_token *tab_token);
static char *supp_extra_spaces(t_lexer *lx);
static t_bool		check_quotes(t_lexer *lx);
static void	set_quotes(t_lexer *lx);

t_lexer *lexing(char *line)
{
	int size;
	t_token *tab_token;
	t_lexer	*tab_lexer;
	//char *newline;
	int i;

	i = 0;

	tab_lexer = malloc(sizeof(tab_lexer));
	size = ft_strlen(line);
	tab_token = ft_calloc(size + 1, sizeof(t_token));
	if (tab_token == NULL)
		return (NULL);
	tab_lexer->entry = line;
	tab_lexer->lexing = tab_token;
	/* TOKEN SETTINGS */
	add_token(line, tab_token);
	/* QUOTES */
	if (check_quotes(tab_lexer) == FALSE)
	{
		//FREE ALL
		return (NULL); //ERROR
	}
	set_quotes(tab_lexer);
	ft_printf("%s", supp_extra_spaces(tab_lexer));
	ft_printf("\n");
	// while (line[i])
	// {
	// 	ft_printf("%d", tab_token[i]);
	// 	i++;
	// }
	ft_printf("\n");

	return (tab_lexer);
}


static void add_token(char *entry, t_token *tab_token)
{
	int i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] == '$')
			tab_token[i] = DOLLAR;
		else if (entry[i] == '<' || entry[i] == '>')
			tab_token[i] = REDIRECTION_OPERATOR;
		else if (entry[i] == '|')
			tab_token[i] = PIPE;
		else if (entry[i] == 39)
			tab_token[i] = SINGLE_QUOTE;
		else if (entry[i] == 34)
			tab_token[i] = DOUBLE_QUOTE;
		else if (entry[i] == 32)
			tab_token[i] = IS_SPACE;
		else
			tab_token[i] = CHARACTER;
		i++;
	}
	tab_token[i] = -1;
}

static char *supp_extra_spaces(t_lexer *lx)
{
	char **tmp;
	char *newline;
	int i;

	i = 0;
	tmp = split_lexer(lx, IS_SPACE, 32);
	if (tmp == NULL)
		return (NULL);
	newline = ft_calloc(1, sizeof(char));
	while (tmp[i])
	{
		newline = ft_fstrjoin(newline, tmp[i]);
		newline = ft_strjoin(newline, " ", TRUE);
		i++;
	}
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
				{
					quote = TRUE;
					break;
				}
			}					
		}
		i++;
	}
	return (quote);
}

static void	set_quotes(t_lexer *lx)
{
	int i;
	t_token a;

	i = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == SINGLE_QUOTE || lx->lexing[i] == DOUBLE_QUOTE)
		{
			a = lx->lexing[i];
			while (lx->entry[i])
			{
				i++;
				if (lx->lexing[i] == a)
					break;
				else
					lx->lexing[i] = CHARACTER;
			}					
		}
		i++;
	}
}


/* UNIT TEST */

// int main(int argc, char **argv)
// {
// 	t_lexer	*test;
// 	char	*all_arg;
// 	char	**split = NULL;
// 	int		i;
// 	int		y = 0;

// 	i = 1;
// 	if (argc < 2)
// 		return (0);					
// 	all_arg = ft_calloc(1, sizeof(char));
// 	while (argv[i])
// 	{
// 		all_arg = ft_strjoin(all_arg, argv[i], TRUE);
// 		i++;
// 	}
// 	//ft_printf("%s\n", all_arg);
// 	test = malloc(sizeof(t_lexer));
// 	test->lexing = malloc(sizeof(t_token) * (ft_strlen(all_arg) + 1));
// 	test->entry = all_arg;
// 	add_token(test->entry, test->lexing);
// 	set_quotes(test);
// 	split = split_lexer(test, IS_SPACE, 32);
// 	i = 0;
// 	if (split == NULL)
// 	{
// 		ft_printf("NULL");
// 		return (0);
// 	}
// 	while (split[y])
// 	{
// 		while (split[y][i])	
// 		{
// 			ft_putchar_fd(split[y][i], 1);
// 			i++;
// 		}
// 		y++;
// 	}
// }