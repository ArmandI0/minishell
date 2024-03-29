/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 15:24:30 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bloc_cmd	*add_new_bloc(t_sh_data *data, int id);
static t_list		*add_new_redir(t_bloc_cmd *lst, t_redir_def type,
						t_list *node, t_list **head);
static t_list		*suppp_from_list(t_list *node, t_list **head);
static t_list	*find_redir(t_list *tmp, t_bloc_cmd *new_bloc, t_list **args);

void	redirection_parsing(t_list **args, t_sh_data *data)
{
	t_list		*tmp;
	t_bloc_cmd	*new_bloc;
	int			i;

	tmp = *args;
	i = 0;
	new_bloc = add_new_bloc(data, i);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			new_bloc = add_new_bloc(data, i);
			i++;
		}
		if (tmp->next != NULL)
		{
			tmp = find_redir(tmp, new_bloc, args);
		}
		else
			break ;
	}
}

static t_list	*find_redir(t_list *tmp, t_bloc_cmd *new_bloc, t_list **args)
{
 	if (ft_strncmp(tmp->content, "<<", 3) == 0)
		tmp = add_new_redir(new_bloc, HEREDOC, tmp, args);
	else if (ft_strncmp(tmp->content, ">>", 3) == 0)
		tmp = add_new_redir(new_bloc, APPEND, tmp, args);
	else if (ft_strncmp(tmp->content, "<", 2) == 0)
		tmp = add_new_redir(new_bloc, INPUT_REDIR, tmp, args);
	else if (ft_strncmp(tmp->content, ">", 2) == 0)
		tmp = add_new_redir(new_bloc, OUTPUT_REDIR, tmp, args);
	else
		tmp = tmp->next;
	return (tmp);
}

static t_list	*add_new_redir(t_bloc_cmd *lst, t_redir_def type,
					t_list *node, t_list **head)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = lst->redir;
	new = ft_calloc(1, sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->type = type;
	if (type == HEREDOC)
		new->lim_hdoc = ft_strdup(node->next->content);
	else
		new->file_path = ft_strdup(node->next->content);
	if (tmp == NULL)
		lst->redir = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (suppp_from_list(node, head));
}

static t_bloc_cmd	*add_new_bloc(t_sh_data *data, int id)
{
	t_bloc_cmd	*new;
	t_bloc_cmd	*tmp;

	tmp = data->bloc;
	new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (new == NULL)
		return (NULL);
	if (tmp == NULL)
		data->bloc = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (new != NULL)
		new->id = id;
	return (new);
}

static t_list	*suppp_from_list(t_list *node, t_list **head)
{
	t_list	*tmp;
	t_list	*new_head;

	if (node->prev == NULL)
	{
		new_head = node->next->next;
		free_node(node->next);
		free_node(node);
		*head = new_head;
		if (*head != NULL)
			new_head->prev = NULL;
		tmp = new_head;
	}
	else
	{
		new_head = node->prev;
		tmp = node->next->next;
		free_node(node->next);
		free_node(node);
		new_head->next = tmp;
		if (tmp != NULL)
			tmp->prev = new_head;
	}
	return (tmp);
}
