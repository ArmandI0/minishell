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
		if (ft_strncmp(tmp->content, "\"", 2) == 0
			|| ft_strncmp(tmp->content, "\'", 2) == 0)
		{
			supp_node_list(args, tmp);
			tmp = *args;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

void print_all_bloc(t_sh_data *a);

t_bool	parsing(char *line, t_sh_data *data)
{
	t_lexer		*lx;
	t_list		**a;

	lx = lexing(line);
	if (lx == NULL)
		return (0);
	a = ft_calloc(1, sizeof(t_list *));
	if (a == NULL)
		return (0);
	lx = replace_variable(data, lx);
	split_cmd(lx, a);
	suppr_quotes(a);
	redirection_parsing(a, data);
	command_parsing(a, data);
	ft_lstclear(a);
	print_all_bloc(data); //
	free(a);
	free_lexer(lx);
	return (1);
}
