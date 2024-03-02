/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/02 16:59:41 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_chdir(char *path_dir, t_cmd *cd)
{
	if (path_dir == NULL)
		return (1);
	if (chdir(path_dir) != 0)
	{
		print_error(ER_CD_DIR_FILE_N_FOUND, cd);
		free(path_dir);
		return (1);
	}
	if (path_dir != NULL)
		free (path_dir);
	return (0);
}

int    bt_cd(t_cmd *cd)
{
	char	*home_directory;
	char	*path_dir;

	home_directory = getenv("HOME");
	path_dir = NULL;
	if (cd->argc == 1)
	{
		if (home_directory != NULL)
			return (chdir(home_directory));
		else
			return (1);
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
		print_error(ER_CD_TOO_MANY_ARGS, cd);
		return (1);
	}
	return (do_chdir(path_dir, cd));
}
