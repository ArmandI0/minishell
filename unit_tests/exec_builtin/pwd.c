/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/26 13:19:28 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_pwd(char *pwd)
{
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	bt_pwd(void) 
{
	char	*pwd;
	int		size;
	int		r_value;

	size = 500;
	r_value = -1;
	while (1)
	{
		pwd = ft_calloc(size, sizeof(char));
		if (pwd == NULL)
			return (-1);
		if (getcwd(pwd, size) != NULL)
		{
			r_value = print_pwd(pwd);
			break;
		}
		else if (errno == ERANGE)
			size += 500;
		else
			break;
		free(pwd);
	}
	free(pwd);
	return (r_value);
}
