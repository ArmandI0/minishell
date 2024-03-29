/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:24:54 by aranger           #+#    #+#             */
/*   Updated: 2024/03/29 20:03:04 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_builtin	check_builtin(char *cmd);
static char			**all_args(t_list *args);
static int			count_args(char **args);
static t_cmd		*set_new_cmd(t_bloc_cmd *bloc,
						t_sh_data *data, t_list *list);

void	command_parsing(t_list **args, t_sh_data *data)
{
	t_list		*tmp;
	t_bloc_cmd	*bloc;
	int			i;

	tmp = *args;
	bloc = data->bloc;
	i = 0;
	while (tmp != NULL && bloc != NULL)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			bloc = bloc->next;
			tmp = tmp->next;
		}
		else
		{
			bloc->cmd = set_new_cmd(bloc, data, tmp);
			while (tmp != NULL && ft_strncmp(tmp->content, "|", 2) != 0)
				tmp = tmp->next;
		}	
		// i++;
		// if (tmp != NULL)
		// 	tmp = tmp->next;
	}
}

static t_cmd	*set_new_cmd(t_bloc_cmd *bloc, t_sh_data *data, t_list *list)
{
	t_cmd	*new_cmd;

	if (list == NULL)
	{
		bloc->builtin = BT_NO;
		return (NULL);
	}
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	bloc->builtin = check_builtin(list->content);
	if (bloc->builtin == BT_NO)
	{
		new_cmd->path = find_command_path(data->env_var1, list->content);
		if (new_cmd->path == NULL)
			new_cmd->path = ft_strdup(list->content);
	}
	new_cmd->name = ft_strdup(list->content);
	new_cmd->args = all_args(list);
	new_cmd->argc = count_args(new_cmd->args);
	return (new_cmd);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (0);
	while (args[i])
		i++;
	return (i);
}

static char	**all_args(t_list *args)
{
	t_list	*tmp;
	char	**all_args;
	int		size;

	tmp = args;
	size = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	all_args = ft_calloc(size + 1, sizeof(char *));
	if (all_args == NULL)
		return (NULL);
	tmp = args;
	size = 0;
	while (tmp != NULL && ft_strncmp(tmp->content, "|", 2) != 0)
	{
		all_args[size] = ft_strdup(tmp->content);
		tmp = tmp->next;
		size++;
	}
	return (all_args);
}

static t_builtin	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BT_ECHO);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BT_CD);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BT_PWD);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (BT_EXPORT);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BT_UNSET);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (BT_ENV);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BT_EXIT);
	else
		return (BT_NO);
}
