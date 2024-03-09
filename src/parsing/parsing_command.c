/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:24:54 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 11:45:15 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_builtin	check_builtin(char *cmd);
static char	**all_args(t_list *args);
static int	count_args(char **args);

void	command_parsing(t_list **args, t_sh_data *data)
{
	t_list		*tmp;
	t_bloc_cmd	*bloc;
	t_cmd		*new_cmd;
	int			i;

	tmp = *args;
	bloc = data->bloc;
	i = 0;
	while (tmp != NULL && bloc != NULL)
	{
		if (bloc != NULL && tmp->content && (ft_strncmp(tmp->content, "|", 2) == 0 || i == 0))
		{
			if (ft_strncmp(tmp->content, "|", 2) == 0)
			{
				bloc = bloc->next;
				tmp = tmp->next;
			}
			if (tmp == NULL)
				bloc->builtin = BT_NO;
			else
			{
				new_cmd = ft_calloc(1, sizeof(t_cmd));
				bloc->builtin = check_builtin(tmp->content);
				if (new_cmd == NULL)
					return ;
				if (bloc->builtin == BT_NO)
				{
					new_cmd->path = find_command_path(data->envp, tmp->content);
					if (new_cmd->path == NULL)
						new_cmd->path = ft_strdup(tmp->content);
				}
				new_cmd->name = ft_strdup(tmp->content);
				new_cmd->args = all_args(tmp);
				new_cmd->argc = count_args(new_cmd->args);
				bloc->cmd = new_cmd;
			}
			bloc->id = i;
			i++;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
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
	return(all_args);
}

static t_builtin	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return(BT_ECHO);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return(BT_CD);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return(BT_PWD);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return(BT_EXPORT);	
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return(BT_UNSET);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return(BT_ENV);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return(BT_EXIT);
	else
		return(BT_NO);
}
