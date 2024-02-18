/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/18 17:15:37 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_pwd(char *pwd, int *r_value)
{
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	*r_value = 0;
}

int	ft_pwd(void) 
{
	char	*pwd;
	int		size;
	int		r_value;

	size = 500;
	r_value = -1;
	while (1)
	{
		pwd = malloc(sizeof(char) * size);
		if (pwd == NULL)
			return (-1);
		if (getcwd(pwd, sizeof(pwd)) != NULL)
		{
			print_pwd(pwd, &r_value);
			break;
		}
		else if (errno == ERANGE)
			size +=500;
		else
			break;
		free(pwd);
	}
	free(pwd);
	return (r_value);
}
