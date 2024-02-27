/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 13:49:24 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static void handler_sigint(int signum)
{
	(void)signum;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

