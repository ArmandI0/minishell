/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/05 16:03:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_and_print(char *arg, t_cmd *cmd)
{
	if (check_var_name(arg) == 1)
	{
		if (ft_strchr(arg, '=') != 0)
			*(ft_strchr(arg, '=')) = 0;
		print_error(ER_EXPORT, cmd, arg);
		return (1);
	}
	else
		return (0);
}

static char *export_extract_name(char *name)
{
	char	*extr_name;
	char	*ad_equal;

	extr_name = ft_strdup(name);
	ad_equal = ft_strchr(extr_name, '=');
	if (ad_equal != 0)
		*ad_equal = 0;
	return (extr_name);
}

static char *export_extract_value(char *value)
{
	char *extr_value;

	if (ft_strchr(value, '=') == 0)
		extr_value = ft_strdup("");
	else
		extr_value = ft_strdup((ft_strchr(value, '=') + 1));
	return (extr_value);
}

int	edit_env_var(t_sh_data *sh, t_cmd *cmd)
{
	int		i;
	int		r_value;
	char	*name;
	char	*value;
	
	r_value = 0;
	i = 1;
	while (cmd->args[i] != NULL && r_value == 0)
	{
		if (check_and_print(cmd->args[i], cmd) == 1)
			return (1);
		name = export_extract_name(cmd->args[i]);
		value = export_extract_value(cmd->args[i]);
		if (upd_env_var(sh, name, value) == 0)
			r_value = 0;
		else if (add_env_var(sh, name, value) == 0)
			r_value = 0;
		else
			r_value = 1;
		free(name);
		free(value);
		i++;
	}
	return (r_value);
}

int	bt_export(t_sh_data *sh, t_cmd *cmd)
{
	int	r_value;
	
	r_value = 0;
	if (cmd->args[1] == NULL)
		print_env(sh);
	else
		r_value = edit_env_var(sh, cmd);
	return (r_value);
}
