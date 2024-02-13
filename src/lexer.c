/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:22:23 by aranger           #+#    #+#             */
/*   Updated: 2024/02/13 12:01:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_entry(int argc, char *argv[]);

t_list	**list_of_command(int argc, char **argv, char **envp)
{
	char	*entry;

	entry = join_entry(argc, argv);
	

	
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