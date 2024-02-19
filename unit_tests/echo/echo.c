/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/18 16:09:03 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// attention : gerer echo -n -n  ???
void	bt_echo(t_cmd *echo)
{
	if (echo->argc == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (echo->argc == 2 && (ft_strncmp(echo->args[1], "-n", 3) != 0))
	{
		ft_putstr_fd(echo->args[1], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else if (echo->argc == 2 && (ft_strncmp(echo->args[1], "-n", 3) == 0))
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putstr_fd(echo->args[2], STDOUT_FILENO);
}
