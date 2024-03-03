/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:24:54 by aranger           #+#    #+#             */
/*   Updated: 2024/03/03 17:00:51 by aranger          ###   ########.fr       */
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
	int			a;

	tmp = *args;
	bloc = data->bloc;
	check_builtin("sfs");
	a = 0;
	while (tmp != NULL && bloc != NULL)
	{
		if (bloc != NULL && tmp->content && (ft_strncmp(tmp->content, "|", 2) == 0 || a == 0))
		{
			if (ft_strncmp(tmp->content, "|", 2) == 0)
				bloc = bloc->next;
			bloc->builtin = check_builtin(tmp->content);
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			if (new_cmd == NULL)
				return ;
			if (bloc->builtin != BT_NO)
				new_cmd->path = find_command_path(data->envp, tmp->content);
			new_cmd->name = ft_strdup(tmp->content);
			new_cmd->args = all_args(tmp);
			new_cmd->argc = count_args(new_cmd->args);
			bloc->cmd = new_cmd;
			a = 1;
			bloc = bloc->next;
		}
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
	char	*newline;
	char	**all_args;

	tmp = args;
	newline = ft_calloc(1, sizeof(char));
	while (tmp != NULL && ft_strncmp(tmp->content, "|", 2) != 0)
	{
		newline = ft_strjoin(newline, tmp->content, TRUE);
		newline = ft_strjoin(newline, " ", TRUE);
		tmp = tmp->next;
	}
	all_args = ft_split(newline, 32);
	int i = 0;
	while(all_args[i])
	{
		ft_printf_fd(1, "%s", all_args[i]);
		i++;
	}
	free(newline);
	return(all_args);
}

static t_builtin	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return(BT_ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return(BT_CD);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return(BT_PWD);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return(BT_EXPORT);	
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return(BT_UNSET);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return(BT_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return(BT_EXIT);
	return(BT_NO);
}
