/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_print_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/03 18:03:41 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char* redir_def_to_string(t_redir_def redir)
{
    switch (redir) {
        case HEREDOC:
            return "HEREDOC";
        case INPUT_REDIR:
            return "INPUT_REDIR";
        case OUTPUT_REDIR:
            return "OUTPUT_REDIR";
        case APPEND:
            return "APPEND";
        default:
            return "UNKNOWN";
    }
}

void print_all_bloc(t_sh_data *a)
{
	int i = 0;
	t_bloc_cmd	*bloc;
	t_redir		*redir;
	t_cmd		*cmd;
	
	bloc = a->bloc;
	ft_printf_fd(1, "%p", bloc);
	while (bloc != NULL)
	{
		ft_printf_fd(1, "\n--------------------------------------------------------------\n");
		ft_printf_fd(1, "ID = %d // ADR %p : redir %p \n", i, bloc, bloc->redir);
		cmd = bloc->cmd;
		ft_printf_fd(1, "######--COMMANDE--#####\n");
		if (cmd != NULL)
		{
			ft_printf_fd(1, "Command name : %s || path : %s || argc : %d ||arguments : ", cmd->name, cmd->path, cmd->argc);
			if (cmd->args != NULL)
			{
				while(cmd->args[i] != NULL)
				{
					ft_printf_fd(1, "%s ", cmd->args[i]);
					i++;				
				}
			}
		}
		ft_printf_fd(1, "\n##########################\n\n");
		redir = bloc->redir;
		ft_printf_fd(1, "######--REDIRECTION--#####\n");
		while (redir != NULL)
		{
			ft_printf_fd(1, "ADR=%p NEXT=%p TYPE=%s PATH=%s\n",redir, redir->next, redir_def_to_string(redir->type), redir->file_path);
			redir = redir->next;
		}	
		bloc = bloc->next;
		ft_printf_fd(1, "##########################\n\n");
		i = 0;
	}
	
}

void printList(t_list* node) 
{
    while (node != NULL) 
	{

        ft_printf_fd(1, "-%s-", node->content);
        node = node->next;
    }
    printf("\n");
}




