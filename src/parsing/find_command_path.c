/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:41 by aranger           #+#    #+#             */
/*   Updated: 2024/03/11 13:44:12 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*set_command_path(t_env_var *envp, char *command);
static char		**find_path(t_env_var *envp);
static char		**join_path_command(char **all_path, char *command);
static char		*set_command(char *command);

char	*find_command_path(t_env_var *envp, char *command)
{
	char	*command_path;

	if (*command == '\0')
		return (NULL);
	command_path = NULL;
	if (command != NULL && check_path_acces(command) == TRUE)
	{
		command_path = ft_strdup(command);
		return (command_path);
	}
	command_path = set_command_path(envp, command);
	return (command_path);
}

static char	*set_command_path(t_env_var *envp, char *command)
{
	char	**all_path;
	char	*command_path;
	int		i;
	t_bool	access;

	i = 0;
	if (command == NULL)
		return (NULL);
	all_path = find_path(envp);
	command_path = set_command(command);
	all_path = join_path_command(all_path, command_path);
	free(command_path);
	while (all_path != NULL && all_path[i])
	{
		access = check_path_acces(all_path[i]);
		if (access == TRUE)
		{
			command_path = ft_strdup(all_path[i]);
			free_split(all_path);
			return (command_path);
		}
		i++;
	}
	free_split(all_path);
	return (NULL);
}

static char	**join_path_command(char **all_path, char *command)
{
	int		i;
	char	**join_path;

	i = 0;
	join_path = NULL;
	if (all_path == NULL)
		return (NULL);
	while (all_path[i])
		i++;
	join_path = ft_calloc(i + 1, sizeof(char *));
	if (join_path == NULL)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		join_path[i] = ft_strjoin(all_path[i], command, 1);
		i++;
	}
	free(all_path);
	return (join_path);
}

static char	**find_path(t_env_var *envp)
{
	t_env_var	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "PATH", 5) == 0)
			return (ft_split(tmp->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*set_command(char *command)
{
	int		size;
	char	*new_command;

	size = ft_strlen(command);
	new_command = ft_calloc(size + 2, sizeof(char));
	if (new_command == NULL)
		return (NULL);
	new_command[0] = '/';
	ft_strlcpy(&new_command[1], command, size + 1);
	return (new_command);
}
