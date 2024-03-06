/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/06 17:43:22 by nledent          ###   ########.fr       */
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

/* static void handler_sigquit(int signum)
{
	(void)signum;
    exit (1);
} */

void	init_signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void    ign_sigint(void)
{
	signal(SIGINT, SIG_IGN);
}

void	re_init_def_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}
