/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/29 22:19:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    bt_cd(t_cmd *cd)
{
	char	*home_directory;

	if (cd->argc > 2)
		print_error(ER_CD_TOO_MANY_ARGS, cd);
	else if (cd->argc == 1)
	{
		home_directory = getenv("HOME");
		if (home_directory != NULL)
			chdir(home_directory);
	}
	else if (chdir(cd->args[1]) != 0)
		print_error(ER_CD_DIR_FILE_N_FOUND, cd);
	bt_pwd();
}
