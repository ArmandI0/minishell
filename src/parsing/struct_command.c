/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:33:07 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 13:21:04 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_command_struct(char *arg, t_token *t_arg, char **envp)
{
	int		i;
	char	*command;
	t_cmd	*cmd;

	i = 0;
	while (arg[i] != '\0' && t_arg[i] == CHARACTER)
		i++;
	command = malloc(sizeof(char) * (i + 1));
	if (command == NULL)
		return (NULL);
	ft_strlcpy(command, arg, i + 1);
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->name = command;
	cmd->path = find_command_path(envp, command);
	i = 0;
	return (cmd);
}