/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/18 21:33:17 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* NB : possibility of implementing variables in here docs */
static char	*ft_here_doc(char *lim)
{
	char	*here_doc;
	char	*line;
	char	*limiter;

	here_doc = ft_strdup("");
	limiter = ft_strjoin(lim, "\n", 0);
	line = ft_strdup("");
	ft_putstr_fd(">", STDOUT_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (line[0] != 0)
			ft_putstr_fd(">", STDOUT_FILENO);
		here_doc = ft_fstrjoin(here_doc, line);
		line = get_next_line(0);
		if (line == NULL)
		{
			line = ft_strdup(limiter);
			printf("minishell warning : here_doc stopped by EOF (ctrl+d)");
		}
	}
	free(line);
	free(limiter);
	return (here_doc);
}

void	launch_hdocs(t_list_cmd *list_cmds)
{
	t_list_cmd	*next;

	next = list_cmds;
	while (next != NULL)
	{
		if (next->limiter != NULL)
			next->hdoc = ft_here_doc(next->limiter);
		next = next->next;
	}
}
