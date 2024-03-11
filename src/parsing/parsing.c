/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 17:09:05 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*FOR TESTING*/
// cat file2 file3
// cat < file2 file3
// cat file3 < file2
// file2 cat < file3

void printList(t_list* node);

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
		if (operator == FALSE && n_node->cmd == NULL && tline[i] == CHAR)
			n_node->cmd = init_command_struct(&line[i], &tline[i], envp);
		i++;
	}	
	return (n_node);
}

void	supp_node_list(t_list **args, t_list *node)
{
	t_list	*top;
	t_list	*bottom;

	if (node != NULL && *args == node)
	{
		*args = node->next;
		free_node(node);
	}
	else
	{
		top = node->prev;
		bottom = node->next;
		top->next = bottom;
		if (bottom != NULL)
			bottom->prev = top;
		free_node(node);
	}	
}

void	delete_quote(t_list **args)
{
	t_list	*tmp;

	tmp = *args;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "\"", 2) == 0  || ft_strncmp(tmp->content, "\'", 2) == 0)
		{
			supp_node_list(args, tmp);
			tmp = *args;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

/*#################test : <<here_doc infile cat < file1 <file2 | cat >> here | grep -a "file 1   " */

t_bool	parsing(char *line, t_sh_data *data)
{
	t_lexer		*lx;
	t_list		**a = NULL;
	
	lx = lexing(line);
	if (lx == NULL)
		return 0;
	//print_lexer(lx);
	a = ft_calloc(1, sizeof(t_list *));	
	if (a == NULL)
		return 0;
	lx = replace_variable(data, lx);
	//print_lexer(lx);
	split_cmd(lx, a);
	//printList(*a);
	suppr_quotes(a);
	//printList(*a);
	redirection_parsing(a, data);
	command_parsing(a, data);
	//print_all_bloc(data);
	ft_lstclear(a);
	free(a);
	free_lexer(lx);
	return (1);
}
