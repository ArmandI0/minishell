/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/02/27 13:48:39 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    bt_echo(t_cmd *echo)
{
    int       i;
    t_bool    n;

    i = 1;
    n = FALSE;
    while (echo->args[i] != NULL && (ft_strncmp(echo->args[i], "-n", 3) == 0))
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
