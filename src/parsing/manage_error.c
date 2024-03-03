/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:31:57 by aranger           #+#    #+#             */
/*   Updated: 2024/03/02 19:49:31 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quote_error(t_lexer *lx)
{
	if (lx != NULL)
	{
		if (lx->lexing != NULL)
			free(lx->lexing);
		free(lx);
		lx = NULL;
	}
	ft_putstr_fd("Quotes error\n", 2);
}