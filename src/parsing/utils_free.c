/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:21:43 by aranger           #+#    #+#             */
/*   Updated: 2024/03/02 19:48:21 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer(t_lexer *lx)
{
	if (lx != NULL)
	{
		if (lx->entry != NULL)
			free(lx->entry);
		if (lx->lexing != NULL)
			free(lx->lexing);
		free(lx);
		lx = NULL;
	}
}

void	free_node(t_list *node)
{
	free(node->content);
	free(node);
}