/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/02/13 17:46:51 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_entry(int argc, char *argv[]);
static void	add_token(char *entry, t_token *tab_token);

void	list_of_command(int argc, char **argv)
{
	char	*entry;
	int		size;
	t_token	*tab_token;
	int		i;
	
	/*test*/
	char	*test = " cat   -e -t << file1 |  >  < grep -a | $PATH=fdgdgd fsfa";


	i = 0;
	entry = join_entry(argc, argv);
	size = ft_strlen(test);
	tab_token = ft_calloc(size, sizeof(t_token));
	add_token(test, tab_token);
	ft_printf("%s\n", test);
	while (test[i])
	{
		ft_printf("%d", tab_token[i]);
		i++;
	}

	
}

static void	add_token(char *entry, t_token *tab_token)
{
	int	i;

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
			tab_token[i] = SPACE;
		else
			tab_token[i] = CHARACTER;
		i++;
	}
}


static char	*join_entry(int argc, char *argv[])
{
	int		i;
	char	*argv_join;
	char	*tmp;

	i = 1;
	argv_join = ft_calloc(1, sizeof(char));
	while (i < argc)
	{
		tmp = ft_strjoin(argv_join, argv[i], TRUE);
		argv_join = ft_strjoin(tmp, " ", TRUE);
		i++;
	}
	return (argv_join);
}