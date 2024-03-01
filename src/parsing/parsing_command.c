/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:24:54 by aranger           #+#    #+#             */
/*   Updated: 2024/03/01 18:20:19 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_parsing(t_list **args, t_sh_data *data)
{
	t_list		*tmp;
	t_bloc_cmd	*new_bloc;
	t_cmd		*new_cmd;

	tmp = *args;
	new_bloc = add_new_bloc(data);
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
			new_bloc = add_new_bloc(data);
		new_cmd->path = find_command_path(data->envp, tmp->content);
		new_cmd->name = tmp->content;
		new_cmd->args = tmp
		printList(*args);
		tmp = tmp->next;
	}
 	print_all_redir(data);
}
