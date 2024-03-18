/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 20:58:52 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_bck_n(char *str)
{
	int	i;

	i = 1;
	if (ft_strncmp(str, "-n", 3) == 0)
		return (1);
	if (str[0] != '-')
		return (0);
	while (str[i] != 0)
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	bt_echo(t_cmd *echo)
{
	int		i;
	t_bool	n;

	i = 1;
	n = FALSE;
	while (echo->args[i] != NULL && check_bck_n(echo->args[i]))
	{
		n = TRUE;
		i++;
	}
	while (echo->args[i] != NULL)
	{
		ft_putstr_fd(echo->args[i], STDOUT_FILENO);
		if (echo->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n == TRUE)
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}
