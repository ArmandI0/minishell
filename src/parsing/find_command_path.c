/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:41 by aranger           #+#    #+#             */
/*   Updated: 2024/02/14 15:23:46 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*set_command_path(char **envp, char *command);
static char		**find_path(char **envp);
static char		**join_path_command(char **all_path, char *command);
static char		*set_command(char *command);

char	*find_command_path(char **envp, char *command)
{
	char	*command_path;
	char	**split_command;

	if (*command == '\0')
		return (NULL);
	command_path = NULL;
	split_command = ft_split(command, ' ');
	if (split_command[0] != NULL && check_path_acces(split_command[0]) == TRUE)
	{
		command_path = ft_strdup(split_command[0]);
		return (command_path);
	}
	command_path = set_command_path(envp, split_command[0]);
	free_split(split_command);
	return (command_path);
}

static char	*set_command_path(char **envp, char *command)
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

static char	**find_path(char **envp)
{
	int		i;
	int		j;
	char	**split_path;

	i = 0;
	j = 0;
	split_path = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	while (envp[i] && envp[i][j] && envp[i][j] != '=')
		j++;
	if (envp[i] != NULL)
		split_path = ft_split(&envp[i][j + 1], ':');
	return (split_path);
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
