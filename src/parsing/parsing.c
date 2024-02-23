/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/23 17:47:31 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	parsing(char *line)
{
	t_lexer *lx;
	
	lx = lexing(line);
	
	
}

/*  ################### MAIN TEST : PARSING ###################  */

int main(int argc, char **argv)
{
	t_lexer	*test;
	char	*all_arg;
	int		i;
	
	i = 1;
	if (argc < 2)
		return (0);					
	all_arg = ft_calloc(1, sizeof(char));
	while (argv[i])
	{
		all_arg = ft_strjoin(all_arg, argv[i], TRUE);
		if (argv[i + 1] != NULL)
			all_arg = ft_strjoin(all_arg, " ", TRUE);
		i++;
	}
	ft_printf("ENTREE :%s\n", all_arg);
	test = lexing(all_arg);
	
	i = 0;
	ft_printf("LEXEUR :");
	if (test != NULL)
	{
		while(test->entry[i])
		{
			ft_printf("%d", test->lexing[i]);
			i++;
		}
		ft_printf("\n");
		ft_printf("LEXEUR :");
		ft_printf("%s", test->entry);
	}
	free_lexer(test);
}