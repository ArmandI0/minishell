/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 14:29:42 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		add_token(t_lexer *lx);
static char		*supp_extra_spaces(t_lexer *lx);
static t_bool	check_quotes(t_lexer *lx);
static void		set_quotes(t_lexer *lx);

t_lexer	*lexing(char *line)
{
	t_lexer	*lexing;
	int 	i;

	i = 0;
	if (!line)
		return (NULL);
	lexing = malloc(sizeof(t_lexer));
	if (lexing == NULL)
		return (NULL);
	lexing->lexing = malloc(sizeof(t_token) * (ft_strlen(line) + 1));
	if (lexing->lexing == NULL)
	{
		free(lexing);
		return (NULL);
	}
	lexing->entry = line;
	add_token(lexing);
	if (check_quotes(lexing) == FALSE)
	{
		quote_error(lexing);
		return (NULL);
	}
	lexing->entry = supp_extra_spaces(lexing);
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
	if (lx->entry != NULL)
		free(lx->entry);
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
				else if (lx->entry[i] == '$' && a == DOUBLE_QUOTE)
					lx->lexing[i] = DOLLAR;
				else
					lx->lexing[i] = CHARACTER;
			}					
		}
		i++;
	}
}

/* ################### MAIN TEST : t_lexer *lexing(char *line) ###################*/


// int main(int argc, char **argv)
// {
// 	t_lexer	*test;
// 	char	*all_arg;
// 	int		i;
	
// 	i = 1;
// 	if (argc < 2)
// 		return (0);					
// 	all_arg = ft_calloc(1, sizeof(char));
// 	while (argv[i])
// 	{
// 		all_arg = ft_strjoin(all_arg, argv[i], TRUE);
// 		if (argv[i + 1] != NULL)
// 			all_arg = ft_strjoin(all_arg, " ", TRUE);
// 		i++;
// 	}
// 	ft_printf("ENTREE :%s\n", all_arg);
// 	test = lexing(all_arg);
	
// 	i = 0;
// 	ft_printf("LEXEUR :");
// 	if (test != NULL)
// 	{
// 		while(test->entry[i])
// 		{
// 			ft_printf("%d", test->lexing[i]);
// 			i++;
// 		}
// 		ft_printf("\n");
// 		ft_printf("LEXEUR :");
// 		ft_printf("%s", test->entry);
// 	}
// 	free_lexer(test);
// }


/* UNIT TEST */
	/* ################### MAIN TEST TOUTES LES FONCTIONS ###################*/


// int main(int argc, char **argv)
// {
// 	t_lexer	*test;
// 	char	*all_arg;
// 	char	**split = NULL;
// 	int		i;
// 	int		y = 0;
// 	//12 33 '"a   b   a"'
// 	i = 1;
// 	if (argc < 2)
// 		return (0);					
// 	all_arg = ft_calloc(1, sizeof(char));
// 	while (argv[i])
// 	{
// 		all_arg = ft_strjoin(all_arg, argv[i], TRUE);
// 		if (argv[i + 1] != NULL)
// 			all_arg = ft_strjoin(all_arg, " ", TRUE);
// 		i++;
// 	}
// 	ft_printf("ENTREE :%s\n", all_arg);
// 	test = malloc(sizeof(t_lexer));
// 	test->lexing = malloc(sizeof(t_token) * (ft_strlen(all_arg) + 1));
// 	test->entry = all_arg;
// 	add_token(test);
// 	set_quotes(test);
// 	i = 0;
// 	ft_printf("LEXEUR :");
// 	while(all_arg[i])
// 	{
// 		ft_printf("%d", test->lexing[i]);
// 		i++;
// 	}
// 	ft_printf("\n");
// 	ft_printf("%s", supp_extra_spaces(test));

// }

	/* ################### TEST SPLIT_LEEXEUR ###################*/

	// split = split_lexer(test, SPACES, 32);
	// i = 0;
	// if (split == NULL)
	// {
	// 	ft_printf("NULL");
	// 	return (0);
	// }
	// ft_printf("SPLIT  :\n");
	// while (split[y])
	// {
	// 	ft_printf("-arg %d :\"%s\"\n",y + 1 , split[y]);
	// 	y++;
	// }