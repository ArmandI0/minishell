/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/16 19:12:29 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_pwd(char *pwd)
{
	free (pwd);
	exit(1);
}

/*attention ajouter les variables qu'il faut free*/
void	ft_pwd(void) 
{
	char	*pwd;
	int		size;

	size = 500;
	while (1)
	{
		pwd = malloc(sizeof(char) * size);
		if (pwd == NULL)
			exit(1); //vois si rajouter free
		if (getcwd(pwd, sizeof(pwd)) != NULL)
		{
			ft_putstr_fd(pwd, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			free(pwd);
			break;
		}
		else if (errno == ERANGE)
			size +=500;
		else
			exit_pwd(pwd);
		free(pwd);
	}
}
