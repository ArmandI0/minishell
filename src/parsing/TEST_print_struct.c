/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_print_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/05 11:08:25 by aranger          ###   ########.fr       */
=======
/*   Updated: 2024/03/03 18:56:12 by nledent          ###   ########.fr       */
>>>>>>> main
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

const char* token_to_string(t_token token)
{
    switch (token) {
        case T_NULL:
            return "T_NULL";
        case CHARACTER:
            return "CHARACTER";
        case SINGLE_QUOTE:
            return "SINGLE_QUOTE";
        case DOUBLE_QUOTE:
            return "DOUBLE_QUOTE";
        case REDIRECTION_OPERATOR:
            return "REDIRECTION_OPERATOR";
        case PIPE:
            return "PIPE";
        case DOLLAR:
            return "DOLLAR";
        case SPACES:
            return "SPACES";
        default:
            return "UNKNOWN_TOKEN";
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
	ft_printf_fd(1, "\n######################################################################\n");
	ft_printf_fd(1, "                               ALL_BLOC_COMMAND                          ");
	ft_printf_fd(1, "\n######################################################################\n");
	while (bloc != NULL)
	{
		ft_printf_fd(1, "\n--------------------------------------------------------------\n");
		ft_printf_fd(1, "ID = %d // ADR %p : redir %p \n", bloc->id, bloc, bloc->redir);
		cmd = bloc->cmd;
		ft_printf_fd(1, "##############################  COMMANDE  ##############################\n");
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
		ft_printf_fd(1, "\n######################################################################\n\n");
		redir = bloc->redir;
		ft_printf_fd(1, "##############################  REDIRECTION  ##############################\n");
		while (redir != NULL)
		{
			ft_printf_fd(1, "ADR=%p NEXT=%p TYPE=%s PATH=%s\n",redir, redir->next, redir_def_to_string(redir->type), redir->file_path);
			redir = redir->next;
		}	
		bloc = bloc->next;
		ft_printf_fd(1, "######################################################################\n\n");
		i = 0;
	}
	
}

void printList(t_list* node) 
{
	ft_printf_fd(1, "\n##############################  LIST  ##############################\n");
    while (node != NULL)
	{
        ft_printf_fd(1, " \"%s\" ", node->content);
        node = node->next;
    }
    printf("\n");
}

void	print_lexer(t_lexer *lx)
{
	int	i;

	i = 0;
	ft_printf_fd(1, "\n##############################  LEXEUR  ##############################\n");
	ft_printf_fd(1, "ENTRY = %s\n", lx->entry);
	ft_printf_fd(1, "LEXER = ");
	while (lx->entry[i])
	{
		ft_printf_fd(1, "%d", lx->lexing[i]);
		i++;
	}
	ft_printf_fd(1, "\n######################################################################\n");
}
