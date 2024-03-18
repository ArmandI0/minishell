/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 20:29:44 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_pwd(char *pwd)
{
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

char	*ft_getcwd(void)
{
	char	*pwd;
	int		size;

	size = 500;
	while (1)
	{
		pwd = NULL;
		pwd = ft_calloc(size, sizeof(char));
		if (pwd == NULL)
			return (NULL);
		if (getcwd(pwd, size) != NULL)
			break ;
		else if (errno == ERANGE)
			size += 500;
		else
			break ;
		free(pwd);
	}
	return (pwd);
}

int	bt_pwd(void)
{
	char	*pwd;
	int		r_value;

	r_value = 1;
	pwd = ft_getcwd();
	if (pwd != NULL)
	{
		print_pwd(pwd);
		free(pwd);
		r_value = 0;
	}
	return (r_value);
}
