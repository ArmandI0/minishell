/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/26 16:23:27 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_during_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handler_sigquit_during_process);
}

void	sigint_hdoc(void)
{
	signal(SIGINT, handler_hdoc);
}

void	init_signals(void)
{
	signal(SIGINT, handler_sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void	re_init_def_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
