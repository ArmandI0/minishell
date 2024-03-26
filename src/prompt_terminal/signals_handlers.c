/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/26 16:23:24 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sign_received = 0;

void	handler_sigquit_during_process(int signum)
{
	if (signum == SIGQUIT)
		ft_printf_fd(2, "Quit (core dumped)");
}

void	handler_sigint_main(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sign_received = 1;
}

void	handler_hdoc(int signum)
{
	(void)signum;
	close(0);
	g_sign_received = 1;
}
