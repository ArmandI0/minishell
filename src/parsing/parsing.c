/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/06 13:56:48 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*FOR TESTING*/
// cat file2 file3
// cat < file2 file3
// cat file3 < file2
// file2 cat < file3

void printList(t_list* node);

void	split_cmd(t_lexer *lx, t_list **args)
{
	size_t		i;
	size_t		j;
	size_t		size;
	t_token	tmp;
	t_list	*new_arg;

	i = 0;
	while (i < ft_strlen(lx->entry))
	{
		size = 0;
		j = i;
		tmp = lx->lexing[i];
		if (lx->lexing[i] != SPACES)
		{
			if (lx->lexing[j] == DOLLAR || lx->lexing[j] == PIPE)
				size = 1;
			else
			{
				while (lx->lexing[j] == tmp)
				{
					size++;
					j++;
				}
			}
			new_arg = ft_lstnew(strdup_size(&lx->entry[i], size));
			ft_lstadd_back(args, new_arg);
		}
		else
			i++;
		i += size;
	}
}

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
	//t_bloc_cmd **lc;
	t_list		**a = NULL;
	(void)data;
	lx = lexing(line);
	if (lx == NULL)
		return 0;
	//print_lexer(lx); //affichage du lexeur;
	a = ft_calloc(1, sizeof(t_list *));	
	if (a == NULL)
		return 0;
	split_cmd(lx, a);
	printList(*a);
	replace_var(a, data);
	delete_quote(a);
	//rajouter d'enlever les quotes dans les arguments !!!
	printList(*a);
	redirection_parsing(a, data);
	command_parsing(a, data);
	print_all_bloc(data);
	ft_lstclear(a);
	free(a);
	free_lexer(lx);
	return (1);
}
