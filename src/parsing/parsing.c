/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 12:23:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bloc_cmd	*set_new_node(char *line, t_token *tline, char **envp)
{
	int			i;
	t_bloc_cmd	*n_node;
	t_bool		operator;

	i = 0;
	operator = FALSE;
	n_node = ft_calloc(1, sizeof(t_bloc_cmd));
	while (line[i] != '\0' && tline[i] != PIPE)
	{
		if (operator == FALSE && n_node->cmd == NULL && tline[i] == CHARACTER)
			n_node->cmd = init_command_struct(&line[i], &tline[i], envp);
		i++;
	}	
	return (n_node);
}

void	parsing(char *line, char **envp)
{
	t_lexer		*lx;
	t_bloc_cmd **lc;
	//int		i;
	
	lx = lexing(line);
	if (lx == NULL) 	
		return ;
	lc = malloc(sizeof(t_bloc_cmd *));
	*lc = set_new_node(lx->entry, lx->lexing, envp);
	ft_printf("%s\n", (*lc)->cmd->name);
	ft_printf("%s\n", (*lc)->cmd->path);
}


/*  ################### MAIN TEST : PARSING ###################  */

int main(int argc, char **argv, char **envp)
{
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
	parsing(all_arg, envp);	
}