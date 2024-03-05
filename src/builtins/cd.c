/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/03 21:38:44 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_chdir(t_sh_data *sh,char *path_dir, t_cmd *cd)
{
	char	*oldpwd;

	oldpwd = ft_getcwd();
	if (path_dir == NULL)
		return (1);
	if (chdir(path_dir) != 0)
	{
		print_error(ER_CD_DIR_FILE_N_FOUND, cd, NULL);
		free(path_dir);
		free(oldpwd);
		return (1);
	}
	upd_env_var(sh, "OLDPWD", oldpwd);
	free(path_dir);
	path_dir = ft_getcwd();
	upd_env_var(sh, "PWD", path_dir);
	free(oldpwd);
	free(path_dir);
	return (0);
}

int    bt_cd(t_sh_data *sh, t_cmd *cd)
{
	char	*home_directory;
	char	*path_dir;

	home_directory = getenv("HOME");
	path_dir = NULL;
	if (cd->argc == 1)
	{
		if (home_directory != NULL)
			path_dir = ft_strdup(home_directory);
	}
	else if (cd->argc == 2 && cd->args[1][0] ==  '~')
	{
		if (home_directory != NULL)
			path_dir = ft_strjoin(home_directory, &(cd->args[1][1]), 0);
	}
	else if (cd->argc == 2)
		path_dir = ft_strdup(cd->args[1]);
	else
	{
		print_error(ER_CD_TOO_MANY_ARGS, cd, NULL);
		return (1);
	}
	return (do_chdir(sh, path_dir, cd));
}
