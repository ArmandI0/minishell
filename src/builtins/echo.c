/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/19 14:05:46 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// attention : gerer echo -n -n  ??? -> a faire dans le parsing : si plusieurs -n de suite séparés par espaces: n'enregistrer que le premier
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

void	bt_echo_aranger(t_cmd *echo)
{
	int		i;
	t_bool	n;

	i = 1;
	n = FALSE;
	if (echo->args[i] == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	while(echo->args[i] != NULL)
	{
		if ((ft_strncmp(echo->args[i], "-n", 3) == 0))
			n = TRUE;
		else
		{
			ft_putstr_fd(echo->args[i], STDOUT_FILENO);
			if (n == TRUE)
				ft_putstr_fd("", STDOUT_FILENO);
			else
				ft_putchar_fd('\n', STDOUT_FILENO);
		}	
		i++;
	}		
}
